#ifndef CLEAN_MANAGER_H
#define CLEAN_MANAGER_H

#include <string>
#include <unordered_map>

class CleanManager {
public:
    // Constructor que recibe el path del directorio y los dos mapas
    CleanManager(const std::string& dirPath,
                 const std::unordered_map<std::string, std::string>& fileMap,
                 const std::unordered_map<std::string, std::string>& dirMap);

    // Función para eliminar archivos comprimidos
    void cleanCompressedFiles();

    // Función para renombrar los directorios según el segundo diccionario
    void renameDirectories();

private:
    std::string dirPath;
    std::unordered_map<std::string, std::string> fileMap;
    std::unordered_map<std::string, std::string> dirMap;

    // Helper function to remove a file
    void removeFile(const std::string& filePath);

    // Helper function to rename a directory
    void renameDirectory(const std::string& oldName, const std::string& newName);
};

#endif // CLEAN_MANAGER_H
