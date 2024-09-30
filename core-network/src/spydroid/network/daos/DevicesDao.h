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

#ifndef DEVICES_DAO_H
#define DEVICES_DAO_H

#include <string>
#include <vector>
#include "../../../../../core-data/src/spydroid/data/models/DevicesHandler.h"
#include "../api/ApiService.h"

class DevicesDao {
public:
    virtual ~DevicesDao() = default;

    virtual std::vector<DevicesHandler> getDevices() const = 0;
    virtual std::vector<DevicesHandler> getDevice(const std::string& alias) const = 0;
};

class DevicesDaoImpl : public DevicesDao {
public:
    DevicesDaoImpl() = default;

    std::vector<DevicesHandler> getDevices() const override;
    std::vector<DevicesHandler> getDevice(const std::string& alias) const override;

private:
    ApiService apiService;
};

#endif // DEVICES_DAO_H