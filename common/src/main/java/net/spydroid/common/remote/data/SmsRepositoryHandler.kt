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

package net.spydroid.common.remote.data

import net.spydroid.common.remote.domain.SmsRepository
import net.spydroid.common.remote.network.daos.SmsDevicesDao
import net.spydroid.common.remote.network.models.SmsDevices
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject

class SmsRepositoryHandler: SmsRepository, KoinComponent {

    private val smsDevicesDao: SmsDevicesDao by inject()

    override suspend fun getAllSms(): List<SmsDevices>  =
        smsDevicesDao.getAllSms()

    override suspend fun getSms(alias: String): List<SmsDevices> =
        smsDevicesDao.getSpecificSms(alias)

    override suspend fun insertSms(sms: SmsDevices) =
        smsDevicesDao.insertSms(sms)

    override suspend fun deleteSms(sms: SmsDevices) =
        smsDevicesDao.deleteSms(sms)

    override suspend fun updateSms(sms: SmsDevices) =
        smsDevicesDao.updateSms(sms)
}