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
import net.spydroid.common.remote.network.daos.MultimediaDevicesDao
import net.spydroid.common.remote.network.models.MultimediaDevices

class MultimediaDevicesDaoHandler: MultimediaDevicesDao {

    private val TAG = "PRUBA_INSERT"

    override suspend fun getAllMultimedia(): List<MultimediaDevices> =
        try {
            val response = apiService.getMultimedia("iygad7618wg8y1f7fgvas71f671").execute()
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

    override suspend fun getSpecificMultimedia(alias: String): List<MultimediaDevices> =
        try {
            val response = apiService.getSpecificMultimedia("iygad7618wg8y1f7fgvas71f671", alias).execute()
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

    override suspend fun insertMultimedia(multimedia: MultimediaDevices) {
        try {
            val response = apiService.createMultimedia(
                accessToken = "iygad7618wg8y1f7fgvas71f671",
                alias = multimedia.alias,
                routeFile = multimedia.routeFile,
                type = multimedia.type
            ).execute()
            if (response.isSuccessful){
                Log.i(TAG, "MULTIMEDIA INSERTADO EN LA BASE DE DATOS!")
            }
        } catch (e: Exception) {
            Log.e(TAG, "ERROR INSERTANDO MULTIMEDIA: ${e.message} ")
        }
    }

    override suspend fun deleteMultimedia(multimedia: MultimediaDevices) {
        TODO("Not yet implemented")
    }

    override suspend fun updateMultimedia(multimedia: MultimediaDevices) {
        TODO("Not yet implemented")
    }
}