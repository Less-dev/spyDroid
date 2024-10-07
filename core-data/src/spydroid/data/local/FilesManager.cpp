#include "FilesManager.h"
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <archive.h>
#include <archive_entry.h>

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

// Descomprimir un archivo usando libarchive
bool FilesManager::extractFile(const std::string& filePath, const std::string& destinationDir) {
    struct archive* a;
    struct archive* ext;
    struct archive_entry* entry;
    int flags;
    int r;

    // Configurar opciones para la extracción
    flags = ARCHIVE_EXTRACT_TIME;
    a = archive_read_new();
    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, flags);
    archive_read_support_format_all(a);
    archive_read_support_compression_all(a);

    if ((r = archive_read_open_filename(a, filePath.c_str(), 10240))) {
        std::cerr << "No se puede abrir el archivo " << filePath << std::endl;
        return false;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char* currentFile = archive_entry_pathname(entry);
        std::string fullOutputPath = destinationDir + "/" + currentFile;
        archive_entry_set_pathname(entry, fullOutputPath.c_str());
        r = archive_write_header(ext, entry);

        if (r == ARCHIVE_OK) {
            archive_read_data_into_fd(a, archive_entry_filetype(entry));
        } else {
            std::cerr << "Error al escribir el archivo " << fullOutputPath << std::endl;
        }
        archive_write_finish_entry(ext);
    }

    archive_read_close(a);
    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);

    return true;
}
