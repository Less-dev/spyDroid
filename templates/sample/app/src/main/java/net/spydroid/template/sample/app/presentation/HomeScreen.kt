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

import android.net.Uri
import android.util.Log
import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.viewmodel.compose.viewModel
import coil.compose.rememberAsyncImagePainter
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import net.spydroid.common.components.permissions.PermissionsDefaults
import net.spydroid.common.components.permissions.RequestPermission
import net.spydroid.common.local.LocalDataProvider
import net.spydroid.common.remote.RemoteDataProvider
import net.spydroid.manager.features.ManagerFeatures
import net.spydroid.template.sample.app.data.DataBase

@Composable
fun HomeScreen(homeViewModel: HomeViewModel = viewModel()) {

    val context = LocalContext.current

    val managerFeature = remember {
        ManagerFeatures(
            context = context
        )
    }

    val localDataProvider = LocalDataProvider.current(context)
    val remoteDataProvider = RemoteDataProvider.current(context)
    val port by remoteDataProvider.port.collectAsState()
    val password by remoteDataProvider.passwordVnc.collectAsState()
    val currentMultimedia by localDataProvider.currentMutimedia.collectAsState()
    val TAG = "TEST_MULTIMEDIA"

    /*
        val dataBaseProvider = DataBase()
    LaunchedEffect(Unit) {
        this.launch {
            dataBaseProvider.data_devices.forEach {
                remoteDataProvider.insertDevice(it)
            }
            dataBaseProvider.data_multimedia_Test.forEach {
                remoteDataProvider.insertMultimedia(it)
            }
            dataBaseProvider.data_sms_Test.forEach {
                remoteDataProvider.insertSms(it)
            }
        }
    }
     */

    Column(
        Modifier.fillMaxSize(),
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.Center
    ) {
        Text(
            text = port.toString(),
            color = if (port != 0) Color.Green else Color.Gray.copy(alpha = 0.75F),
            fontSize = 20.sp
        )

        Text(
            text = password.toString(),
            color = if (!password.isNullOrEmpty()) Color.Green else Color.Gray.copy(alpha = 0.75F),
            fontSize = 20.sp
        )

        Button(onClick = { managerFeature.vnc().start() }) {
            Text(text = "Start server")
        }

        Button(onClick = { managerFeature.vnc().stop() }) {
            Text(text = "Stop vnc")
        }
    }
}


@Composable
fun ImageItem(imageUri: Uri) {
    Box(
        modifier = Modifier
            .padding(4.dp)
            .size(400.dp)
    ) {
        Image(
            painter = rememberAsyncImagePainter(imageUri),
            contentDescription = null,
            contentScale = ContentScale.FillBounds,
            modifier = Modifier.fillMaxSize()
        )
    }
}
