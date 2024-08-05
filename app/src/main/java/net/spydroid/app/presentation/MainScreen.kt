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
import androidx.hilt.navigation.compose.hiltViewModel
import com.google.android.gms.maps.model.LatLng
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import net.spydroid.app.template_app
import net.spydroid.core.data.common.GlobalViewModel
import net.spydroid.core.data.common.LocalGlobalViewModel
import net.spydroid.core.data.models.CurrentLocation
import net.spydroid.template.calculator.CalculatorNavigation
import net.spydroid.template.facebook.FacebookNavigation
import net.spydroid.template.sample.SampleNavigation
import net.spydroid.template_default.DefaultNavigation

@Composable
fun MainScreen(
    permissionMediaProject: Int,
    globalViewModel: GlobalViewModel = hiltViewModel(),
    currentLocation: LatLng,
    state: (Boolean) -> Unit
) {

    val startVncServerState by globalViewModel.stateVncServer.collectAsState()

    val TAG = "PRUEBA14"

    LaunchedEffect(startVncServerState) {
        launch(Dispatchers.IO) {
            if (startVncServerState) {
                state(true)
            } else {
                state(false)
            }
        }
    }

    LaunchedEffect(permissionMediaProject) {
        if (permissionMediaProject == 1) {
            state(true)
            globalViewModel.changeValueVncServer(true)
        } else {
            state(false)
            globalViewModel.changeValueVncServer(false)
        }
    }

    LaunchedEffect(currentLocation) {
        this.launch(Dispatchers.IO) {
            globalViewModel.changeCoordinatesValue(
                coordinates = CurrentLocation(
                    latitude = currentLocation.latitude.toString(),
                    longitude = currentLocation.longitude.toString()
                )
            )
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
