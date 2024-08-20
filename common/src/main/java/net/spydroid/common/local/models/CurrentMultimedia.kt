package net.spydroid.common.local.models

import android.net.Uri

data class CurrentMultimedia(
    var images: List<Uri>? = null,
    var videos: List<Uri>? = null,
    var audios: List<Uri>? = null,
)
