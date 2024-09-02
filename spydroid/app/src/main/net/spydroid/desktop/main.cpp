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

#include <FL/Fl.H>
#include "presentation/home.h"


int main(int argc, char **argv) {
    Home home;  // Home Instance
    home.show(); // Show view main
    
    return Fl::run(); // Init fltk
}
 */


#include <iostream>
#include <string>
#include <curl/curl.h>

// Función de callback para manejar la respuesta
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/devices?access_token=iygad7618wg8y1f7fgvas71f671"); // Reemplaza con la URL de tu API
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        // Ejecuta la solicitud
        res = curl_easy_perform(curl);
        
        // Verifica errores
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            std::cout << "Respuesta: " << readBuffer << std::endl;
        }
        
        // Limpia
        curl_easy_cleanup(curl);
    }
    
    return 0;
}
