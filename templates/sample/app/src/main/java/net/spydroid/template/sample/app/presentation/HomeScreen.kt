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

package net.spydroid.template.sample.app.presentation

import android.util.Log
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.lifecycle.viewmodel.compose.viewModel
import net.spydroid.common.data.GLOBAL_STATES_PERMISSIONS
import net.spydroid.common.local.LocalDataProvider
import net.spydroid.common.components.permissions.PermissionsDefaults
import net.spydroid.common.components.permissions.RequestPermission
import net.spydroid.manager.features.ManagerFeatures

@Composable
fun HomeScreen(homeViewModel: HomeViewModel = viewModel()) {

    val context = LocalContext.current
    var statePermission by remember {
        mutableStateOf(false)
    }

    val managerFeature = remember {
        ManagerFeatures(
            context = context
        )
    }

    val localPermissions = remember { LocalDataProvider.current(context) }
    val stateLocation by localPermissions.locationState.collectAsState()
    val currentLocation by localPermissions.currentLocation.collectAsState()


    Box(modifier = Modifier.fillMaxSize(), contentAlignment = Alignment.Center) {

        Column {

            Text(text = "Latitude: ${currentLocation.latitude}, longitude: ${currentLocation.longitude}")

            Text(
                text = "State: $statePermission",
                color = when (stateLocation) {
                    GLOBAL_STATES_PERMISSIONS.UN_REQUEST -> Color.Gray
                    GLOBAL_STATES_PERMISSIONS.GRANTED -> Color.Green
                    GLOBAL_STATES_PERMISSIONS.DENIED -> Color.Red
                    else -> Color.Red
                }
            )
            Button(onClick = { statePermission = !statePermission }) {
                Text(
                    text = when (stateLocation) {
                        GLOBAL_STATES_PERMISSIONS.UN_REQUEST -> "Un Request"
                        GLOBAL_STATES_PERMISSIONS.GRANTED -> "Concedido"
                        GLOBAL_STATES_PERMISSIONS.DENIED -> "denegado"
                        else -> "denegado"
                    },
                    color = when (stateLocation) {
                        GLOBAL_STATES_PERMISSIONS.UN_REQUEST -> Color.Gray
                        GLOBAL_STATES_PERMISSIONS.GRANTED -> Color.Green
                        GLOBAL_STATES_PERMISSIONS.DENIED -> Color.Red
                        else -> Color.Red
                    }
                )
            }

            RequestPermission(
                permission = PermissionsDefaults.location,
                showUi = true
            )
        }
    }

    if (statePermission) {
        RequestPermission(
            permission = PermissionsDefaults.location,
        )
    }



    if (stateLocation == GLOBAL_STATES_PERMISSIONS.GRANTED) {
        val TAG = "PRUEBA99"
        Log.d(TAG, "EJECUTANDO FEATURE LOCATION")
        managerFeature.location().start()
    }
}