#ifndef DEVICES_REPOSITORY_H
#define DEVICES_REPOSITORY_H

#include <vector>
#include <memory>
#include "../network/models/Devices.h"
#include "../network/api/ApiService.h"
#include "../network/daos/DevicesDao.h"
#include "../models/DevicesHandler.h"

class DevicesRepository {
public:
    virtual ~DevicesRepository() = default;
    // Método que retorna todos los dispositivos
    virtual std::vector<DevicesHandler> getDevices() const = 0;

    // Método que retorna un dispositivo basado en un alias
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
