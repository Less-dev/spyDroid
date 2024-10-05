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

size_t headerCallback(char* buffer, size_t size, size_t nitems, void* userdata) {
    size_t numBytes = size * nitems;
    ProgressData* progressData = static_cast<ProgressData*>(userdata);
    
    std::string header(buffer, numBytes);
    if (header.find("Content-Length:") != std::string::npos) {
        std::string contentLengthStr = header.substr(16);  // "Content-Length:" tiene 15 caracteres más 1 de espacio.
        progressData->totalSize = std::stod(contentLengthStr);
    }
    return numBytes;
}

int progressFunction(void* progressDataPtr, curl_off_t total, curl_off_t now, curl_off_t, curl_off_t) {
    auto* progressData = static_cast<ProgressData*>(progressDataPtr);

    if (total > 0) {
        progressData->totalSize = static_cast<double>(total);
    }
    progressData->downloaded = static_cast<double>(now);

    if (progressData->totalSize > 0) {
        double progressPercentage = (progressData->downloaded / progressData->totalSize) * 100.0;
        if (progressPercentage - progressData->lastReportedPercentage >= 1.0) {
            progressData->lastReportedPercentage = progressPercentage;
            progressData->progressCallback(progressData->currentUrl, progressData->downloaded, progressData->totalSize, progressData->isRunning);
        }
    } else {
        progressData->progressCallback(progressData->currentUrl, progressData->downloaded, -1.0, progressData->isRunning);
    }

    return 0;
}

bool DownloaderService::checkUrl(const std::string& url) {
    CURL* curl;
    CURLcode res;
    bool isValid = false;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");

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
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 100L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progressFunction);
        curl_easy_setopt(curl, CURLOPT_XFERINFODATA, &progressData);
        
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, headerCallback);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &progressData);

        progressData.currentUrl = url;
        progressData.downloaded = 0.0;
        progressData.totalSize = 0.0;
        progressData.lastReportedPercentage = 0.0;

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
    const std::map<std::string, std::string>& urlToFileMap,  // Usamos map en lugar de vectores
    std::function<void(const std::string&, double, double, bool)> progressCallback) {

    std::thread downloadThread([this, directory, urlToFileMap, progressCallback]() {
        ProgressData progressData;
        progressData.progressCallback = progressCallback;
        progressData.isRunning = true;

        for (const auto& entry : urlToFileMap) {  // Iterar sobre cada par URL -> archivo
            std::string url = entry.first;
            std::string filename = entry.second;

            // Eliminar posibles espacios al final de la URL
            url.erase(url.find_last_not_of(" \n\r\t") + 1);

            if (!checkUrl(url)) {
                std::cerr << "Error: URL inválida o no accesible: " << url << std::endl;
                continue;
            }

            std::string outputPath = getOutputFilePath(directory, filename);

            if (!downloadFile(url, outputPath, progressData)) {
                std::cerr << "Error: No se pudo descargar el archivo de la URL: " << url << std::endl;
                continue;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Pausar entre descargas
        }

        progressData.isRunning = false;
        progressCallback("", 0, 0, progressData.isRunning);
    });

    downloadThread.detach();
}