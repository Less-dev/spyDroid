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

package net.spydroid.feature.location

import android.annotation.SuppressLint
import android.content.Context
import android.content.Intent
import android.location.LocationManager
import android.os.Handler
import android.os.Looper
import android.provider.Settings
import androidx.work.Worker
import androidx.work.WorkerParameters
import com.google.android.gms.location.LocationCallback
import com.google.android.gms.location.LocationRequest
import com.google.android.gms.location.LocationResult
import com.google.android.gms.location.LocationServices
import com.google.android.gms.location.Priority
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import net.spydroid.common.local.models.CurrentLocation
import net.spydroid.common.local.data.GLOBAL_STATES_PERMISSIONS
import net.spydroid.common.local.LocalDataProvider


class LocationWork(
    private val context: Context,
    workerParams: WorkerParameters
) : Worker(context, workerParams) {

    private lateinit var locationCallback: LocationCallback
    private val handler = Handler(Looper.getMainLooper())
    private lateinit var runnable: Runnable
    private val fusedLocationClient = LocationServices.getFusedLocationProviderClient(context)
    val localPermissions = LocalDataProvider.current(context)

    private val coroutineScope = CoroutineScope(Dispatchers.Main)

    override fun doWork(): Result {
        // Aquí va la lógica del trabajo en segundo plano
        try {
            locationCallback = object : LocationCallback() {
                override fun onLocationResult(p0: LocationResult) {
                    super.onLocationResult(p0)
                    for (location in p0.locations) {
                        if (location.latitude != null && location.longitude != null) {
                            localPermissions.setLocationCurrent(
                                CurrentLocation(
                                    location.latitude.toString(),
                                    location.longitude.toString()
                                )
                            )
                        }
                    }
                }
            }

            coroutineScope.launch {
                localPermissions.locationState.collect { state ->
                    if (state == GLOBAL_STATES_PERMISSIONS.GRANTED) {
                        val intent = Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS)
                        runnable = Runnable {
                            handler.postDelayed(runnable, 3000)
                            val isLocationOn = isLocationEnabled(context)
                            if (isLocationOn) {
                                startLocationUpdates()
                            } else {
                                intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK)
                                context.startActivity(intent)
                            }
                        }
                        handler.post(runnable)
                    }
                }
            }

            return Result.success()
        } catch (e: Exception) {
            // Si hubo un fallo en el trabajo
            return Result.failure()
        }
    }


    fun isLocationEnabled(ctx: Context): Boolean {
        val locationManager = ctx.getSystemService(Context.LOCATION_SERVICE) as LocationManager
        return locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER) ||
                locationManager.isProviderEnabled(LocationManager.NETWORK_PROVIDER)
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

}
