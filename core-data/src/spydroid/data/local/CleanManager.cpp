#include "CleanManager.h"
#include <iostream>
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

CleanManager::CleanManager(const std::string& dirPath,
                           const std::unordered_map<std::string, std::string>& fileMap,
                           const std::unordered_map<std::string, std::string>& dirMap)
    : dirPath(dirPath), fileMap(fileMap), dirMap(dirMap) {}

void CleanManager::cleanCompressedFiles() {
    for (const auto& [fileName, relativePath] : fileMap) {
        // Construye el path completo del archivo
        fs::path fullPath = fs::path(dirPath) / relativePath / fileName;

        if (fs::exists(fullPath)) {
            try {
                std::cout << "Deleting file: " << fullPath << std::endl;
                fs::remove(fullPath); // Elimina el archivo
            } catch (const std::filesystem::filesystem_error& e) {
                std::cerr << "Error deleting file: " << e.what() << std::endl;
            }
        } else {
            std::cerr << "File does not exist: " << fullPath << std::endl;
        }
    }
}

void CleanManager::renameDirectories() {
    for (const auto& [oldDirName, newDirName] : dirMap) {
        if (oldDirName == newDirName) {
            // Si el nombre es el mismo, no se hace nada
            continue;
        }

        // Busca la ruta original basada en el fileMap (directorio donde está el archivo)
        for (const auto& [fileName, relativePath] : fileMap) {
            if (fileName.find(oldDirName) != std::string::npos) {
                // La carpeta original está en relativePath
                fs::path oldDirPath = fs::path(dirPath) / relativePath / oldDirName;
                fs::path newDirPath = fs::path(dirPath) / relativePath / newDirName;

                if (fs::exists(oldDirPath)) {
                    try {
                        std::cout << "Renaming directory: " << oldDirPath << " to " << newDirPath << std::endl;
                        fs::rename(oldDirPath, newDirPath); // Renombra el directorio
                    } catch (const std::filesystem::filesystem_error& e) {
                        std::cerr << "Error renaming directory: " << e.what() << std::endl;
                    }
                } else {
                    std::cerr << "Directory does not exist: " << oldDirPath << std::endl;
                }

                // Termina el ciclo si se encuentra la carpeta correcta
                break;
            }
        }
    }
}

void CleanManager::removeFile(const std::string& filePath) {
    if (fs::exists(filePath)) {
        try {
            fs::remove(filePath);
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error removing file: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "File does not exist: " << filePath << std::endl;
    }
}

void CleanManager::renameDirectory(const std::string& oldName, const std::string& newName) {
    fs::path oldPath = fs::path(dirPath) / oldName;
    fs::path newPath = fs::path(dirPath) / newName;

    if (fs::exists(oldPath)) {
        try {
            fs::rename(oldPath, newPath);
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error renaming directory: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "Directory does not exist: " << oldPath << std::endl;
    }
}
