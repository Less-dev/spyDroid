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

package net.spydroid.app

import android.annotation.SuppressLint
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Build
import android.os.Bundle
import android.os.Looper
import android.preference.PreferenceManager
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.compose.setContent
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
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
import androidx.core.content.ContextCompat
import com.google.android.gms.location.FusedLocationProviderClient
import com.google.android.gms.location.LocationCallback
import com.google.android.gms.location.LocationRequest
import com.google.android.gms.location.LocationResult
import com.google.android.gms.location.LocationServices
import com.google.android.gms.location.Priority
import com.google.android.gms.maps.model.CameraPosition
import com.google.android.gms.maps.model.LatLng
import com.google.maps.android.compose.CameraPositionState
import dagger.hilt.android.AndroidEntryPoint
import net.christianbeier.droidvnc_ng.Constants
import net.christianbeier.droidvnc_ng.Defaults
import net.christianbeier.droidvnc_ng.MainService
import net.spydroid.app.ui.theme.SpyDroidTheme
import kotlin.math.PI
import kotlin.math.cos
import kotlin.math.sin
import com.google.maps.android.compose.rememberCameraPositionState
import net.spydroid.app.presentation.MainScreen


@Suppress("DEPRECATION", "KotlinConstantConditions")
@AndroidEntryPoint
class MainActivity : ComponentActivity() {

    private lateinit var fusedLocationClient: FusedLocationProviderClient
    private lateinit var locationCallback: LocationCallback
    private var locationRequired: Boolean = false


    private var mediaProjectionPermission by mutableIntStateOf(-1)
    override fun onCreate(savedInstanceState: Bundle?) {

        super.onCreate(savedInstanceState)

        fusedLocationClient = LocationServices.getFusedLocationProviderClient(this)

        setContent {

            SpyDroidTheme {
                // A surface container using the 'background' color from the theme
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {


                    var currentLocation by remember {
                        mutableStateOf(
                            LatLng(
                                0.toDouble(),
                                0.toDouble()
                            )
                        )
                    }

                    locationCallback = object : LocationCallback() {
                        override fun onLocationResult(p0: LocationResult) {
                            super.onLocationResult(p0)
                            for (location in p0.locations) {
                                currentLocation = LatLng(location.latitude, location.longitude)
                            }
                        }
                    }

                    /*
                    MainScreen(
                        permissionMediaProject = mediaProjectionPermission,
                        currentLocation = currentLocation
                    ) {
                        if (it) startMainService() else stopMainService()
                    }
                     */

                    LocationScreen {
                        locationRequired = true
                        startLocationUpdates()
                    }


                }
            }

        }
    }

    override fun onResume() {
        super.onResume()
        when (MainService.isMediaProjectionEnabled()) {
            0 -> {
                //granted permission
                mediaProjectionPermission = 0
            }

            1 -> {
                //denied permission
                mediaProjectionPermission = 1
            }

            -1 -> {
                mediaProjectionPermission = -1
                //unknown permission
            }
        }

        if (locationRequired) {
            startLocationUpdates()
        }
    }

    override fun onPause() {
        super.onPause()
        locationCallback?.let {
            fusedLocationClient?.removeLocationUpdates(it)
        }
    }

    @SuppressLint("MissingPermission")
    private fun startLocationUpdates() {
        locationCallback?.let {
            val locationRequest = LocationRequest.Builder(
                Priority.PRIORITY_HIGH_ACCURACY, 100
            )
                .setWaitForAccurateLocation(false)
                .setMinUpdateIntervalMillis(3000)
                .setMaxUpdateDelayMillis(100)
                .build()

            fusedLocationClient?.requestLocationUpdates(
                locationRequest,
                it,
                Looper.getMainLooper()
            )
        }
    }


    private fun startMainService() {
        val intent = Intent(this, MainService::class.java)
        val prefs = PreferenceManager.getDefaultSharedPreferences(this)
        val mDefaults = Defaults(this)

        intent.putExtra(
            MainService.EXTRA_PORT,
            prefs.getInt(Constants.PREFS_KEY_SETTINGS_PORT, mDefaults.port)
        )
        intent.putExtra(
            MainService.EXTRA_PASSWORD,
            prefs.getString(Constants.PREFS_KEY_SETTINGS_PASSWORD, mDefaults.password)
        )
        intent.putExtra(
            MainService.EXTRA_FILE_TRANSFER,
            prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_FILE_TRANSFER, mDefaults.fileTransfer)
        )
        intent.putExtra(
            MainService.EXTRA_VIEW_ONLY,
            prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_VIEW_ONLY, mDefaults.viewOnly)
        )
        intent.putExtra(
            MainService.EXTRA_SHOW_POINTERS,
            prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_SHOW_POINTERS, mDefaults.showPointers)
        )
        intent.putExtra(
            MainService.EXTRA_SCALING,
            prefs.getFloat(Constants.PREFS_KEY_SETTINGS_SCALING, mDefaults.scaling)
        )
        intent.putExtra(
            MainService.EXTRA_ACCESS_KEY,
            prefs.getString(Constants.PREFS_KEY_SETTINGS_ACCESS_KEY, mDefaults.accessKey)
        )
        intent.setAction(MainService.ACTION_START)
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            startForegroundService(intent)
        } else {
            startService(intent)
        }
    }


    private fun stopMainService() {
        val intent = Intent(this, MainService::class.java)
        intent.setAction(MainService.ACTION_STOP)
        stopService(intent)
    }
}

@Composable
private fun LocationScreen(
    permissionsGranted: () -> Unit
) {
    val context = LocalContext.current

    val permissions = arrayOf(
        android.Manifest.permission.ACCESS_FINE_LOCATION,
        android.Manifest.permission.ACCESS_COARSE_LOCATION,
    )

    val launchMultiplePermissions =
        rememberLauncherForActivityResult(ActivityResultContracts.RequestMultiplePermissions())
        { permissionMaps ->
            val areGranted = permissionMaps.values.reduce { acc, next -> acc && next }
            if (areGranted) {
                permissionsGranted()
                Toast.makeText(context, "Permisos concedidos", Toast.LENGTH_SHORT).show()
            } else {
                Toast.makeText(context, "Permisos denegados", Toast.LENGTH_SHORT).show()
            }
        }
    LaunchedEffect(Unit) {
        if (permissions.all {
                ContextCompat.checkSelfPermission(
                    context,
                    it
                ) == PackageManager.PERMISSION_GRANTED
            }) {

            permissionsGranted()
        } else {
            launchMultiplePermissions.launch(permissions)
        }
    }

    Box(modifier = Modifier.fillMaxSize()) {

        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(15.dp),
            verticalArrangement = Arrangement.Top,
            horizontalAlignment = Alignment.CenterHorizontally
        ) {
            Text(
                text = "LATITUD: 40.1287128, LONGITUD: -12.78127",
                style = TextStyle(
                    color = Color.Blue,
                    fontWeight = FontWeight.ExtraBold,
                    fontSize = 30.sp
                )
            )
            Button(onClick = {

                if (permissions.all {
                        ContextCompat.checkSelfPermission(
                            context,
                            it
                        ) == PackageManager.PERMISSION_GRANTED
                    }) {
                    //get location
                    permissionsGranted()
                } else {
                    launchMultiplePermissions.launch(permissions)
                }
            }) {
                Text(text = "Refresh Location")
            }
        }
    }
}


