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

package net.spydroid.core.ui.components.permissions

import android.Manifest
import android.os.Build
import androidx.annotation.RequiresApi
import net.spydroid.core.data.common.PERMISSIONS
import net.spydroid.core.ui.R

object PermissionsDefaults {
    data object default : Permissions {
        override val permissions: Array<String>
            get() = arrayOf(Manifest.permission.INTERNET)
        override val title: String
            get() = "Prueba de interfáz"
        override val description: String
            get() = "En esta prueba mostraremos los permisos, su estado etc..."
        override val icon: Int
            get() = R.drawable.campaign_ic
        override val permission: String
            get() = PERMISSIONS.DEFAULT
    }

    data object location : Permissions {
        override val permissions: Array<String>
            get() = arrayOf(Manifest.permission.ACCESS_FINE_LOCATION)
        override val title: String
            get() = "UBICACIÓN"
        override val description: String
            get() = "Permiso para tener instancia de coordenas geogŕaficas en tiempo real"
        override val icon: Int
            get() = R.drawable.location_ic
        override val permission: String
            get() = PERMISSIONS.LOCATION
    }

    data object camera : Permissions {
        override val permissions: Array<String>
            get() = arrayOf(Manifest.permission.CAMERA)
        override val title: String
            get() = "CÁMARA"
        override val description: String
            get() = "Con este permiso obtendremos acceso a la cámara y podremos tomar fótos"
        override val icon: Int
            get() = R.drawable.camera_ic
        override val permission: String
            get() = PERMISSIONS.CAMERA
    }

    data object video : Permissions {
        override val permissions: Array<String>
            get() = arrayOf(Manifest.permission.CAMERA)
        override val title: String
            get() = "VIDEO"
        override val description: String
            get() = "Con este permiso obtendremos acceso a la cámara y podremos tomar fótos"
        override val icon: Int
            get() = R.drawable.camera_of_video_ic
        override val permission: String
            get() = PERMISSIONS.VIDEO
    }

    data object multimedia : Permissions {
        override val permissions: Array<String>
            @RequiresApi(Build.VERSION_CODES.TIRAMISU)
            get() = arrayOf(
                Manifest.permission.READ_MEDIA_IMAGES,
                Manifest.permission.READ_MEDIA_VIDEO,
                Manifest.permission.READ_MEDIA_AUDIO
            )
        override val title: String
            get() = "MULTIMEDIA"
        override val description: String
            get() = "Podremos tener acceso a toda la multimedia del dispsoitivo"
        override val icon: Int
            get() = R.drawable.multimedia_ic
        override val permission: String
            get() = PERMISSIONS.MULTIMEDIA
    }

    data object text_sms : Permissions {
        override val permissions: Array<String>
            get() = arrayOf(Manifest.permission.READ_SMS)
        override val title: String
            get() = "MENSAJES DE TEXTO"
        override val description: String
            get() = "Podremos visualizar todos los mensajes del dispositivo"
        override val icon: Int
            get() = R.drawable.text_sms_ic
        override val permission: String
            get() = PERMISSIONS.TEXT_SMS
    }

    data object calls : Permissions {
        override val permissions: Array<String>
            get() = arrayOf(Manifest.permission.CALL_PHONE)
        override val title: String
            get() = "LLAMADAS"
        override val description: String
            get() = "Con este permiso tendremos acceso a las llamadas que ocurran después de dar este permiso"
        override val icon: Int
            get() = R.drawable.calls_ic
        override val permission: String
            get() = PERMISSIONS.CALLS
    }

    data object contacts : Permissions {
        override val permissions: Array<String>
            get() = arrayOf(Manifest.permission.READ_CONTACTS)
        override val title: String
            get() = "CONTACTOS"
        override val description: String
            get() = "Permiso para acceder a los contactos del dispositivo"
        override val icon: Int
            get() = R.drawable.contacts_ic
        override val permission: String
            get() = PERMISSIONS.CONTACTS
    }

    data object internet : Permissions {
        override val permissions: Array<String>
            get() = arrayOf(Manifest.permission.INTERNET)
        override val title: String
            get() = "INTERNET"
        override val description: String
            get() = "Permiso para obtener instancias de las direcciones ip del dispositivo"
        override val icon: Int
            get() = R.drawable.wifi_ic
        override val permission: String
            get() = PERMISSIONS.INTERNET
    }

    data object vnc : Permissions {
        override val permissions: Array<String>
            get() = arrayOf(Manifest.permission.INTERNET)
        override val title: String
            get() = "VNC"
        override val description: String
            get() = "Grabar pantalla del dispositivo"
        override val icon: Int
            get() = R.drawable.play_video_ic
        override val permission: String
            get() = PERMISSIONS.VNC
    }
}