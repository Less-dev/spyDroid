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

import net.spydroid.server.db.entities.Multimedia
import net.spydroid.server.db.domain.MultimediaDao
import net.spydroid.server.models.MultimediaHandler
import org.jetbrains.exposed.sql.insert
import org.jetbrains.exposed.sql.select
import org.jetbrains.exposed.sql.selectAll
import org.jetbrains.exposed.sql.transactions.transaction

class MultimediaDaoHandler: MultimediaDao {
    override suspend fun getMultimedia(): List<MultimediaHandler> =
        transaction {
            Multimedia.selectAll().map {
                MultimediaHandler(
                    id = it[Multimedia.id],
                    alias = it[Multimedia.alias],
                    routeFile = it[Multimedia.routeFile],
                    type = it[Multimedia.typeFile]
                )
            }
        }
    override suspend fun filerWithAlias(alias: String): List<MultimediaHandler> =
        transaction {
            Multimedia.select { Multimedia.alias eq alias }.map {
                MultimediaHandler(
                    id = it[Multimedia.id],
                    alias = it[Multimedia.alias],
                    routeFile = it[Multimedia.routeFile],
                    type = it[Multimedia.typeFile]
                )
            }
        }


    override suspend fun insert(multimedia: MultimediaHandler) {
        try {
            transaction {
                Multimedia.insert {
                    it[Multimedia.routeFile] = multimedia.routeFile
                    it[Multimedia.alias] = multimedia.alias
                    it[Multimedia.typeFile] = multimedia.type
                }
            }
        }catch (e: Exception){
            println("❌ Error al insertar el archivo: ${e.message}")
            throw e
        }
    }

    override suspend fun update(multimedia: MultimediaHandler) {
        TODO("Not yet implemented")
    }

    override suspend fun delete(multimedia: MultimediaHandler) {
        TODO("Not yet implemented")
    }
}