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

#ifndef API_SERVICE_H
#define API_SERVICE_H

#include <cstddef>
#include <string>
#include "../models/Devices.h"
#include <vector>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

class ApiService {
public:
    std::vector<Devices> getDevices() const;
    std::vector<Devices> getDevice(const std::string& alias) const;
};

#endif // API_SERVICE_H