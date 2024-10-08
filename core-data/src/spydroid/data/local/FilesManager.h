#ifndef FILESMANAGER_H
#define FILESMANAGER_H

#include <unordered_map>
#include <string>
#include <filesystem>
#include <functional>

class FilesManager {
public:
    // Constructor que recibe el diccionario de archivos y el directorio base
    FilesManager(const std::string& baseDir, const std::unordered_map<std::string, std::string>& fileMap);

    // Función para procesar archivos con un callback para el progreso
    void processFiles(const std::function<void(double, bool)>& progressCallback);

    // Función para descomprimir los archivos después de haberlos movido
    void extractFiles(const std::function<void(double, bool)>& progressCallback);

private:
    std::unordered_map<std::string, std::string> fileMap;  // Diccionario de archivos y sus directorios
    std::string baseDir;  // Directorio base

    // Función auxiliar para crear un directorio si no existe
    void createDirectoryIfNotExists(const std::filesystem::path& dirPath);

    // Función auxiliar para mover un archivo
    void moveFile(const std::string& fileName, const std::string& destinationDir);

    // Función auxiliar para descomprimir un archivo
    bool extractFile(const std::string& filePath, const std::string& destinationDir);
};

#endif // FILESMANAGER_H
