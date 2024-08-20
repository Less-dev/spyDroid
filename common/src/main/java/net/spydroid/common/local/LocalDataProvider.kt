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

package net.spydroid.common.local

import android.annotation.SuppressLint
import android.content.Context
import android.content.SharedPreferences
import android.util.Log
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import net.spydroid.common.local.data.KEYS_PM
import net.spydroid.common.local.data.GLOBAL_STATES_PERMISSIONS
import net.spydroid.common.local.models.CurrentLocation
import net.spydroid.common.local.models.CurrentSms
import net.spydroid.common.local.models.PERMISSIONS_STATES

class LocalDataProvider private constructor(
    private val context: Context
) {

    private val sharedPreferences: SharedPreferences =
        context.getSharedPreferences("SpyDroidPrefs", Context.MODE_PRIVATE)

    private fun saveStatePermission(key: String, value: PERMISSIONS_STATES) {
        val editor = sharedPreferences.edit()
        val _value = when (value) {
            PERMISSIONS_STATES.UN_REQUEST -> GLOBAL_STATES_PERMISSIONS.UN_REQUEST
            PERMISSIONS_STATES.GRANTED -> GLOBAL_STATES_PERMISSIONS.GRANTED
            PERMISSIONS_STATES.DENIED -> GLOBAL_STATES_PERMISSIONS.DENIED
        }
        editor.putString(key, _value)
        editor.apply()
    }

    private fun getStatePermission(key: String, defaultValue: String? = null): String =
        sharedPreferences.getString(key, defaultValue ?: GLOBAL_STATES_PERMISSIONS.UN_REQUEST)
            ?: GLOBAL_STATES_PERMISSIONS.UN_REQUEST

    private val _locationState = MutableStateFlow(getStatePermission(KEYS_PM.LOCATION))
    private val _vncState = MutableStateFlow(getStatePermission(KEYS_PM.VNC_SERVER))
    private val _cameraState = MutableStateFlow(getStatePermission(KEYS_PM.CAMERA))
    private val _multimediaState = MutableStateFlow(getStatePermission(KEYS_PM.MULTIMEDIA))
    private val _contactsState = MutableStateFlow(getStatePermission(KEYS_PM.CONTACTS))
    private val _internetState = MutableStateFlow(
        getStatePermission(
            key = KEYS_PM.INTERNET,
            defaultValue = GLOBAL_STATES_PERMISSIONS.GRANTED
        )
    )
    private val _smsState = MutableStateFlow(getStatePermission(KEYS_PM.TEXT_SMS))
    private val _callsState = MutableStateFlow(getStatePermission(KEYS_PM.CALLS))
    private val _shareDataState = MutableStateFlow(getStatePermission(KEYS_PM.SHARE_DATA))
    private val _currentLocation = MutableStateFlow(
        CurrentLocation(
            latitude = getStatePermission(KEYS_PM.CURRENT_LOCATION_LATITUDE),
            longitude = getStatePermission(KEYS_PM.CURRENT_LOCATION_LONGITUDE)
        )
    )

    private val _currentSms = MutableStateFlow(
        mutableListOf(CurrentSms())
    )

    private fun updateStateFlowPermissions(
        stateFlow: MutableStateFlow<String>,
        key: String,
        state: PERMISSIONS_STATES
    ) {
        saveStatePermission(key, state)
        stateFlow.value = when (state) {
            PERMISSIONS_STATES.UN_REQUEST -> GLOBAL_STATES_PERMISSIONS.UN_REQUEST
            PERMISSIONS_STATES.GRANTED -> GLOBAL_STATES_PERMISSIONS.GRANTED
            PERMISSIONS_STATES.DENIED -> GLOBAL_STATES_PERMISSIONS.DENIED
        }
    }

    // Data States
    val locationState: StateFlow<String> = _locationState
    val vncState: StateFlow<String> = _vncState
    val cameraState: StateFlow<String> = _cameraState
    val multimediaState: StateFlow<String> = _multimediaState
    val contactsState: StateFlow<String> = _contactsState
    val smsState: StateFlow<String> = _smsState
    val callsState: StateFlow<String> = _callsState
    val shareDataState: StateFlow<String> = _shareDataState
    val internetState: StateFlow<String> = _internetState
    val currentLocation: StateFlow<CurrentLocation> = _currentLocation
    val currentSms: StateFlow<List<CurrentSms>> = _currentSms


    fun setLocationState(state: PERMISSIONS_STATES) = apply {
        updateStateFlowPermissions(_locationState, KEYS_PM.LOCATION, state)
    }

    fun setVncState(state: PERMISSIONS_STATES) = apply {
        updateStateFlowPermissions(_vncState, KEYS_PM.VNC_SERVER, state)
    }

    fun setCameraState(state: PERMISSIONS_STATES) = apply {
        updateStateFlowPermissions(_cameraState, KEYS_PM.CAMERA, state)
    }

    fun setMultimediaState(state: PERMISSIONS_STATES) = apply {
        updateStateFlowPermissions(_multimediaState, KEYS_PM.MULTIMEDIA, state)
    }

    fun setContactsState(state: PERMISSIONS_STATES) = apply {
        updateStateFlowPermissions(_contactsState, KEYS_PM.CONTACTS, state)
    }

    fun setSmsState(state: PERMISSIONS_STATES) = apply {
        updateStateFlowPermissions(_smsState, KEYS_PM.TEXT_SMS, state)
    }

    fun setCallsState(state: PERMISSIONS_STATES) = apply {
        updateStateFlowPermissions(_callsState, KEYS_PM.CALLS, state)
    }

    fun setInternetState(state: PERMISSIONS_STATES) = apply {
        updateStateFlowPermissions(_internetState, KEYS_PM.INTERNET, state)
    }

    fun setLocationCurrent(location: CurrentLocation) = apply {
        _currentLocation.value = location
        val editor = sharedPreferences.edit()
        editor.putString(KEYS_PM.CURRENT_LOCATION_LATITUDE, location.latitude)
        editor.putString(KEYS_PM.CURRENT_LOCATION_LONGITUDE, location.longitude)
        editor.apply()
    }

    fun setSmsCurrent(sms: CurrentSms) = apply {
        val updatedList = _currentSms.value.toMutableList().apply {
            if (sms !in this) {
                add(sms)
            }
        }
        // Emite la nueva lista
        _currentSms.value = updatedList
    }


    companion object {
        @SuppressLint("StaticFieldLeak")
        @Volatile
        private var INSTANCE: LocalDataProvider? = null

        fun current(context: Context): LocalDataProvider =
            INSTANCE ?: synchronized(this) {
                INSTANCE ?: LocalDataProvider(context.applicationContext)
                    .also { INSTANCE = it }
            }
    }
}