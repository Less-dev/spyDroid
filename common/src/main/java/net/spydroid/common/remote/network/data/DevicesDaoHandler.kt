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
import net.spydroid.common.remote.network.daos.DevicesDao
import net.spydroid.common.remote.network.models.Devices
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response

class DevicesDaoHandler : DevicesDao {
    private val TAG = "PRUBA_INSERT"
    override suspend fun getAllDevices(): List<Devices> =
        try {
            val response = apiService.getDevices("iygad7618wg8y1f7fgvas71f671").execute()
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

    override suspend fun getSpecificDevice(alias: String): List<Devices> =
        try {
            val response = apiService.getSpecificDevices("iygad7618wg8y1f7fgvas71f671", alias).execute()
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

    override suspend fun insertDevice(device: Devices) {
        try {
            val response = apiService.createDevice(
                accessToken = "iygad7618wg8y1f7fgvas71f671",
                alias = device.alias,
                name = device.name
            ).execute()
            if (response.isSuccessful){
                Log.i(TAG, "DISPOSITIVO INSERTADO EN LA BASE DE DATOS!")
            }
        } catch (e: Exception) {
            Log.e(TAG, "ERROR INSERTANDO DISPOSITIVO: ${e.message} ")
        }
    }

    override suspend fun deleteDevice(device: Devices) {
        TODO("Not yet implemented")
    }

    override suspend fun updateDevice(device: Devices) {
        TODO("Not yet implemented")
    }
}