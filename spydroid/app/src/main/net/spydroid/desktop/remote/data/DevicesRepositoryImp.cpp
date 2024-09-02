#include "../domain/DevicesRepository.h"
#include "../models/DevicesHandler.h"

std::vector<DevicesHandler> DevicesRepositoryImp::getDevices() const {
    std::vector<Devices> devices = devicesDao.getDevices();
    std::vector<DevicesHandler> devicesHandlers;
    for (const Devices& device : devices) {
        DevicesHandler handler;
        handler.id = device.id;
        handler.alias = device.alias;
        handler.name = device.name;
        devicesHandlers.push_back(handler);
    }

    return devicesHandlers;
}


std::vector<DevicesHandler> DevicesRepositoryImp::getDevice(const std::string& alias) const {
    std::vector<Devices> device = devicesDao.getDevice(alias);
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