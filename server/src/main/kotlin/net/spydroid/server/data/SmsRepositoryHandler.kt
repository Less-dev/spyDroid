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

import net.spydroid.server.db.entities.Sms
import net.spydroid.server.domain.SmsRepository
import net.spydroid.server.models.SmsHandler
import org.jetbrains.exposed.sql.insert
import org.jetbrains.exposed.sql.select
import org.jetbrains.exposed.sql.selectAll
import org.jetbrains.exposed.sql.transactions.transaction

class SmsRepositoryHandler : SmsRepository {
    override suspend fun getSms(): List<SmsHandler> =
        transaction {
            Sms.selectAll().map {
                SmsHandler(
                    id = it[Sms.id],
                    sms = it[Sms.sms]
                )
            }
        }

    override suspend fun getSpecificSms(sms: SmsHandler): SmsHandler? =
        transaction {
            Sms.select { Sms.id eq (sms.id ?: 1) }.map {
                SmsHandler(
                    id = it[Sms.id],
                    sms = it[Sms.sms]
                )
            }
                .singleOrNull()
        }

    override suspend fun insertSms(sms: SmsHandler) {
        try {
            transaction {
                Sms.insert {
                    it[Sms.sms] = sms.sms
                }
            }
        }catch (e: Exception) {
            println("❌ Error al insertar el dispositivo: ${e.message}")
            throw e
        }
    }

    override suspend fun updateSms(sms: SmsHandler) {
        TODO("Not yet implemented")
    }

    override suspend fun deleteSms(sms: SmsHandler) {
        TODO("Not yet implemented")
    }
}