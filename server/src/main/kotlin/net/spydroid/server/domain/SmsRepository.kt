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

package net.spydroid.server.domain

import net.spydroid.server.models.SmsHandler

interface SmsRepository {
    suspend fun getALlSms(): List<SmsHandler>
    suspend fun filerWithAlias(alias: String): List<SmsHandler>
    suspend fun insert(sms: SmsHandler)
    suspend fun update(sms: SmsHandler)
    suspend fun delete(sms: SmsHandler)
}