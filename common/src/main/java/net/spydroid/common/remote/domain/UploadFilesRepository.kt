package net.spydroid.common.remote.domain

import android.content.Context
import java.io.File

// This repository upload files in the server
interface UploadFilesRepository {
    fun insertFile(
        context: Context,
        file: File,
        type: String,
        alias: String
    )
}