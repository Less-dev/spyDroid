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

    override suspend fun update(info: Info) {
        TODO("Not yet implemented")
    }

    override suspend fun delete(info: Info) {
        TODO("Not yet implemented")
    }
}