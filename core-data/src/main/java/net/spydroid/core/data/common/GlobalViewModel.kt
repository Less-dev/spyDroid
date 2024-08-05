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
import java.net.InetAddress
import java.net.NetworkInterface
import javax.inject.Inject


val LocalGlobalViewModel = compositionLocalOf<GlobalViewModel> { error("No GlobalViewModel found!") }

@HiltViewModel
class GlobalViewModel  @Inject constructor(
    private val preferenceManagerRepository: PreferenceManagerRepository
): ViewModel() {

    private val _stateVncServer = MutableStateFlow(preferenceManagerRepository.getData("state"))
    val stateVncServer: StateFlow<Boolean> = _stateVncServer

    private val _privateIpAddress = MutableStateFlow("")
    val privateIpAddress: StateFlow<String> = _privateIpAddress

    private val _currentLocation = MutableStateFlow(CurrentLocation())
    val currentLocation: StateFlow<CurrentLocation> = _currentLocation

    fun changeValueVncServer(value: Boolean) =
        viewModelScope.launch(Dispatchers.IO) {
            preferenceManagerRepository.saveData(key = "state", value = value)
            _stateVncServer.value = value
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
}