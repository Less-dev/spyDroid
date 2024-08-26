package net.spydroid.common.remote.data.api

import net.spydroid.common.remote.data.models.Devices
import retrofit2.http.GET
import retrofit2.http.Query
import retrofit2.Call

interface ApiService {
    @GET("/devices")
    fun getDevices(@Query("access_token") accessToken: String): Call<List<Devices>>
}