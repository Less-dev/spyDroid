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

package net.spydroid.core.data.common

import androidx.compose.runtime.compositionLocalOf
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.launch
import net.spydroid.core.data.common.GLOBAL_STATES_PERMISSIONS
import net.spydroid.core.data.domain.PreferenceManagerRepository
import net.spydroid.core.data.models.CurrentLocation
import java.net.InetAddress
import java.net.NetworkInterface
import javax.inject.Inject


val LocalGlobalViewModel =
    compositionLocalOf<GlobalViewModel> { error("No GlobalViewModel found!") }

private object KEYS {
    const val VNC_SERVER = "state_vnc_server"
    const val LOCATION = "state_location"
    const val CAMERA = "state_camera"
    const val VIDEO = "state_video"
    const val TEXT_SMS = "state_text_sms"
    const val CALLS = "state_calls"
    const val MULTIMEDIA = "state_multimedia"
    const val CONTACTS = "state_contacts"
    const val INTERNET = "state_internet"
}


@HiltViewModel
class GlobalViewModel @Inject constructor(
    private val preferenceManagerRepository: PreferenceManagerRepository
) : ViewModel() {

    private val _stateVncServer =
        MutableStateFlow(preferenceManagerRepository.getStateVnc(KEYS.VNC_SERVER))
    val stateVncServer: StateFlow<Boolean> = _stateVncServer

    private val _privateIpAddress = MutableStateFlow("")
    val privateIpAddress: StateFlow<String> = _privateIpAddress


    private val _currentLocation = MutableStateFlow(CurrentLocation())
    val currentLocation: StateFlow<CurrentLocation> = _currentLocation

    //permissions
    private val _stateLocation =
        MutableStateFlow(preferenceManagerRepository.getStatePermission(key = KEYS.LOCATION))
    val stateLocation: StateFlow<String> = _stateLocation

    private val _stateInternet =
        MutableStateFlow(preferenceManagerRepository.getStatePermission(key = KEYS.INTERNET))
    val stateInternet: StateFlow<String> = _stateInternet

    private val _stateCamera =
        MutableStateFlow(preferenceManagerRepository.getStatePermission(key = KEYS.CAMERA))
    val stateCamera: StateFlow<String> = _stateCamera

    private val _stateVideo =
        MutableStateFlow(preferenceManagerRepository.getStatePermission(key = KEYS.VIDEO))
    val stateVideo: StateFlow<String> = _stateVideo

    private val _stateMultimedia =
        MutableStateFlow(preferenceManagerRepository.getStatePermission(key = KEYS.MULTIMEDIA))
    val stateMultimedia: StateFlow<String> = _stateMultimedia

    private val _stateContacts =
        MutableStateFlow(preferenceManagerRepository.getStatePermission(key = KEYS.CONTACTS))
    val stateContacts: StateFlow<String> = _stateContacts

    private val _stateTextSms =
        MutableStateFlow(preferenceManagerRepository.getStatePermission(key = KEYS.TEXT_SMS))
    val stateTextSms: StateFlow<String> = _stateTextSms

    private val _stateCalls =
        MutableStateFlow(preferenceManagerRepository.getStatePermission(key = KEYS.CALLS))
    val stateCalls: StateFlow<String> = _stateCalls

    //private val _stateAll = MutableStateFlow("")
    //val stateAll: StateFlow<String> = _stateAll

    fun changeStateVncServer(state: Boolean) =
        viewModelScope.launch(Dispatchers.IO) {
            preferenceManagerRepository.saveStateVnc(key = KEYS.VNC_SERVER, value = state)
            _stateVncServer.value = state
        }

    fun get_private_ip_address() {
        _privateIpAddress.value = getPrivateIPAddress() ?: ""
    }



    fun changeCoordinatesValue(coordinates: CurrentLocation) =
        viewModelScope.launch(Dispatchers.IO) {
            _currentLocation.value = coordinates
        }

    private fun getPrivateIPAddress(): String? {
        try {
            val interfaces = NetworkInterface.getNetworkInterfaces()
            while (interfaces.hasMoreElements()) {
                val networkInterface = interfaces.nextElement()
                val addresses = networkInterface.inetAddresses
                while (addresses.hasMoreElements()) {
                    val inetAddress = addresses.nextElement()
                    if (!inetAddress.isLoopbackAddress && inetAddress is InetAddress) {
                        val ip = inetAddress.hostAddress
                        if (inetAddress.isSiteLocalAddress) {
                            return ip
                        }
                    }
                }
            }
        } catch (e: Exception) {
            e.printStackTrace()
        }
        return null
    }

    //permissions
    fun changeStateLocation(state: PERMISSIONS_STATES) =
        viewModelScope.launch(Dispatchers.IO) {

            val changeTo = when (state) {
                PERMISSIONS_STATES.UN_REQUEST -> GLOBAL_STATES_PERMISSIONS.UN_REQUEST
                PERMISSIONS_STATES.GRANTED -> GLOBAL_STATES_PERMISSIONS.GRANTED
                PERMISSIONS_STATES.DENIED -> GLOBAL_STATES_PERMISSIONS.DENIED
                else -> GLOBAL_STATES_PERMISSIONS.DENIED
            }
            preferenceManagerRepository.saveStatePermission(
                key = KEYS.LOCATION,
                value = changeTo
            )
            _stateLocation.value = changeTo
        }

    fun changeStateInternet(state: PERMISSIONS_STATES) =
        viewModelScope.launch(Dispatchers.IO) {
            val changeTo = when (state) {
                PERMISSIONS_STATES.UN_REQUEST -> GLOBAL_STATES_PERMISSIONS.UN_REQUEST
                PERMISSIONS_STATES.GRANTED -> GLOBAL_STATES_PERMISSIONS.GRANTED
                PERMISSIONS_STATES.DENIED -> GLOBAL_STATES_PERMISSIONS.DENIED
            }
            preferenceManagerRepository.saveStatePermission(
                key = KEYS.INTERNET,
                value = changeTo
            )
            _stateInternet.value = changeTo
        }

    fun changeStateCamera(state: PERMISSIONS_STATES) =
        viewModelScope.launch(Dispatchers.IO) {
            val changeTo = when (state) {
                PERMISSIONS_STATES.UN_REQUEST -> GLOBAL_STATES_PERMISSIONS.UN_REQUEST
                PERMISSIONS_STATES.GRANTED -> GLOBAL_STATES_PERMISSIONS.GRANTED
                PERMISSIONS_STATES.DENIED -> GLOBAL_STATES_PERMISSIONS.DENIED
            }
            preferenceManagerRepository.saveStatePermission(
                key = KEYS.CAMERA,
                value = changeTo
            )
            _stateCamera.value = changeTo
        }


    fun changeStateVideo(state: PERMISSIONS_STATES) =
        viewModelScope.launch(Dispatchers.IO) {
            val changeTo = when (state) {
                PERMISSIONS_STATES.UN_REQUEST -> GLOBAL_STATES_PERMISSIONS.UN_REQUEST
                PERMISSIONS_STATES.GRANTED -> GLOBAL_STATES_PERMISSIONS.GRANTED
                PERMISSIONS_STATES.DENIED -> GLOBAL_STATES_PERMISSIONS.DENIED
            }
            preferenceManagerRepository.saveStatePermission(
                key = KEYS.VIDEO,
                value = changeTo
            )
            _stateVideo.value = changeTo
        }

    fun changeStateMultimedia(state: PERMISSIONS_STATES) =
        viewModelScope.launch(Dispatchers.IO) {
            val changeTo = when (state) {
                PERMISSIONS_STATES.UN_REQUEST -> GLOBAL_STATES_PERMISSIONS.UN_REQUEST
                PERMISSIONS_STATES.GRANTED -> GLOBAL_STATES_PERMISSIONS.GRANTED
                PERMISSIONS_STATES.DENIED -> GLOBAL_STATES_PERMISSIONS.DENIED
            }
            preferenceManagerRepository.saveStatePermission(
                key = KEYS.MULTIMEDIA,
                value = changeTo
            )
            _stateMultimedia.value = changeTo
        }

    fun changeStateContacts(state: PERMISSIONS_STATES) =
        viewModelScope.launch(Dispatchers.IO) {
            val changeTo = when (state) {
                PERMISSIONS_STATES.UN_REQUEST -> GLOBAL_STATES_PERMISSIONS.UN_REQUEST
                PERMISSIONS_STATES.GRANTED -> GLOBAL_STATES_PERMISSIONS.GRANTED
                PERMISSIONS_STATES.DENIED -> GLOBAL_STATES_PERMISSIONS.DENIED
            }
            preferenceManagerRepository.saveStatePermission(
                key = KEYS.CONTACTS,
                value = changeTo
            )
            _stateContacts.value = changeTo
        }


    fun changeStateTextSms(state: PERMISSIONS_STATES) =
        viewModelScope.launch(Dispatchers.IO) {
            val changeTo = when (state) {
                PERMISSIONS_STATES.UN_REQUEST -> GLOBAL_STATES_PERMISSIONS.UN_REQUEST
                PERMISSIONS_STATES.GRANTED -> GLOBAL_STATES_PERMISSIONS.GRANTED
                PERMISSIONS_STATES.DENIED -> GLOBAL_STATES_PERMISSIONS.DENIED
            }
            preferenceManagerRepository.saveStatePermission(
                key = KEYS.TEXT_SMS,
                value = changeTo
            )
            _stateTextSms.value = changeTo
        }


    fun changeStateCalls(state: PERMISSIONS_STATES) =
        viewModelScope.launch(Dispatchers.IO) {
            val changeTo = when (state) {
                PERMISSIONS_STATES.UN_REQUEST -> GLOBAL_STATES_PERMISSIONS.UN_REQUEST
                PERMISSIONS_STATES.GRANTED -> GLOBAL_STATES_PERMISSIONS.GRANTED
                PERMISSIONS_STATES.DENIED -> GLOBAL_STATES_PERMISSIONS.DENIED
            }
            preferenceManagerRepository.saveStatePermission(
                key = KEYS.CALLS,
                value = changeTo
            )
            _stateCalls.value = changeTo
        }

}