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

#include "../daos/DevicesDao.h"
#include "../../models/DevicesHandler.h"

std::vector<DevicesHandler> DevicesDaoImpl::getDevices() const {
    std::vector<Devices> devices = apiService.getDevices();
    std::vector<DevicesHandler> devicesHandlers;

    // Parser Data Devices to DevicesHandler
    for (const Devices& device : devices) {
        DevicesHandler handler;
        handler.id = device.id;
        handler.alias = device.alias;
        handler.name = device.name;
        devicesHandlers.push_back(handler);
    }

    return devicesHandlers;
}

std::vector<DevicesHandler> DevicesDaoImpl::getDevice(const std::string& alias) const {
    std::vector<Devices> device = apiService.getDevice(alias);
    std::vector<DevicesHandler> devicesHandlers;

    for (const Devices& _device : device) {
        DevicesHandler handler;
        handler.id = _device.id;
        handler.alias = _device.alias;
        handler.name = _device.name;
        devicesHandlers.push_back(handler);
    }

    return devicesHandlers;
}