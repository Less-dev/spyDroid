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

import net.spydroid.server.db.domain.SmsDao
import net.spydroid.server.domain.SmsRepository
import net.spydroid.server.models.SmsHandler
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject

class SmsRepositoryHandler: SmsRepository, KoinComponent {

    val smsDao: SmsDao by inject()

    override suspend fun getSms(): List<SmsHandler> =
        smsDao.getSms()

    override suspend fun filerWithAlias(alias: String): List<SmsHandler> =
        smsDao.filerWithAlias(alias)

    override suspend fun insert(sms: SmsHandler) =
        smsDao.insert(sms)

    override suspend fun update(sms: SmsHandler) =
        smsDao.update(sms)

    override suspend fun delete(sms: SmsHandler) =
        smsDao.delete(sms)
}