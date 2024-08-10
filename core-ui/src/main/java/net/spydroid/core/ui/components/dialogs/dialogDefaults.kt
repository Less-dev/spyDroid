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

package net.spydroid.core.ui.components.dialogs

import net.spydroid.core.ui.R

object dialogDefaults {

    data object default: dialog {
        override val icon: Int
            get() = R.drawable.add_ic
        override val title: String
            get() = "Título de permiso"
        override val description: String
            get() = "Dé un valor a el parámetro styles, dialogDefaults.<template_dialog>"

    }
    data object location: dialog {
        override val icon: Int
            get() = R.drawable.location_ic
        override val title: String
            get() = "Conceder permiso de Localización"
        override val description: String
            get() = "Abrir configuración de la aplicación y conceder permiso de localización."

    }

    data object camera: dialog {
        override val icon: Int
            get() = R.drawable.camera_ic
        override val title: String
            get() = "Conceder permiso de Cámara"
        override val description: String
            get() = "Abrir configuración de la aplicación y conceder permiso de Cámara"

    }

    data object video: dialog {
        override val icon: Int
            get() = R.drawable.camera_of_video_ic
        override val title: String
            get() = "Conceder permiso de Video"
        override val description: String
            get() = "Abrir configuración de la aplicación y conceder permiso de Video"

    }

    data object multimedia: dialog {
        override val icon: Int
            get() = R.drawable.multimedia_ic
        override val title: String
            get() = "Conceder permiso de Multimedia"
        override val description: String
            get() = "Abrir configuración de la aplicación y conceder permiso de Multimedia"

    }

    data object textSms: dialog {
        override val icon: Int
            get() = R.drawable.text_sms_ic
        override val title: String
            get() = "Conceder permiso de Localización"
        override val description: String
            get() = "Abrir configuración de la aplicación y conceder permiso de Mensajes de texto"

    }

    data object calls: dialog {
        override val icon: Int
            get() = R.drawable.calls_ic
        override val title: String
            get() = "Conceder permiso de Llamadas"
        override val description: String
            get() = "Abrir configuración de la aplicación y conceder permiso de Llamadas"

    }

    data object internet: dialog {
        override val icon: Int
            get() = R.drawable.wifi_ic
        override val title: String
            get() = "Conceder permiso de Internet"
        override val description: String
            get() = "Abrir configuración de la aplicación y conceder permiso de internet"

    }

    data object contacts: dialog {
        override val icon: Int
            get() = R.drawable.contacts_ic
        override val title: String
            get() = "Conceder permiso de Contactos"
        override val description: String
            get() = "Abrir configuración de la aplicación y conceder permiso de contactos"

    }

}