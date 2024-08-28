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

package net.spydroid.common.remote.data

import net.spydroid.common.remote.network.models.Devices
import net.spydroid.common.remote.domain.DevicesRepository
import net.spydroid.common.remote.network.daos.DevicesDao
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject

class DevicesRepositoryHandler: DevicesRepository, KoinComponent {

    private val devicesDao: DevicesDao by inject()

    override suspend fun getAllDevices(): List<Devices> =
        devicesDao.getAllDevices()

    override suspend fun getDevice(alias: String): List<Devices>  =
        devicesDao.getSpecificDevice(alias)

    override suspend fun insertDevice(device: Devices) =
        devicesDao.insertDevice(device)

    override suspend fun deleteDevice(device: Devices) =
        devicesDao.deleteDevice(device)

    override suspend fun updateDevice(device: Devices) =
        devicesDao.updateDevice(device)
}