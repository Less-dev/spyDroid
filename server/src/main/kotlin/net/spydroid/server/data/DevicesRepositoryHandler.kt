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

package net.spydroid.server.data

import net.spydroid.server.db.entities.Devices
import net.spydroid.server.domain.DevicesRepository

class DevicesRepositoryHandler: DevicesRepository {
    override suspend fun getDevices(): List<Devices> {
        TODO("Not yet implemented")
    }

    override suspend fun getSpecificDevice(device: Devices): Devices {
        TODO("Not yet implemented")
    }

    override suspend fun insertDevice(device: Devices) {
        TODO("Not yet implemented")
    }

    override suspend fun updateDevice(device: Devices) {
        TODO("Not yet implemented")
    }

    override suspend fun deleteDevice(device: Devices) {
        TODO("Not yet implemented")
    }
}