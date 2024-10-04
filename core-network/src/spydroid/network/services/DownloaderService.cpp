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

#include "DownloaderService.h"
#include <iostream>
#include <curl/curl.h>
#include <thread>
#include <chrono>

// Función para escribir los datos descargados en el archivo
size_t writeData(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    return fwrite(ptr, size, nmemb, stream);
}

// Función de progreso para mostrar el estado de la descarga
int progressFunction(void* progressDataPtr, curl_off_t total, curl_off_t now, curl_off_t, curl_off_t) {
    auto* progressData = static_cast<ProgressData*>(progressDataPtr);

    if (total > 0) {
        progressData->totalSize = static_cast<double>(total);
        progressData->downloaded = static_cast<double>(now);

        // Solo notifica si ha habido un progreso de al menos 1%
        double progressPercentage = (progressData->totalSize > 0) ? (progressData->downloaded / progressData->totalSize) * 100.0 : 0.0;
        if (progressPercentage - progressData->lastReportedPercentage >= 1.0) {
            progressData->lastReportedPercentage = progressPercentage;
            progressData->progressCallback(progressData->currentUrl, progressData->downloaded, progressData->totalSize, progressData->isRunning);
        }
    }

    return 0;  // Continuar la descarga
}

bool DownloaderService::checkUrl(const std::string& url) {
    CURL* curl;
    CURLcode res;
    bool isValid = false;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);  // Sigue redirecciones
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);  // Realiza una petición HEAD para verificar la URL
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");  // Establece un User-Agent

        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            isValid = true;
        } else {
            std::cerr << "Error: " << curl_easy_strerror(res) << " al verificar URL: " << url << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    return isValid;
}

bool DownloaderService::downloadFile(const std::string& url, const std::string& outputPath, ProgressData& progressData) {
    CURL* curl;
    CURLcode res;
    FILE* file = fopen(outputPath.c_str(), "wb");
    if (!file) {
        std::cerr << "Error: No se pudo abrir el archivo para escritura: " << outputPath << std::endl;
        return false;
    }

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);  // Sigue redirecciones
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 100L);  // Límite de redirecciones
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");  // Agente de usuario
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);  // Habilita la función de progreso
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progressFunction);
        curl_easy_setopt(curl, CURLOPT_XFERINFODATA, &progressData);

        progressData.currentUrl = url;
        progressData.downloaded = 0.0;
        progressData.totalSize = 0.0;
        progressData.lastReportedPercentage = 0.0;

        // Realiza la descarga
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Error al descargar: " << curl_easy_strerror(res) << " para la URL: " << url << std::endl;
            fclose(file);
            curl_easy_cleanup(curl);
            return false;
        }

        fclose(file);
        curl_easy_cleanup(curl);
        return true;
    }

    fclose(file);
    return false;
}

std::string DownloaderService::getOutputFilePath(const std::string& directory, const std::string& filename) {
    return directory + "/" + filename;
}

void DownloaderService::downloadFiles(
    const std::string& directory, 
    const std::vector<std::string>& urls, 
    const std::vector<std::string>& filenames, 
    std::function<void(const std::string&, double, double, bool)> progressCallback) {

    // Ejecutar las descargas en un hilo separado
    std::thread downloadThread([this, directory, urls, filenames, progressCallback]() {
        ProgressData progressData;
        progressData.progressCallback = progressCallback;
        progressData.isRunning = true;

        for (size_t i = 0; i < urls.size(); ++i) {
            std::string url = urls[i];
            std::string filename = filenames[i];

            // Eliminar posibles espacios al final de la URL
            url.erase(url.find_last_not_of(" \n\r\t") + 1);

            // Verifica si la URL es válida
            if (!checkUrl(url)) {
                std::cerr << "Error: URL inválida o no accesible: " << url << std::endl;
                continue;  // Saltar a la siguiente URL
            }

            // Obtener el path completo para el archivo de salida
            std::string outputPath = getOutputFilePath(directory, filename);

            // Intentar descargar el archivo
            if (!downloadFile(url, outputPath, progressData)) {
                std::cerr << "Error: No se pudo descargar el archivo de la URL: " << url << std::endl;
                continue;  // Saltar a la siguiente URL
            }

            // Pausa entre descargas para evitar ser bloqueado
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Pausar 1 segundo entre descargas
        }

        // Indicar que todas las descargas han terminado
        progressData.isRunning = false;
        progressCallback("", 0, 0, progressData.isRunning);
    });

    // Desvincular el hilo para que se ejecute en segundo plano
    downloadThread.detach();
}
