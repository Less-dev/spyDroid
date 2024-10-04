/*
 * Copyright (C) 2024 Daniel Gómez(Less)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */


#ifndef DOWNLOADER_SERVICE_H
#define DOWNLOADER_SERVICE_H
#include <string>
#include <vector>
#include <functional>

class DownloaderService {
public:
    // Constructor por defecto
    DownloaderService() = default;

    // Método principal para descargar múltiples archivos
    void downloadFiles(
        const std::string& directory, 
        const std::vector<std::string>& urls, 
        const std::vector<std::string>& filenames, 
        std::function<void(const std::string&, double, double, bool)> progressCallback);

private:
    // Verifica si una URL es válida y alcanzable
    bool checkUrl(const std::string& url);

    // Descarga un archivo individual desde una URL
    bool downloadFile(
        const std::string& url, 
        const std::string& outputPath, 
        struct ProgressData& progressData);

    // Devuelve la ruta completa del archivo de salida basado en el directorio y nombre de archivo
    std::string getOutputFilePath(const std::string& directory, const std::string& filename);
};

// Estructura para almacenar los datos de progreso de descarga
struct ProgressData {
    std::string currentUrl;
    double downloaded = 0.0;
    double totalSize = 0.0;
    bool isRunning = false;
    std::function<void(const std::string&, double, double, bool)> progressCallback;
    double lastReportedPercentage = 0.0;
};

#endif // DOWNLOADER_SERVICE_H
