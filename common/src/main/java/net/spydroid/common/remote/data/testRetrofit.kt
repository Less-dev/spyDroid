package net.spydroid.common.remote.data

import android.util.Log
import net.spydroid.common.remote.data.api.ApiService
import net.spydroid.common.remote.data.models.Devices
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory


import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response


fun searchDevices()
{
    val retrofit = Retrofit.Builder()
        .baseUrl("http://192.168.100.70:8080/")
        .addConverterFactory(GsonConverterFactory.create())
        .build()

    val apiService = retrofit.create(ApiService::class.java)

    val TAG = "PRUEBA_RETROFIT"
    val call = apiService.getDevices("iygad7618wg8y1f7fgvas71f671")
    call.enqueue(object : Callback<List<Devices>> {
        override fun onResponse(call: Call<List<Devices>>, response: Response<List<Devices>>) {
            if (response.isSuccessful) {
                val devicesList = response.body()
                devicesList?.forEach { device ->
                    Log.d(TAG, "ID: ${device.id}, Alias: ${device.alias}, Name: ${device.name}")
                }
            } else {
                Log.i(TAG, "Error: ${response.code()}")
            }
        }

        override fun onFailure(call: Call<List<Devices>>, t: Throwable) {
            Log.e(TAG,"Failure: ${t.message}")
        }
    })
}