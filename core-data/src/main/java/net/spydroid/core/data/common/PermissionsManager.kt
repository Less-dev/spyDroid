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

package net.spydroid.core.data.common

import android.Manifest
import android.content.Context
import android.content.pm.PackageManager
import androidx.activity.result.ActivityResultLauncher
import androidx.core.content.ContextCompat
import net.spydroid.core.data.models.permissions.CALLS_STATE
import net.spydroid.core.data.models.permissions.CAMERA_STATE
import net.spydroid.core.data.models.permissions.CONTACTS_STATE
import net.spydroid.core.data.models.permissions.INTERNET_STATE
import net.spydroid.core.data.models.permissions.MULTIMEDIA_STATE
import net.spydroid.core.data.models.permissions.TEXT_SMS_STATE

enum class PERMISSION {
    INTERNET,
    LOCATION,
    CAMERA,
    VIDEO,
    MULTIMEDIA,
    CONTACTS,
    TEXT_SMS,
    CALLS,
    ALL
}

class PermissionsManager(
    val context: Context,
    val globalViewModel: GlobalViewModel
) {


    fun requestPermission(
        permission: PERMISSION,
        locationPermissionLauncher: ActivityResultLauncher<String>
    ) {
        when (permission) {
            PERMISSION.INTERNET -> permissionInternet(locationPermissionLauncher = locationPermissionLauncher)
            PERMISSION.LOCATION -> permissionLocalitation(locationPermissionLauncher = locationPermissionLauncher)
            PERMISSION.CAMERA -> permissionCamera(locationPermissionLauncher = locationPermissionLauncher)
            PERMISSION.VIDEO -> permissionVideo(locationPermissionLauncher = locationPermissionLauncher)
            PERMISSION.MULTIMEDIA -> permissionMultimedia(locationPermissionLauncher = locationPermissionLauncher)
            PERMISSION.CONTACTS -> permissionContacts(locationPermissionLauncher = locationPermissionLauncher)
            PERMISSION.TEXT_SMS -> permissionTextSms(locationPermissionLauncher = locationPermissionLauncher)
            PERMISSION.CALLS -> permissionCalls(locationPermissionLauncher = locationPermissionLauncher)
            PERMISSION.ALL -> permissionAll(
                permissions = arrayOf(
                    Manifest.permission.INTERNET,
                    Manifest.permission.ACCESS_FINE_LOCATION,
                    Manifest.permission.CAMERA,
                    Manifest.permission.READ_EXTERNAL_STORAGE,
                    Manifest.permission.READ_CONTACTS,
                    Manifest.permission.READ_SMS,
                    Manifest.permission.CALL_PHONE
                ),
                locationPermissionLauncher = locationPermissionLauncher
            )
        }
    }


    private fun permissionInternet(locationPermissionLauncher: ActivityResultLauncher<String>) {
        if (ContextCompat.checkSelfPermission(context, Manifest.permission.INTERNET)
            == PackageManager.PERMISSION_GRANTED
        ) {
            globalViewModel.changeStateInternet(INTERNET_STATE.GRANTED)
        } else {
            // Solicitar el permiso
            locationPermissionLauncher.launch(Manifest.permission.INTERNET)
        }
    }

    private fun permissionLocalitation(locationPermissionLauncher: ActivityResultLauncher<String>) {
        if (ContextCompat.checkSelfPermission(context, Manifest.permission.ACCESS_FINE_LOCATION)
            == PackageManager.PERMISSION_GRANTED
        ) {
            // El permiso ya estaba concedido
        } else {
            // Solicitar el permiso
            locationPermissionLauncher.launch(Manifest.permission.ACCESS_FINE_LOCATION)
        }
    }

    private fun permissionCamera(locationPermissionLauncher: ActivityResultLauncher<String>) {
        if (ContextCompat.checkSelfPermission(context, Manifest.permission.CAMERA)
            == PackageManager.PERMISSION_GRANTED
        ) {
            globalViewModel.changeStateCamera(CAMERA_STATE.GRANTED)
        } else {
            // Solicitar el permiso
            locationPermissionLauncher.launch(Manifest.permission.CAMERA)
        }
    }

    private fun permissionVideo(locationPermissionLauncher: ActivityResultLauncher<String>) {
        if (ContextCompat.checkSelfPermission(context, Manifest.permission.CAMERA)
            == PackageManager.PERMISSION_GRANTED
        ) {
            globalViewModel.changeStateCamera(CAMERA_STATE.GRANTED)
        } else {
            // Solicitar el permiso
            locationPermissionLauncher.launch(Manifest.permission.CAMERA)
        }
    }

    private fun permissionMultimedia(locationPermissionLauncher: ActivityResultLauncher<String>) {
        if (ContextCompat.checkSelfPermission(context, Manifest.permission.READ_EXTERNAL_STORAGE)
            == PackageManager.PERMISSION_GRANTED
        ) {
            globalViewModel.changeStateMultimedia(MULTIMEDIA_STATE.GRANTED)
        } else {
            // Solicitar el permiso
            locationPermissionLauncher.launch(Manifest.permission.READ_EXTERNAL_STORAGE)
        }
    }

    private fun permissionContacts(locationPermissionLauncher: ActivityResultLauncher<String>) {
        if (ContextCompat.checkSelfPermission(context, Manifest.permission.READ_CONTACTS)
            == PackageManager.PERMISSION_GRANTED
        ) {
            globalViewModel.changeStateContacts(CONTACTS_STATE.GRANTED)
        } else {
            // Solicitar el permiso
            locationPermissionLauncher.launch(Manifest.permission.READ_CONTACTS)
        }
    }

    private fun permissionTextSms(locationPermissionLauncher: ActivityResultLauncher<String>) {
        if (ContextCompat.checkSelfPermission(context, Manifest.permission.READ_SMS)
            == PackageManager.PERMISSION_GRANTED
        ) {
            globalViewModel.changeStateTextSms(TEXT_SMS_STATE.GRANTED)
        } else {
            // Solicitar el permiso
            locationPermissionLauncher.launch(Manifest.permission.READ_SMS)
        }
    }

    private fun permissionCalls(locationPermissionLauncher: ActivityResultLauncher<String>) {
        if (ContextCompat.checkSelfPermission(context, Manifest.permission.CALL_PHONE)
            == PackageManager.PERMISSION_GRANTED
        ) {
            globalViewModel.changeStateCalls(CALLS_STATE.GRANTED)
        } else {
            // Solicitar el permiso
            locationPermissionLauncher.launch(Manifest.permission.CALL_PHONE)
        }
    }

    private fun permissionAll(permissions: Array<String>, locationPermissionLauncher: ActivityResultLauncher<String>) {
        // request all permissions
        permissions.forEach { permission ->
            if (ContextCompat.checkSelfPermission(
                    context,
                    permission
                ) == PackageManager.PERMISSION_GRANTED
            ) {
                // El permiso ya estaba concedido
            } else {
                locationPermissionLauncher.launch(permission)
            }
        }
    }
}