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

package net.spydroid.template.sample.presentation

import androidx.compose.animation.AnimatedVisibility
import androidx.compose.runtime.Composable
import androidx.hilt.navigation.compose.hiltViewModel
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import net.spydroid.core.data.common.GlobalViewModel
import net.spydroid.core.data.data.LOCATION_STATES
import net.spydroid.core.data.models.STATES_LOCATION
import net.spydroid.core.ui.components.dialogs.PermissionLocationDialog

@Composable
internal fun HomeScreen(
    homeViewModel: HomeViewModel = hiltViewModel(),
    globalViewModel: GlobalViewModel
) {

    val startVncServerState by globalViewModel.stateVncServer.collectAsState()
    val privateIpAddress by globalViewModel.privateIpAddress.collectAsState()
    val currentLocation by globalViewModel.currentLocation.collectAsState()
    val stateLocation by globalViewModel.stateLocation.collectAsState()
    var showDialogLocation by remember { mutableStateOf(false) }
    val context = LocalContext.current

    LaunchedEffect(globalViewModel) {
        this.launch(Dispatchers.IO) {
            globalViewModel.get_private_ip_address()
        }
    }

    Box(modifier = Modifier.fillMaxSize()) {
        Column(
            modifier = Modifier.fillMaxSize(),
            horizontalAlignment = Alignment.CenterHorizontally
        ) {

            Text(
                text = "Server vnc state: $startVncServerState", style = TextStyle(
                    color = if (startVncServerState) Color.Green else Color.Red,
                    fontSize = 20.sp,
                    fontWeight = FontWeight.ExtraBold
                ),
                modifier = Modifier.padding(bottom = 200.dp)
            )

            Button(onClick = {
                globalViewModel.changeStateVncServer(!startVncServerState)
            }) {
                Text(text = "Change state to ${if (startVncServerState) !startVncServerState else !startVncServerState}")
            }

            Spacer(modifier = Modifier.weight(1F))

            Text(
                text = if (currentLocation.latitude != null && currentLocation.longitude != null) "Current Location: ${currentLocation.latitude},${currentLocation.longitude}" else "no location found",
                style = TextStyle(
                    color = if (currentLocation.latitude != null && currentLocation.longitude != null) Color(
                        0xFFF4511E
                    ) else Color.Gray.copy(alpha = 0.65F),
                    fontWeight = FontWeight.SemiBold,
                    fontSize = 20.sp
                ),
                modifier = Modifier.padding(bottom = 20.dp)
            )

            Text(
                text = "State is ${stateLocation}",
                color = when (stateLocation) {
                    LOCATION_STATES.UN_REQUEST -> Color.Gray
                    LOCATION_STATES.GRANTED -> Color.Green
                    LOCATION_STATES.DENIED -> Color.Red
                    else -> Color.Gray
                }
            )

            Button(
                onClick = {
                    when (stateLocation) {
                        LOCATION_STATES.UN_REQUEST -> {
                            //If permission has not been requested, do so.
                            globalViewModel.changeStateLocation(STATES_LOCATION.GRANTED)
                        }

                        /*
                        LOCATION_STATES.GRANTED -> {
                            globalViewModel.changeStateLocation(STATES_LOCATION.GRANTED)
                        }
                         */

                        LOCATION_STATES.DENIED -> {
                            //show settings for the app
                            showDialogLocation = true
                        }
                    }
                },
                modifier = Modifier.padding(bottom = 20.dp)
            ) {
                Text(text = "Requests Permission Location")
            }

            AnimatedVisibility(visible = startVncServerState) {
                Text(
                    text = "host: $privateIpAddress:5300", style = TextStyle(
                        color = Color(0xFFA79000),
                        fontWeight = FontWeight.Bold,
                        fontSize = 20.sp
                    ),
                    modifier = Modifier.padding(bottom = 20.dp)
                )
            }

        }
    }

    PermissionLocationDialog(context = context, state = showDialogLocation) {
        showDialogLocation = false
    }
}


