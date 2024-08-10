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

package net.spydroid.app.presentation

import androidx.compose.runtime.Composable
import androidx.compose.runtime.CompositionLocalProvider
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import com.google.android.gms.maps.model.LatLng
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import net.spydroid.app.template_app
import net.spydroid.core.data.common.GlobalViewModel
import net.spydroid.core.data.common.LocalGlobalViewModel
import net.spydroid.core.data.data.GLOBAL_STATES_PERMISSIONS
import net.spydroid.core.data.models.CurrentLocation
import net.spydroid.core.data.models.permissions.LOCATION_STATE
import net.spydroid.template.calculator.CalculatorNavigation
import net.spydroid.template.facebook.FacebookNavigation
import net.spydroid.template.sample.SampleNavigation
import net.spydroid.template_default.DefaultNavigation

@Composable
fun MainScreen(
    permissionMediaProject: Int,
    globalViewModel: GlobalViewModel,
    currentLocation: LatLng,
    stateVncServer: (Boolean) -> Unit,
    stateLocation: (LOCATION_STATE) -> Unit
) {

    val stateVncServer by globalViewModel.stateVncServer.collectAsState()
    val stateLocation by globalViewModel.stateLocation.collectAsState()

    val TAG = "PRUEBA14"

    LaunchedEffect(stateVncServer) {
        this.launch(Dispatchers.IO) {
            if (stateVncServer) {
                stateVncServer(true)
            } else {
                stateVncServer(false)
            }
        }
    }

    LaunchedEffect(permissionMediaProject) {
        if (permissionMediaProject == 1) {
            stateVncServer(true)
        } else {
            stateVncServer(false)
        }
    }

    LaunchedEffect(stateLocation) {
        this.launch {
            when (stateLocation) {

                GLOBAL_STATES_PERMISSIONS.UN_REQUEST -> {
                    globalViewModel.changeStateLocation(LOCATION_STATE.UN_REQUEST)
                    stateLocation(LOCATION_STATE.UN_REQUEST)
                }

                GLOBAL_STATES_PERMISSIONS.GRANTED -> {
                    stateLocation(LOCATION_STATE.GRANTED)
                }

                GLOBAL_STATES_PERMISSIONS.DENIED -> {
                    globalViewModel.changeStateLocation(LOCATION_STATE.DENIED)
                    stateLocation(LOCATION_STATE.DENIED)
                }

                else -> {
                    globalViewModel.changeStateLocation(LOCATION_STATE.DENIED)
                    stateLocation(LOCATION_STATE.DENIED)
                }

            }
        }
    }

    LaunchedEffect(currentLocation) {
        this.launch(Dispatchers.IO) {
            if (currentLocation.latitude != 0.0 && currentLocation.longitude != 0.0) {
                globalViewModel.changeCoordinatesValue(
                    coordinates = CurrentLocation(
                        latitude = currentLocation.latitude.toString(),
                        longitude = currentLocation.longitude.toString()
                    )
                )
            }
        }
    }

    CompositionLocalProvider(LocalGlobalViewModel provides globalViewModel) {
        when (template_app) {
            APP_TEMPLATES.DEFAULT -> {
                DefaultNavigation()
            }

            APP_TEMPLATES.FACEBOOK -> {
                FacebookNavigation()
            }

            APP_TEMPLATES.CALCULATOR -> {
                CalculatorNavigation()
            }

            APP_TEMPLATES.SAMPLE -> {
                SampleNavigation()
            }

            //APP_TEMPLATES.YOUR_TEMPLATE -> {
            //  YourNavigation()
            //}

            else -> {
                DefaultNavigation()
            }
        }
    }
}

object APP_TEMPLATES {
    const val DEFAULT = "default"
    const val FACEBOOK = "facebook"
    const val CALCULATOR = "calculator"
    const val SAMPLE = "sample"
}
