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

package net.spydroid.server.db.data

import net.spydroid.server.db.entities.Info
import net.spydroid.server.db.domain.InfoDao
import net.spydroid.server.models.InfoHandler
import org.jetbrains.exposed.sql.insert
import org.jetbrains.exposed.sql.select
import org.jetbrains.exposed.sql.selectAll
import org.jetbrains.exposed.sql.transactions.transaction
import org.jetbrains.exposed.sql.update

class InfoDaoHandler : InfoDao {
    override suspend fun getInfo(): List<InfoHandler> =
        transaction {
            Info.selectAll().map {

                InfoHandler(
                    id = it[Info.id],
                    alias = it[Info.alias],
                    ip_address_public = it[Info.ip_address_public],
                    ip_address_private = it[Info.ip_address_private],
                    location = it[Info.location],
                )
            }
        }

    override suspend fun filerWithAlias(alias: String): List<InfoHandler> =
        transaction {
            Info.select { Info.alias eq alias }
                .map {
                    InfoHandler(
                        id = it[Info.id],
                        alias = it[Info.alias],
                        ip_address_public = it[Info.ip_address_public],
                        ip_address_private = it[Info.ip_address_private],
                        location = it[Info.location],
                    )
                }
        }

    override suspend fun insert(info: InfoHandler) {
        try {
            transaction {
                Info.insert {
                    it[Info.alias] = info.alias
                    it[Info.ip_address_public] = info.ip_address_public
                    it[Info.ip_address_private] = info.ip_address_private
                    it[Info.location] = info.location
                }
            }
            println("Información subida correctamente a la base de datos.")
        } catch (e: Exception) {
            println("❌ Error al insertar la información ${e.message}")
            throw e
        }
    }

    override suspend fun update(info: InfoHandler) =
        try {
            transaction {
                val updatedRows = Info.update({ Info.alias eq info.alias }) {
                    it[alias] = info.alias
                    it[ip_address_public] = info.ip_address_public
                    it[ip_address_private] = info.ip_address_private
                    it[location] = info.location
                }

                if (updatedRows == 0) {
                    println("❌ No se encontró una fila informacion con el alias ${info.alias} para actualizar.")
                    throw Exception("Device not found")
                } else {
                    println("🔄 Info actualizada correctamente.")
                }
            }
        } catch (e: Exception) {
            throw e
        }

    override suspend fun delete(info: InfoHandler) {
        TODO("Not yet implemented")
    }
}
