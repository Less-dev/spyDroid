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
#include "string"
#include "remote/domain/DevicesRepository.h"
#include "remote/models/DevicesHandler.h"

int main() {

    DevicesRepositoryImp devicesRepository;
    std::vector<DevicesHandler> devices = devicesRepository.getDevices();


    for (const auto& device : devices) {
        std::cout <<
         "ID: " <<
          device.id <<
           ", Alias: " <<
            device.alias <<
             ", Name: " <<
              device.name <<
               std::endl;
    }

    // Obtener un dispositivo específico
    std::string alias = "ALIAS_3";
    std::vector<DevicesHandler> device = devicesRepository.getDevice(alias);
    std::cout << std::string(40, '-') << std::endl;

    for (const auto& device : device) {
        std::cout << 
        "ID: " <<
         device.id <<
          ", Alias: " <<
           device.alias <<
            ", Name: " <<
             device.name <<
              std::endl;
    }
    return 0;
}
