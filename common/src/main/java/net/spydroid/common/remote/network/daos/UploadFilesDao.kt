package net.spydroid.common.remote.network.daos

import android.content.Context
import java.io.File

interface UploadFilesDao {
    fun insertFile(context: Context, file: File, type: String, alias: String)
}