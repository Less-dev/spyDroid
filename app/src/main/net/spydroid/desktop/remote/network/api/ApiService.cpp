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
#include "../models/Devices.h"
#include <jsoncpp/json/json.h>
#include "ApiService.h"


size_t WriteCallback(void* contents,
  size_t size,
  size_t nmemb,
  void* userp
) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
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