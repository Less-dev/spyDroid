#include "FilesManager.h"
#include <zip.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <cstring>
#include <cctype>


namespace fs = std::filesystem;

// Función auxiliar para agregar permiso de ejecución a un archivo
void addExecutePermission(const fs::path& filePath) {
    std::error_code ec;
    
    // Obtenemos los permisos actuales del archivo
    auto currentPerms = fs::status(filePath, ec).permissions();
    
    if (ec) {
        std::cerr << "Error obtaining file permissions: " << ec.message() << std::endl;
        return;
    }
    
    // Asignamos el bit de ejecución al propietario
    fs::permissions(filePath, currentPerms | fs::perms::owner_exec, ec);
    
    if (ec) {
        std::cerr << "Error setting file permissions: " << ec.message() << std::endl;
    }
}

// Función para verificar si un archivo es binario
bool isBinaryFile(const fs::path& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    
    if (!file) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return false;
    }
    
    // Leer los primeros 512 bytes para determinar si es binario
    char buffer[512];
    file.read(buffer, sizeof(buffer));
    std::streamsize bytesRead = file.gcount();
    
    // Contar los caracteres no imprimibles
    int nonPrintableCount = 0;
    for (std::streamsize i = 0; i < bytesRead; ++i) {
        if (!std::isprint(static_cast<unsigned char>(buffer[i])) && !std::isspace(static_cast<unsigned char>(buffer[i]))) {
            nonPrintableCount++;
        }
    }

    // Si más del 30% de los caracteres no son imprimibles, consideramos que es binario
    return nonPrintableCount > (bytesRead * 0.3);
}

// Función para verificar si un archivo está en un directorio llamado "bin"
bool isInBinDirectory(const fs::path& filePath) {
    // Recorremos cada uno de los componentes de la ruta
    for (const auto& part : filePath.parent_path()) {
        if (part.filename() == "bin") {
            return true;  // El archivo está en un directorio llamado "bin"
        }
    }
    return false;
}

// Función que determina si un archivo debe ser ejecutable
bool shouldBeExecutable(const fs::path& filePath) {
    // Regla 1: Revisamos la extensión primero
    if (filePath.extension() == ".sh") {
        return true;  // Script de shell
    }

    // Regla 2: Verificamos si es binario
    if (isBinaryFile(filePath)) {
        return true;  // Es un archivo binario
    }

    // Regla 3: Verificamos si está en un directorio "bin"
    if (isInBinDirectory(filePath)) {
        return true;  // Está en un directorio "bin"
    }

    // Regla 4: Verificamos si el archivo se llama exactamente "gradlew"    
    if (filePath.filename() == "gradlew") {
        return true;  // El archivo es "gradlew", así que debe ser ejecutable
    }


    return false;  // No se debe hacer ejecutable
}


// Constructor
FilesManager::FilesManager(const std::string& baseDir, const std::unordered_map<std::string, std::string>& fileMap)
    : baseDir(baseDir), fileMap(fileMap) {
    if (!fs::exists(baseDir)) {
        throw std::runtime_error("The base directory does not exist.");
    }
}

// Ensure the directory exists
void FilesManager::createDirectoryIfNotExists(const fs::path& dirPath) {
    if (!fs::exists(dirPath)) {
        std::error_code ec;
        if (!fs::create_directories(dirPath, ec)) {
            std::cerr << "Error creating directory: " << dirPath << " - " << ec.message() << std::endl;
            throw std::runtime_error("Failed to create directory: " + dirPath.string());
        }
    }
}

// Move file to the target directory
void FilesManager::moveFile(const std::string& fileName, const std::string& destinationDir) {
    fs::path sourceFile = fs::path(baseDir) / fileName;
    fs::path destinationFile = fs::path(destinationDir) / fileName;

    if (!fs::exists(sourceFile)) {
        std::cerr << "File " << fileName << " does not exist in the base directory." << std::endl;
        return;
    }

    createDirectoryIfNotExists(destinationDir);
    fs::rename(sourceFile, destinationFile);
}

// Extract a ZIP file to the target directory
bool FilesManager::extractFile(const std::string& zipPath, const std::string& destinationDir) {
    int error;
    zip* archive = zip_open(zipPath.c_str(), ZIP_RDONLY, &error);
    if (!archive) {
        std::cerr << "Failed to open ZIP file: " << zipPath << std::endl;
        return false;
    }

    zip_int64_t numEntries = zip_get_num_entries(archive, 0);
    for (zip_uint64_t i = 0; i < numEntries; ++i) {
        const char* entryName = zip_get_name(archive, i, 0);
        if (!entryName) {
            std::cerr << "Failed to read entry " << i << std::endl;
            zip_close(archive);
            return false;
        }

        // Determine full path for the entry
        std::string outputPath = destinationDir + "/" + entryName;
        fs::path outputFilePath(outputPath);

        // Check if the entry is a directory (ends with '/')
        if (entryName[strlen(entryName) - 1] == '/') {
            createDirectoryIfNotExists(outputFilePath);  // Create directory
            continue;  // Skip to the next entry
        }

        // Ensure parent directories exist for the entry
        if (outputFilePath.has_parent_path()) {
            createDirectoryIfNotExists(outputFilePath.parent_path());
        }

        // Open the ZIP entry
        struct zip_file* zf = zip_fopen_index(archive, i, 0);
        if (!zf) {
            std::cerr << "Failed to open ZIP entry " << entryName << std::endl;
            zip_close(archive);
            return false;
        }

        // Create the output file
        std::ofstream outFile(outputPath, std::ios::binary);
        if (!outFile) {
            std::cerr << "Failed to create file: " << outputPath << std::endl;
            zip_fclose(zf);
            zip_close(archive);
            return false;
        }

        // Write data from the ZIP entry to the output file
        char buffer[8192];
        zip_int64_t bytesRead;
        while ((bytesRead = zip_fread(zf, buffer, sizeof(buffer))) > 0) {
            outFile.write(buffer, bytesRead);
        }

        if (bytesRead < 0) {
            std::cerr << "Error reading entry " << entryName << std::endl;
            zip_fclose(zf);
            zip_close(archive);
            return false;
        }

        if (shouldBeExecutable(outputFilePath)) {
            addExecutePermission(outputFilePath);
        }

        zip_fclose(zf);  // Close the ZIP entry
    }

    zip_close(archive);  // Close the ZIP archive
    return true;
}

// Process files: Move and extract with progress callback
void FilesManager::processFiles(const std::function<void(double, bool)>& progressCallback) {
    size_t totalFiles = fileMap.size();
    size_t processedFiles = 0;

    for (const auto& pair : fileMap) {
        const std::string& fileName = pair.first;
        const std::string& directory = pair.second;

        fs::path targetDir = fs::path(baseDir) / directory;

        moveFile(fileName, targetDir.string());

        if (extractFile((targetDir / fileName).string(), targetDir.string())) {
            processedFiles++;
        } else {
            std::cerr << "Failed to extract: " << (targetDir / fileName).string() << std::endl;
        }

        double progress = (static_cast<double>(processedFiles) / totalFiles) * 100.0;
        bool isCompleted = (processedFiles == totalFiles);
        progressCallback(progress, isCompleted);
    }
}

// Extract all ZIP files with progress callback
void FilesManager::extractFiles(const std::function<void(double, bool)>& progressCallback) {
    size_t totalFiles = fileMap.size();
    size_t extractedFiles = 0;

    for (const auto& pair : fileMap) {
        const std::string& fileName = pair.first;
        const std::string& directory = pair.second;

        fs::path targetDir = fs::path(baseDir) / directory;
        fs::path zipFilePath = targetDir / fileName;

        if (extractFile(zipFilePath.string(), targetDir.string())) {
            extractedFiles++;
        } else {
            std::cerr << "Failed to extract: " << zipFilePath.string() << std::endl;
        }

        double progress = (static_cast<double>(extractedFiles) / totalFiles) * 100.0;
        bool isCompleted = (extractedFiles == totalFiles);
        progressCallback(progress, isCompleted);
    }
}
