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

package net.spydroid.common.remote.database.data

import net.spydroid.common.remote.database.daos.MultimediaDevicesDao
import net.spydroid.common.remote.database.models.MultimediaDevices

class MultimediaDevicesDaoHandler: MultimediaDevicesDao {
    override suspend fun getAllMultimedia(): List<MultimediaDevices> {
        TODO("Not yet implemented")
    }

    override suspend fun insertMultimedia(multimedia: MultimediaDevices) {
        TODO("Not yet implemented")
    }

    override suspend fun deleteMultimedia(multimedia: MultimediaDevices) {
        TODO("Not yet implemented")
    }

    override suspend fun updateMultimedia(multimedia: MultimediaDevices) {
        TODO("Not yet implemented")
    }
}