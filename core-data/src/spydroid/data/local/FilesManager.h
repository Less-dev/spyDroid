#ifndef FILES_MANAGER_H
#define FILES_MANAGER_H

#include <string>
#include <unordered_map>
#include <functional>
#include <filesystem>

namespace fs = std::filesystem;

class FilesManager {
public:
    FilesManager(const std::string& baseDir, const std::unordered_map<std::string, std::string>& fileMap);

    // Process files: Move and extract with progress callback
    void processFiles(const std::function<void(double, bool)>& progressCallback);

    // Extract all ZIP files with progress callback
    void extractFiles(const std::function<void(double, bool)>& progressCallback);

private:
    std::string baseDir;
    std::unordered_map<std::string, std::string> fileMap;

    // Ensure the directory exists
    void createDirectoryIfNotExists(const fs::path& dirPath);

    // Move file to the target directory
    void moveFile(const std::string& fileName, const std::string& destinationDir);

    // Extract a ZIP file to the target directory
    bool extractFile(const std::string& zipPath, const std::string& destinationDir);
};

#endif  // FILES_MANAGER_H
