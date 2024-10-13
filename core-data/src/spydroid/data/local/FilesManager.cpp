#include "FilesManager.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <archive.h>
#include <archive_entry.h>
#include <thread>


namespace fs = std::filesystem;

// Constructor
FilesManager::FilesManager(const std::string& baseDir, const std::unordered_map<std::string, std::string>& fileMap)
    : baseDir(baseDir), fileMap(fileMap) {
    if (!fs::exists(baseDir)) {
        throw std::runtime_error("El directorio base no existe.");
    }
}

// Procesar archivos con progreso
void FilesManager::processFiles(const std::function<void(double, bool)>& progressCallback) {
    size_t totalFiles = fileMap.size();
    size_t processedFiles = 0;

    for (const auto& pair : fileMap) {
        const std::string& fileName = pair.first;
        const std::string& directory = pair.second;

        fs::path targetDir = fs::path(baseDir) / directory;  // Crear ruta completa del directorio
        createDirectoryIfNotExists(targetDir);  // Crear el directorio si no existe

        moveFile(fileName, targetDir.string());  // Mover el archivo al directorio correspondiente

        // Actualizar progreso
        processedFiles++;
        double progress = (static_cast<double>(processedFiles) / static_cast<double>(totalFiles)) * 100.0;
        bool isCompleted = (processedFiles == totalFiles);

        // Llamada al callback con el progreso y el estado de finalización
        progressCallback(progress, isCompleted);
    }
}

// Crear directorio si no existe
void FilesManager::createDirectoryIfNotExists(const fs::path& dirPath) {
    if (!fs::exists(dirPath)) {
        //std::cout << "Creando directorio: " << dirPath << std::endl;
        fs::create_directories(dirPath);  // Crea el directorio y cualquier directorio padre si no existen
    }
}

// Mover archivo al directorio correspondiente
void FilesManager::moveFile(const std::string& fileName, const std::string& destinationDir) {
    fs::path sourceFile = fs::path(baseDir) / fileName;  // Archivo original en el directorio base
    fs::path destinationFile = fs::path(destinationDir) / fileName;  // Destino final

    if (fs::exists(sourceFile)) {
        //std::cout << "Moviendo archivo: " << sourceFile << " a " << destinationFile << std::endl;
        fs::rename(sourceFile, destinationFile);  // Mover archivo
    } else {
        //std::cerr << "El archivo " << fileName << " no existe en el directorio base." << std::endl;
    }
}

// Función para descomprimir archivos después de moverlos
void FilesManager::extractFiles(const std::function<void(double, bool)>& progressCallback) {
    size_t totalFiles = fileMap.size();
    size_t extractedFiles = 0;

    for (const auto& pair : fileMap) {
        const std::string& fileName = pair.first;
        const std::string& directory = pair.second;
        fs::path targetDir = fs::path(baseDir) / directory;
        fs::path compressedFile = targetDir / fileName;

        if (extractFile(compressedFile.string(), targetDir.string())) {
            extractedFiles++;
        } else {
            std::cerr << "Error al descomprimir el archivo: " << compressedFile << std::endl;
        }

        // Esperar a que termine el archivo antes de proceder con el siguiente
        double progress = (static_cast<double>(extractedFiles) / static_cast<double>(totalFiles)) * 100.0;
        bool isCompleted = (extractedFiles == totalFiles);

        // Llamada al callback con el progreso y el estado de finalización
        progressCallback(progress, isCompleted);
    }
}


bool FilesManager::extractFile(const std::string& filePath, const std::string& destinationDir) {
    struct archive* a;
    struct archive* ext;
    struct archive_entry* entry;
    int flags;
    int r;

    // Configurar opciones para la extracción
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM; // Simplificar las banderas

    // Crear estructuras de lectura y escritura
    a = archive_read_new();
    ext = archive_write_disk_new();

    // Establecer las opciones de extracción
    archive_write_disk_set_options(ext, flags);

    // Soporte para todos los formatos y filtros de compresión
    archive_read_support_format_all(a);       // Soporte para todos los formatos (incluye tar)
    archive_read_support_filter_all(a);       // Soporte para todas las compresiones (incluye gzip)

    // Abrir el archivo comprimido
    if ((r = archive_read_open_filename(a, filePath.c_str(), 10240))) {
        std::cerr << "No se puede abrir el archivo " << filePath << std::endl;
        return false;
    }

    // Iterar sobre cada entrada del archivo comprimido
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char* currentFile = archive_entry_pathname(entry);
        std::string fullOutputPath = destinationDir + "/" + currentFile;

        // Crear cualquier directorio necesario en la ruta de destino
        fs::path outputPath(fullOutputPath);
        fs::create_directories(outputPath.parent_path());

        // Ajustar el nombre de la entrada al nuevo destino
        archive_entry_set_pathname(entry, fullOutputPath.c_str());

        // Escribir el encabezado del archivo
        r = archive_write_header(ext, entry);
        if (r != ARCHIVE_OK) {
            std::cerr << "Error al escribir el encabezado para " << fullOutputPath << ": " 
                      << archive_error_string(ext) << std::endl;
            continue;
        }

        // Leer los datos del archivo y escribirlos en el disco
        const size_t bufferSize = 8192; // Tamaño del buffer de lectura
        char buffer[bufferSize];
        ssize_t size;

        // Leer el contenido del archivo en bloques y escribirlo
        while ((size = archive_read_data(a, buffer, bufferSize)) > 0) {
            std::ofstream outFile(fullOutputPath, std::ios::binary | std::ios::trunc);
            if (!outFile) {
                std::cerr << "Error al abrir el archivo de salida " << fullOutputPath << std::endl;
                return false;
            }
            outFile.write(buffer, size);
            outFile.close();
        }

        if (size < 0) {
            std::cerr << "Error al leer los datos del archivo " << fullOutputPath << ": " 
                      << archive_error_string(a) << std::endl;
            return false;
        }

        // Finalizar la entrada actual
        r = archive_write_finish_entry(ext);
        if (r != ARCHIVE_OK) {
            std::cerr << "Error al finalizar la entrada para " << fullOutputPath << std::endl;
            return false;
        }
    }

    // Cerrar y liberar recursos
    archive_read_close(a);
    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);

    return true;
}
