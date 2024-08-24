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
import net.spydroid.server.models.DeviceHandler
import org.jetbrains.exposed.sql.insert
import org.jetbrains.exposed.sql.select
import org.jetbrains.exposed.sql.selectAll
import org.jetbrains.exposed.sql.transactions.transaction

class DevicesRepositoryHandler : DevicesRepository {
    override suspend fun getALlDevices(): List<DeviceHandler> =
        transaction {
            Devices.selectAll().map {
                DeviceHandler(
                    id = it[Devices.id],
                    name = it[Devices.name],
                    alias = it[Devices.alias],
                )
            }
        }

    override suspend fun filerDevicesWithAlias(alias: String): List<DeviceHandler> =
        transaction {
            Devices.select { Devices.alias eq alias }
                .map {
                    DeviceHandler(
                        id = it[Devices.id],
                        name = it[Devices.name],
                        alias = it[Devices.alias],
                    )
                }
        }


    override suspend fun insertDevice(device: DeviceHandler) {
        try {
            transaction {
                Devices.insert {
                    it[Devices.name] = device.name
                    it[Devices.alias] = device.alias
                }
            }

            println("👤 Usuario ${device.name} insertado en la base de datos.")
        } catch (e: Exception) {
            println("❌ Error al insertar el dispositivo: ${e.message}")
            throw e
        }
    }

    override suspend fun updateDevice(device: Devices) {
        TODO("Not yet implemented")
    }

    override suspend fun deleteDevice(device: Devices) {
        TODO("Not yet implemented")
    }
}