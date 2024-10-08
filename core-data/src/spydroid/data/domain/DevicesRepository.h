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

#ifndef DEVICES_REPOSITORY_H
#define DEVICES_REPOSITORY_H

#include <vector>
#include <memory>
#include "../../../../../core-network/src/spydroid/network/models/Devices.h"
#include "../../../../../core-network/src/spydroid/network/services/ApiService.h"
#include "../../../../../core-network/src/spydroid/network/daos/DevicesDao.h"
#include "../models/DevicesHandler.h"

class DevicesRepository {
public:
    virtual ~DevicesRepository() = default;

    virtual std::vector<DevicesHandler> getDevices() const = 0;
    
    virtual std::vector<DevicesHandler> getDevice(const std::string& alias) const = 0;
};

class DevicesRepositoryImp: public DevicesRepository {
public:

    DevicesRepositoryImp() = default;

    std::vector<DevicesHandler> getDevices() const override;
    std::vector<DevicesHandler> getDevice(const std::string& alias) const override;

private:
    DevicesDaoImpl devicesDao;
};

#endif // DEVICES_REPOSITORY_H
