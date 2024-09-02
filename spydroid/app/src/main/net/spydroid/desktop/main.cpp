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


#include "remote/network/api/ApiService.h"
#include <iostream>
#include "remote/network/models/Devices.h"
#include "string"

int main() {

    ApiService apiService;
    
    std::string alias = "ALL";

    std::vector<Devices> devices = apiService.getDevice(alias);

    for (const auto& device : devices) {
        std::cout << "ID: " << device.id << ", Alias: " << device.alias << ", Name: " << device.name << std::endl;
    }
    return 0;
}
