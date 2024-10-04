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
#include <fstream>
#include <curl/curl.h>

// Function to write data received from curl to a file
size_t writeData(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

// Progress callback function
int progressFunction(void* progressDataPtr, curl_off_t total, curl_off_t now, curl_off_t, curl_off_t) {
    auto* progressData = static_cast<ProgressData*>(progressDataPtr);

    if (total > 0) {
        progressData->totalSize = static_cast<double>(total);
        progressData->downloaded = static_cast<double>(now);
        // Call the callback to report progress
        progressData->progressCallback(progressData->currentUrl, progressData->downloaded, progressData->totalSize, progressData->isRunning);
    }

    return 0; // Return 0 to indicate success
}

// Function to check if URL is valid and reachable
bool DownloaderService::checkUrl(const std::string& url) {
    CURL* curl;
    CURLcode res;
    bool isValid = false;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L); // Perform a HEAD request
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            isValid = true;
        }
        curl_easy_cleanup(curl);
    }
    return isValid;
}

// Function to download an individual file
bool DownloaderService::downloadFile(
    const std::string& url, 
    const std::string& outputPath, 
    ProgressData& progressData) {

    CURL* curl;
    CURLcode res;
    FILE* file;

    curl = curl_easy_init();
    if (curl) {
        file = fopen(outputPath.c_str(), "wb");
        if (!file) {
            std::cerr << "Error: Could not open file for writing: " << outputPath << std::endl;
            return false;
        }

        // Set URL and file output
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        // Set progress data
        progressData.currentUrl = url;
        progressData.downloaded = 0.0;
        progressData.totalSize = 0.0;

        // Enable progress function
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progressFunction);
        curl_easy_setopt(curl, CURLOPT_XFERINFODATA, &progressData); // Pass progress data

        // Start the file download
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Download failed: " << curl_easy_strerror(res) << " for URL: " << url << std::endl;
            fclose(file);
            curl_easy_cleanup(curl);
            return false;
        }

        // Clean up
        fclose(file);
        curl_easy_cleanup(curl);
        return true;
    }

    return false;
}

// Form the full output path for a given file
std::string DownloaderService::getOutputFilePath(const std::string& directory, const std::string& filename) {
    return directory + "/" + filename;
}

// Main function to handle multiple file downloads
void DownloaderService::downloadFiles(
    const std::string& directory, 
    const std::vector<std::string>& urls, 
    const std::vector<std::string>& filenames, 
    std::function<void(const std::string&, double, double, bool)> progressCallback) {

    ProgressData progressData;
    progressData.progressCallback = progressCallback;
    progressData.isRunning = true;

    for (size_t i = 0; i < urls.size(); ++i) {
        const std::string& url = urls[i];
        const std::string& filename = filenames[i];

        // Check if the URL is valid
        if (!checkUrl(url)) {
            std::cerr << "Error: Invalid or unreachable URL: " << url << std::endl;
            continue; // Skip to the next URL
        }

        // Get the full path for the output file
        std::string outputPath = getOutputFilePath(directory, filename);

        // Download the file
        if (!downloadFile(url, outputPath, progressData)) {
            std::cerr << "Error: Failed to download file from: " << url << std::endl;
        }
    }

    // Signal that all downloads are finished
    progressData.isRunning = false;
    progressCallback("", 0, 0, progressData.isRunning);
}
