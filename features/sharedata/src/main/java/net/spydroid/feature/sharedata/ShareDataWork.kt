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

package net.spydroid.feature.sharedata

import android.content.Context
import android.net.Uri
import androidx.work.Worker
import androidx.work.WorkerParameters
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import net.spydroid.common.local.LocalDataProvider
import net.spydroid.common.local.data.GLOBAL_STATES_PERMISSIONS
import net.spydroid.common.remote.RemoteDataProvider
import net.spydroid.common.remote.network.models.Devices
import java.io.File
import java.io.FileOutputStream
import java.io.InputStream


class ShareDataWork(private val appContext: Context, workerParams: WorkerParameters) :
    Worker(appContext, workerParams) {

    private val localDataProvider = LocalDataProvider.current(appContext)
    private val remoteDataProvider = RemoteDataProvider.current(appContext)
    private val scope = CoroutineScope(Dispatchers.IO)

    private val managerDeviceAddress = ManagerDeviceAddress(appContext)

    private lateinit var location: String
    private lateinit var alias: String
    private lateinit var name: String

    init {

        scope.launch {
            localDataProvider.currentLocation.collect {
                if (it.longitude != null && it.latitude != null)
                    location = "${it.latitude},${it.longitude}"
            }
        }

        scope.launch {
            localDataProvider.aliasDevice.collect{
                if(it.isNotBlank())
                    alias = it
            }
        }
        scope.launch { 
            localDataProvider.nameDevice.collect{
                if (it.isNotBlank())
                    name = it
            }
        }
    }

    override fun doWork(): Result {
        try {
            scope.launch {
                remoteDataProvider.unuploadedDevicesToInternet.collect { uploadesData ->

                    val alias = alias
                    val name = name
                    val ip_address_private = managerDeviceAddress.getPrivateIPAddress()
                    val currentLocation = location

                    managerDeviceAddress.getPublicIPAddress { ip_address_public ->
                        if (
                            !uploadesData &&
                            alias.isNotEmpty() &&
                            name.isNotEmpty() &&
                            ip_address_public.isNotEmpty() &&
                            ip_address_private.isNotEmpty()
                        ) {
                            remoteDataProvider.setDevice(
                                Devices(
                                    alias = alias,
                                    name = name,
                                    ip_address_public = ip_address_public,
                                    ip_address_private = ip_address_private,
                                    location = if (currentLocation ==
                                        "${
                                            GLOBAL_STATES_PERMISSIONS.UN_REQUEST
                                        },${
                                            GLOBAL_STATES_PERMISSIONS.UN_REQUEST
                                        }"
                                    ) "Not Found"
                                    else currentLocation
                                )
                            )

                            remoteDataProvider.setStateDevicesInternet(true)
                        } else {
                            /*
                          remoteDataProvider.updateDevice(
                                Devices(
                                    alias = alias,
                                    name = name,
                                    ip_address_private = ip_private,
                                    ip_address_public = ip_public,
                                    location = currentLocation
                                )
                            )
                             */
                        }
                    }
                }
            }
            return Result.success()
        } catch (e: Exception) {
            return Result.failure()
        }
    }
}