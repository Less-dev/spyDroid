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
import net.spydroid.core.data.domain.PreferenceManagerRepository
import net.spydroid.core.data.models.CurrentLocation
import net.spydroid.core.data.data.LOCATION_STATES
import net.spydroid.core.data.models.STATES_LOCATION
import java.net.InetAddress
import java.net.NetworkInterface
import javax.inject.Inject


val LocalGlobalViewModel =
    compositionLocalOf<GlobalViewModel> { error("No GlobalViewModel found!") }

private object KEYS {
    const val VNC_SERVER = "state_vnc_server"
    const val LOCATION = "state_location"
}



@HiltViewModel
class GlobalViewModel @Inject constructor(
    private val preferenceManagerRepository: PreferenceManagerRepository
) : ViewModel() {

    private val _stateVncServer =
        MutableStateFlow(preferenceManagerRepository.getDataVncServer(KEYS.VNC_SERVER))
    val stateVncServer: StateFlow<Boolean> = _stateVncServer

    private val _privateIpAddress = MutableStateFlow("")
    val privateIpAddress: StateFlow<String> = _privateIpAddress

    private val _stateLocation = MutableStateFlow(preferenceManagerRepository.getDataLocation(key = KEYS.LOCATION))
    val stateLocation: StateFlow<String> = _stateLocation

    private val _currentLocation = MutableStateFlow(CurrentLocation())
    val currentLocation: StateFlow<CurrentLocation> = _currentLocation

    fun changeStateVncServer(state: Boolean) =
        viewModelScope.launch(Dispatchers.IO) {
            preferenceManagerRepository.saveDataVncServer(key = KEYS.VNC_SERVER, value = state)
            _stateVncServer.value = state
        }

    fun get_private_ip_address() {
        _privateIpAddress.value = getPrivateIPAddress() ?: ""
    }

    fun changeStateLocation(state: STATES_LOCATION? = STATES_LOCATION.UN_REQUEST) =
        viewModelScope.launch(Dispatchers.IO) {

            val state_location = when (state) {
                STATES_LOCATION.UN_REQUEST -> LOCATION_STATES.UN_REQUEST
                STATES_LOCATION.GRANTED -> LOCATION_STATES.GRANTED
                STATES_LOCATION.DENIED -> LOCATION_STATES.DENIED
                else -> LOCATION_STATES.DENIED
            }
            preferenceManagerRepository.saveDataLocation(key = KEYS.LOCATION, value = state_location)
            _stateLocation.value = state_location
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
}