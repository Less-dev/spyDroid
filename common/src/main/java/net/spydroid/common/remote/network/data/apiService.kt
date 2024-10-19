package net.spydroid.common.remote.network.data

import net.spydroid.common.remote.network.api.ApiService
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory


private val retrofit = Retrofit.Builder()
    .baseUrl("http://192.168.101.5:8080/")
    .addConverterFactory(GsonConverterFactory.create())
    .build()

val apiService = retrofit.create(ApiService::class.java)