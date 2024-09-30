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

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <dirent.h>
#include <thread>
#include <jsoncpp/json/json.h>
#include "ApiService.h"
#include "../models/Devices.h"


size_t WriteCallback(void* contents,
  size_t size,
  size_t nmemb,
  void* userp
) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

size_t WriteFileCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    FILE* fp = (FILE*)userp;
    size_t written = fwrite(contents, size, nmemb, fp);
    return written;
}

bool createDirectory(const std::string& path) {
    struct stat st = {0};
    if (stat(path.c_str(), &st) == -1) {
        if (mkdir(path.c_str(), 0777) != 0) {
            std::cerr << "Error creating directory " << path << std::endl;
            return false;
        }
    }
    return true;
}


void removeFileOrDirectory(const std::string& path) {
    if (remove(path.c_str()) != 0) {
        std::cerr << "Error delete it: " << path << std::endl;
    }
}

bool directoryIsEmpty(const std::string& path) {
    int n = 0;
    struct dirent *d;
    DIR *dir = opendir(path.c_str());
    if (dir == NULL) return true;
    while ((d = readdir(dir)) != NULL) {
        if (++n > 2) break; // Más de 2 entradas significa que no está vacío
    }
    closedir(dir);
    return n <= 2;
}

bool unzipFile(const std::string& zipFilePath, const std::string& extractToPath) {
    std::string command = "unzip -q " + zipFilePath + " -d " + extractToPath;
    int result = std::system(command.c_str());
    return result == 0;
}

std::vector<Devices> ApiService::getDevices() const {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::vector<Devices> devices;
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/devices?access_token=iygad7618wg8y1f7fgvas71f671");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        // Get info
        res = curl_easy_perform(curl);
    
        if(res != CURLE_OK) {
            fprintf(stderr, "failed getting resource: %s\n", curl_easy_strerror(res));
        } else {

            // Parser Json
            Json::Reader reader;
            Json::Value jsonData;
            if (reader.parse(readBuffer, jsonData)) {
                for (const auto& device : jsonData) {
                    Devices _device;
                    _device.id = device["id"].asInt();
                    _device.alias = device["alias"].asString();
                    _device.name = device["name"].asString();
                    devices.push_back(_device);
                }
            } else {
                std::cerr << "Error al parsear JSON" << std::endl;
            }
        }
        curl_easy_cleanup(curl);
    }
    return devices;
}   



std::vector<Devices> ApiService::getDevice(const std::string& alias) const {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::vector<Devices> devices;
    curl = curl_easy_init();

    if(curl) {
        std::string url = "http://localhost:8080/devices?access_token=iygad7618wg8y1f7fgvas71f671&search=" + alias;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        // Get info
        res = curl_easy_perform(curl);
    
        if(res != CURLE_OK) {
            fprintf(stderr, "failed getting resource: %s\n", curl_easy_strerror(res));
        } else {

            // Parser Json
            Json::Reader reader;
            Json::Value jsonData;
            if (reader.parse(readBuffer, jsonData)) {
                for (const auto& device : jsonData) {
                    Devices _device;
                    _device.id = device["id"].asInt();
                    _device.alias = device["alias"].asString();
                    _device.name = device["name"].asString();
                    _device.ip_address_public = device["ip_address_public"].asString();
                    _device.ip_address_private = device["ip_address_private"].asString();
                    _device.location = device["location"].asString();
                    devices.push_back(_device);
                }
            } else {
                std::cerr << "Error al parsear JSON" << std::endl;
            }
        }
        curl_easy_cleanup(curl);
    }
    return devices;
}


std::vector<Info> ApiService::getInfo(const std::string& alias) const {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::vector<Info> infor;
    curl = curl_easy_init();

    if(curl) {
        std::string url = "http://localhost:8080/info?access_token=iygad7618wg8y1f7fgvas71f671&search=" + alias;
        //std::cout << url << std::endl;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        // Get info
        res = curl_easy_perform(curl);
    
        if(res != CURLE_OK) {
            fprintf(stderr, "failed getting resource: %s\n", curl_easy_strerror(res));
        } else {

            // Parser Json
            Json::Reader reader;
            Json::Value jsonData;
            if (reader.parse(readBuffer, jsonData)) {
                for (const auto& info : jsonData) {
                    Info _info;
                    _info.id = info["id"].asInt();
                    _info.alias = info["alias"].asString();
                    _info.vnc_password = info["vnc_password"].asString();
                    _info.vnc_port = info["vnc_port"].asString();
                    infor.push_back(_info);
                }
            } else {
                std::cerr << "Error al parsear JSON" << std::endl;
            }
        }
        curl_easy_cleanup(curl);
    }
    return infor;
}

std::vector<Multimedia> ApiService::getMultimeida (const std::string& alias) const {

    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::vector<Multimedia> multir;
    curl = curl_easy_init();

    if(curl) {
        std::string url = "http://localhost:8080/multimedia?access_token=iygad7618wg8y1f7fgvas71f671&search=" + alias;
        //std::cout << url << std::endl;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        // Get info
        res = curl_easy_perform(curl);
    
        if(res != CURLE_OK) {
            fprintf(stderr, "failed getting resource: %s\n", curl_easy_strerror(res));
        } else {

            // Parser Json
            Json::Reader reader;
            Json::Value jsonData;
            if (reader.parse(readBuffer, jsonData)) {
                for (const auto& multimedia : jsonData) {
                    Multimedia _multimedia;
                    _multimedia.id = multimedia["id"].asInt();
                    _multimedia.alias = multimedia["alias"].asString();
                    _multimedia.routeFile = multimedia["routeFile"].asString();
                    _multimedia.type = multimedia["type"].asString();
                    multir.push_back(_multimedia);
                }
            } else {
                std::cerr << "Error al parsear JSON" << std::endl;
            }
        }
        curl_easy_cleanup(curl);
    }
    return multir;
}

std::vector<Sms> ApiService::getSms(const std::string& alias) const {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::vector<Sms> smsr;
    curl = curl_easy_init();

    if(curl) {
        std::string url = "http://localhost:8080/sms?access_token=iygad7618wg8y1f7fgvas71f671&search=" + alias;
        //std::cout << url << std::endl;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        // Get info
        res = curl_easy_perform(curl);
    
        if(res != CURLE_OK) {
            fprintf(stderr, "failed getting resource: %s\n", curl_easy_strerror(res));
        } else {

            // Parser Json
            Json::Reader reader;
            Json::Value jsonData;
            if (reader.parse(readBuffer, jsonData)) {
                for (const auto& sms : jsonData) {
                    Sms _sms;
                    _sms.id = sms["id"].asInt();
                    _sms.alias = sms["alias"].asString();
                    _sms.sms = sms["sms"].asString();
                    smsr.push_back(_sms);
                }
            } else {
                std::cerr << "Error al parsear JSON" << std::endl;
            }
        }
        curl_easy_cleanup(curl);
    }
    return smsr;
}


// IMAGES
void ApiService::getImages(const std::string& alias) const {
    std::thread([this, alias]() {
        CURL* curl;
        CURLcode res;
        std::string url = "http://localhost:8080/download/image?alias=" + alias + "&access_token=" + "iygad7618wg8y1f7fgvas71f671";

        std::string baseDir = "uploads/images/" + alias;
        std::string zipFilePath = baseDir + "/images.zip";


        if (!createDirectory("uploads") || !createDirectory("uploads/images") || !createDirectory(baseDir)) {
            std::cerr << "Fail creating directories" << std::endl;
            return;
        }

        FILE* fp = fopen(zipFilePath.c_str(), "wb");
        if (!fp) {
            std::cerr << "Error al abrir el archivo para escribir: " << zipFilePath << std::endl;
            return;
        }

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFileCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "Fail solitude curl" << curl_easy_strerror(res) << std::endl;
                fclose(fp);
                curl_easy_cleanup(curl);
                removeFileOrDirectory(baseDir); // Delete directory if this is fail
                return;
            }

            fclose(fp);
            curl_easy_cleanup(curl);
        } else {
            std::cerr << "Fail starting curl" << std::endl;
            return;
        }

        std::ifstream zipFile(zipFilePath, std::ifstream::ate | std::ifstream::binary);
        if (zipFile.tellg() == 0) { // If size is it equal to 0
            std::cerr << "File ZIP is empty" << std::endl;
            zipFile.close();
            removeFileOrDirectory(zipFilePath); // Delete zip file
            removeFileOrDirectory(baseDir);
            return;
        }
        zipFile.close();

        if (!unzipFile(zipFilePath, baseDir)) {
            std::cerr << "Fail unziping file ZIP" << std::endl;
            removeFileOrDirectory(zipFilePath); 
            removeFileOrDirectory(baseDir); 
            return;
        }

        removeFileOrDirectory(zipFilePath);

        if (directoryIsEmpty(baseDir)) {
            std::cerr << "Directory images  empy va, delete..." << std::endl;
            removeFileOrDirectory(baseDir);
            return;
        }

        std::cout << "Images downlaod sucessfully in: " << baseDir << std::endl;
    }).detach();
}


// VIDEOS
void ApiService::getVideos(const std::string& alias) const {
    std::thread([this, alias]() {
        CURL* curl;
        CURLcode res;
        std::string url = "http://localhost:8080/download/video?alias=" + alias + "&access_token=" + "iygad7618wg8y1f7fgvas71f671";

        std::string baseDir = "uploads/videos/" + alias;
        std::string zipFilePath = baseDir + "/videos.zip";

        if (!createDirectory("uploads") || !createDirectory("uploads/videos") || !createDirectory(baseDir)) {
            std::cerr << "Error al crear directorios" << std::endl;
            return;
        }

        FILE* fp = fopen(zipFilePath.c_str(), "wb");
        if (!fp) {
            std::cerr << "Error al abrir el archivo para escribir: " << zipFilePath << std::endl;
            return;
        }

        // Starting curl
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFileCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "Error en la solicitud cURL: " << curl_easy_strerror(res) << std::endl;
                fclose(fp);
                curl_easy_cleanup(curl);
                removeFileOrDirectory(baseDir); // Delete directory of the download
                return;
            }

            fclose(fp);
            curl_easy_cleanup(curl);
        } else {
            std::cerr << "Error al inicializar cURL." << std::endl;
            return;
        }

        std::ifstream zipFile(zipFilePath, std::ifstream::ate | std::ifstream::binary);
        if (zipFile.tellg() == 0) {
            std::cerr << "El archivo ZIP está vacío." << std::endl;
            zipFile.close();
            removeFileOrDirectory(zipFilePath);
            removeFileOrDirectory(baseDir);
            return;
        }
        zipFile.close();

        if (!unzipFile(zipFilePath, baseDir)) {
            std::cerr << "Error al descomprimir el archivo ZIP." << std::endl;
            removeFileOrDirectory(zipFilePath);
            removeFileOrDirectory(baseDir);
            return;
        }

        removeFileOrDirectory(zipFilePath);

        if (directoryIsEmpty(baseDir)) {
            std::cerr << "Directorio de audios vacío, eliminando..." << std::endl;
            removeFileOrDirectory(baseDir);
            return;
        }

        std::cout << "Videos download sucessfully in: " << baseDir << std::endl;
    }).detach();
}


// DOCUMENTS
void ApiService::getDocuments(const std::string& alias) const {

    std::thread([this, alias]() {
        CURL* curl;
        CURLcode res;
        std::string url = "http://localhost:8080/download/document?alias=" + alias + "&access_token=" + "iygad7618wg8y1f7fgvas71f671";

        std::string baseDir = "uploads/documents/" + alias;
        std::string zipFilePath = baseDir + "/documents.zip";

        if (!createDirectory("uploads") || !createDirectory("uploads/documents") || !createDirectory(baseDir)) {
            std::cerr << "Error al crear directorios" << std::endl;
            return;
        }

        FILE* fp = fopen(zipFilePath.c_str(), "wb");
        if (!fp) {
            std::cerr << "Error al abrir el archivo para escribir: " << zipFilePath << std::endl;
            return;
        }

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFileCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "Error en la solicitud cURL: " << curl_easy_strerror(res) << std::endl;
                fclose(fp);
                curl_easy_cleanup(curl);
                removeFileOrDirectory(baseDir);
                return;
            }

            fclose(fp);
            curl_easy_cleanup(curl);
        } else {
            std::cerr << "File starting curl" << std::endl;
            return;
        }

        std::ifstream zipFile(zipFilePath, std::ifstream::ate | std::ifstream::binary);
        if (zipFile.tellg() == 0) {
            std::cerr << "File ZIP is empty" << std::endl;
            zipFile.close();
            removeFileOrDirectory(zipFilePath);
            removeFileOrDirectory(baseDir); 
            return;
        }
        zipFile.close();

        // Unziping file ZIP
        if (!unzipFile(zipFilePath, baseDir)) {
            std::cerr << "Error unziping file ZIP" << std::endl;
            removeFileOrDirectory(zipFilePath);
            removeFileOrDirectory(baseDir);
            return;
        }

        // Delete file Zip
        removeFileOrDirectory(zipFilePath);

        if (directoryIsEmpty(baseDir)) {
            std::cerr << "Directory Documents is empty, delete..." << std::endl;
            removeFileOrDirectory(baseDir);
            return;
        }

        std::cout << "Documents download sucessfuly in: " << baseDir << std::endl;
    }).detach();
}


// AUDIOS
void ApiService::getAudios(const std::string& alias) const {

    std::thread([this, alias]() {
        CURL* curl;
        CURLcode res;
        std::string url = "http://localhost:8080/download/audio?alias=" + alias + "&access_token=" + "iygad7618wg8y1f7fgvas71f671";

        std::string baseDir = "uploads/audios/" + alias;
        std::string zipFilePath = baseDir + "/audios.zip";

        if (!createDirectory("uploads") || !createDirectory("uploads/audios") || !createDirectory(baseDir)) {
            std::cerr << "Faile creating directories" << std::endl;
            return;
        }

        FILE* fp = fopen(zipFilePath.c_str(), "wb"); // File ZIP to write
        if (!fp) {
            std::cerr << "Error opening file ZIP: " << zipFilePath << std::endl;
            return;
        }

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFileCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "Error solitude curl: " << curl_easy_strerror(res) << std::endl;
                fclose(fp);
                curl_easy_cleanup(curl);
                removeFileOrDirectory(baseDir); // Delete directory if solitude is fail
                return;
            }

            fclose(fp);
            curl_easy_cleanup(curl);
        } else {
            std::cerr << "Fail starting curl!!" << std::endl;
            return;
        }

        // Verifiy if ZIP file does not empty
        std::ifstream zipFile(zipFilePath, std::ifstream::ate | std::ifstream::binary);
        if (zipFile.tellg() == 0) {
            std::cerr << "File Zip is empty" << std::endl;
            zipFile.close();
            removeFileOrDirectory(zipFilePath); // Delete file ZIP
            removeFileOrDirectory(baseDir); // Delete directory
            return;
        }
        zipFile.close();

        if (!unzipFile(zipFilePath, baseDir)) {
            std::cerr << "Error unzipping ZIP file." << std::endl;
            removeFileOrDirectory(zipFilePath); // Delete file ZIP
            removeFileOrDirectory(baseDir); // Delete directory
            return;
        }

        // Delete ZIP file
        removeFileOrDirectory(zipFilePath);

        // If directory is empty delete
        if (directoryIsEmpty(baseDir)) {
            std::cerr << "Delete audio directory..." << std::endl;
            removeFileOrDirectory(baseDir);
            return;
        }

        std::cout << "Audios download sucessfully in: " << baseDir << std::endl;
    }).detach();
}