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
import net.spydroid.common.remote.network.daos.InfoDevicesDao
import net.spydroid.common.remote.network.models.InfoDevices

class InfoDevicesDaoHandler : InfoDevicesDao {

    private val TAG = "PRUBA_INSERT"

    override suspend fun getAllInfo(): List<InfoDevices> =
        try {
            val response = apiService.getInfo("iygad7618wg8y1f7fgvas71f671").execute()
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

    override suspend fun insertInfo(info: InfoDevices) {
        try {
            val response = apiService.createInfo(
                accessToken = "iygad7618wg8y1f7fgvas71f671",
                alias = info.alias,
                ipPublic = info.ip_address_public,
                ipPrivate = info.ip_address_private,
                location = info.location
            ).execute()
            if (response.isSuccessful) {
                Log.i(TAG, "INFORMACIÓN INSERTADO EN LA BASE DE DATOS!")
            }
        } catch (e: Exception) {
            Log.e(TAG, "ERROR INSERTANDO INFORMACIÓN: ${e.message} ")
        }
    }

    override suspend fun deleteInfo(info: InfoDevices) {
        TODO("Not yet implemented")
    }

    override suspend fun updateInfo(info: InfoDevices) {
        TODO("Not yet implemented")
    }
}