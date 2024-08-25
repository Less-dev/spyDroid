package net.spydroid.server.data

import net.spydroid.server.db.domain.DevicesDao
import net.spydroid.server.domain.DevicesRepository
import net.spydroid.server.models.DeviceHandler
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject

class DevicesRepositoryHandler: DevicesRepository, KoinComponent {

    private val devicesDao: DevicesDao by inject()

    override suspend fun getALlDevices(): List<DeviceHandler> =
        devicesDao.getALlDevices()

    override suspend fun filerWithAlias(alias: String): List<DeviceHandler> =
        devicesDao.filerWithAlias(alias)

    override suspend fun insert(device: DeviceHandler) =
        devicesDao.insert(device)

    override suspend fun update(device: DeviceHandler) =
        devicesDao.update(device)

    override suspend fun delete(device: DeviceHandler) =
        devicesDao.delete(device)
}