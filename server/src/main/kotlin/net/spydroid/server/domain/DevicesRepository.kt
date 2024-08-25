package net.spydroid.server.domain

import net.spydroid.server.models.DeviceHandler

interface DevicesRepository {
    suspend fun getALlDevices(): List<DeviceHandler>
    suspend fun filerWithAlias(alias: String): List<DeviceHandler>
    suspend fun insert(device: DeviceHandler)
    suspend fun update(device: DeviceHandler)
    suspend fun delete(device: DeviceHandler)
}