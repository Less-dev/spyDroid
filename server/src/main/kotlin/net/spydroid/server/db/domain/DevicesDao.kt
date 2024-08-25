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

package net.spydroid.server.db.domain

import net.spydroid.server.db.entities.Devices
import net.spydroid.server.models.DeviceHandler

interface DevicesDao {
    suspend fun getALlDevices(): List<DeviceHandler>
    suspend fun filerWithAlias(alias: String): List<DeviceHandler>
    suspend fun insert(device: DeviceHandler)
    suspend fun update(device: Devices)
    suspend fun delete(device: Devices)
}