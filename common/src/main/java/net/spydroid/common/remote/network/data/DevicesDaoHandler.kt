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

package net.spydroid.common.remote.network.data

import net.spydroid.common.remote.network.daos.DevicesDao
import net.spydroid.common.remote.network.models.Devices

class DevicesDaoHandler: DevicesDao {
    override suspend fun getAllDevices(): List<Devices> {
        TODO("Not yet implemented")
    }

    override suspend fun insertDevice(device: Devices) {
        TODO("Not yet implemented")
    }

    override suspend fun deleteDevice(device: Devices) {
        TODO("Not yet implemented")
    }

    override suspend fun updateDevice(device: Devices) {
        TODO("Not yet implemented")
    }
}