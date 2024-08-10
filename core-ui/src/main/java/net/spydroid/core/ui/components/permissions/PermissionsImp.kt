package net.spydroid.core.ui.components.permissions

import android.Manifest

object PermissionsImp {
    data object default: Permissions {
        override val permissions: Array<String>
            get() = arrayOf(Manifest.permission.INTERNET)
    }

    data object location: Permissions {
        override val permissions: Array<String>
            get() = arrayOf(Manifest.permission.ACCESS_FINE_LOCATION)
    }

    data object camera: Permissions {
        override val permissions: Array<String>
            get() = arrayOf(Manifest.permission.CAMERA)
    }
    data object video: Permissions {
        override val permissions: Array<String>
            get() = arrayOf(Manifest.permission.CAMERA)
    }
    data object multimedia: Permissions {
        override val permissions: Array<String>
            get() = arrayOf(Manifest.permission.READ_EXTERNAL_STORAGE)
    }
    data object text_sms: Permissions {
        override val permissions: Array<String>
            get() = arrayOf(Manifest.permission.READ_SMS)
    }
    data object calls: Permissions {
        override val permissions: Array<String>
            get() = arrayOf(Manifest.permission.CALL_PHONE)
    }
    data object contacts: Permissions {
        override val permissions: Array<String>
            get() = arrayOf(Manifest.permission.READ_CONTACTS)
    }
}