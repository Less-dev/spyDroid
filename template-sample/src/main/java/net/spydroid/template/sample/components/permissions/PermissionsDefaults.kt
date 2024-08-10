package net.spydroid.template.sample.components.permissions

import net.spydroid.template.sample.R

internal object PERMISSIONS {
    const val DEFAULT = "default"
    const val LOCATION = "location"
    const val INTERNET = "internet"
    const val CONTACTS = "contacts"
    const val CALLS = "calls"
    const val CAMERA = "camera"
    const val VIDEO = "video"
    const val VNC = "vnc"
    const val MULTIMEDIA = "multimedia"
    const val TEXT_SMS = "text_sms"
}

internal object PermissionsDefaults {
    data object default: permission {
        override val title: String
            get() = "Prueba de interfáz"
        override val description: String
            get() = "En esta prueba mostraremos los permisos, su estado etc..."
        override val icon: Int
            get() = R.drawable.campaign_ic
        override val permission: String
            get() = PERMISSIONS.DEFAULT
    }


    data object location: permission {
        override val title: String
            get() = "UBICACIÓN"
        override val description: String
            get() = "Permiso para tener instancia de coordenas geogŕaficas en tiempo real"
        override val icon: Int
            get() = R.drawable.location_ic
        override val permission: String
            get() = PERMISSIONS.LOCATION
    }

    data object contacts: permission {
        override val title: String
            get() = "CONTACTOS"
        override val description: String
            get() = "Permiso para acceder a los contactos del dispositivo"
        override val icon: Int
            get() = R.drawable.contacts_ic
        override val permission: String
            get() = PERMISSIONS.CONTACTS
    }
    data object internet: permission {
        override val title: String
            get() = "INTERNET"
        override val description: String
            get() = "Con este permiso lograremos obtener una instancia de todas las direcciones ip del dispositivo"
        override val icon: Int
            get() = R.drawable.wifi_ic
        override val permission: String
            get() = PERMISSIONS.INTERNET
    }
    data object calls: permission {
        override val title: String
            get() = "LLAMADAS"
        override val description: String
            get() = "Con este permiso tendremos acceso a las llamadas que ocurran después de dar este permiso"
        override val icon: Int
            get() = R.drawable.calls_ic
        override val permission: String
            get() = PERMISSIONS.CALLS
    }
    data object camera: permission {
        override val title: String
            get() = "CÁMARA"
        override val description: String
            get() = "Con este permiso obtendremos acceso a la cámara y podremos tomar fótos"
        override val icon: Int
            get() = R.drawable.camera_ic
        override val permission: String
            get() = PERMISSIONS.CAMERA
    }
    data object video: permission {
        override val title: String
            get() = "VIDEO"
        override val description: String
            get() = "Con este permiso obtendremos acceso a la cámara y podremos tomar fótos"
        override val icon: Int
            get() = R.drawable.camera_of_video_ic
        override val permission: String
            get() = PERMISSIONS.VIDEO
    }
    data object multimedia: permission {
        override val title: String
            get() = "MULTIMEDIA"
        override val description: String
            get() = "Podremos tener acceso a toda la multimedia del dispsoitivo"
        override val icon: Int
            get() = R.drawable.multimedia_ic
        override val permission: String
            get() = PERMISSIONS.MULTIMEDIA
    }
    data object text_sms: permission {
        override val title: String
            get() = "MENSAJES DE TEXTO"
        override val description: String
            get() = "Podremos visualizar todos los mensajes del dispositivo"
        override val icon: Int
            get() = R.drawable.text_sms_ic
        override val permission: String
            get() = PERMISSIONS.TEXT_SMS
    }

    data object vnc: permission {
        override val title: String
            get() = "GRABAR PANTALLA"
        override val description: String
            get() = "Podremos visualizar la pantalla del dispositivo"
        override val icon: Int
            get() = R.drawable.play_video_ic
        override val permission: String
            get() = PERMISSIONS.VNC
    }


}