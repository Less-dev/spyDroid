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


size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void ApiService() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/devices?access_token=iygad7618wg8y1f7fgvas71f671");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        // Ejecuta la solicitud
        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            fprintf(stderr, "failed getting resource: %s\n", curl_easy_strerror(res));
        } else {
            // Usando jsoncpp para parsear la respuesta JSON
            Json::Reader reader;
            Json::Value jsonData;
            if (reader.parse(readBuffer, jsonData)) {
                std::vector<Devices> devices;
                for (const auto& device : jsonData) {
                    Devices d;
                    d.id = device["id"].asInt();
                    d.alias = device["alias"].asString();
                    d.name = device["name"].asString();
                    devices.push_back(d);
                }

                // Imprimir los dispositivos
                for (const auto& device : devices) {
                    std::cout << "ID: " << device.id << ", Alias: " << device.alias << ", Name: " << device.name << std::endl;
                }
            } else {
                std::cerr << "Error al parsear JSON" << std::endl;
            }
        }
        
        curl_easy_cleanup(curl);
    }
}