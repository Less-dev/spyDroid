#include "FilesManager.h"
#include <iostream>
#include <filesystem>
#include <stdexcept>

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
        std::cout << "Creando directorio: " << dirPath << std::endl;
        fs::create_directories(dirPath);  // Crea el directorio y cualquier directorio padre si no existen
    }
}

// Mover archivo al directorio correspondiente
void FilesManager::moveFile(const std::string& fileName, const std::string& destinationDir) {
    fs::path sourceFile = fs::path(baseDir) / fileName;  // Archivo original en el directorio base
    fs::path destinationFile = fs::path(destinationDir) / fileName;  // Destino final

    if (fs::exists(sourceFile)) {
        std::cout << "Moviendo archivo: " << sourceFile << " a " << destinationFile << std::endl;
        fs::rename(sourceFile, destinationFile);  // Mover archivo
    } else {
        std::cerr << "El archivo " << fileName << " no existe en el directorio base." << std::endl;
    }
}
