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
import android.provider.MediaStore
import androidx.work.Worker
import androidx.work.WorkerParameters
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import net.spydroid.common.local.LocalDataProvider

class MultimediaWork(
    private val context: Context,
    workerParams: WorkerParameters
) :
    Worker(context, workerParams) {

    private val localDataProvider = LocalDataProvider.current(context)

    override fun doWork(): Result {
        try {

            val scope = CoroutineScope(Dispatchers.Main)

            // Launch a coroutine for loading images
            scope.launch {
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
                        val idColumn = it.getColumnIndexOrThrow(MediaStore.Images.Media._ID)
                        while (it.moveToNext()) {
                            val id = it.getLong(idColumn)
                            val imageUri = ContentUris.withAppendedId(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, id)
                            localDataProvider.setMultimediaCurrent(image = imageUri) // add image to list in LocalDataProvider
                        }
                    }
                }
            }

            scope.launch {
                withContext(Dispatchers.IO) {
                    val projectionVideo = arrayOf(MediaStore.Video.Media._ID)
                    val cursorVideo = context.contentResolver.query(
                        MediaStore.Video.Media.EXTERNAL_CONTENT_URI,
                        projectionVideo,
                        null,
                        null,
                        MediaStore.Video.Media.DATE_ADDED + " DESC"
                    )

                    cursorVideo?.use {
                        val idColumn = it.getColumnIndexOrThrow(MediaStore.Video.Media._ID)
                        while (it.moveToNext()) {
                            val id = it.getLong(idColumn)
                            val uriVideo = ContentUris.withAppendedId(MediaStore.Video.Media.EXTERNAL_CONTENT_URI, id)
                            localDataProvider.setMultimediaCurrent(video = uriVideo)
                        }
                    }
                }
            }

            scope.launch {
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
                        val idColumn = it.getColumnIndexOrThrow(MediaStore.Audio.Media._ID)
                        while (it.moveToNext()) {
                            val id = it.getLong(idColumn)
                            val uriAudio = ContentUris.withAppendedId(MediaStore.Audio.Media.EXTERNAL_CONTENT_URI, id)
                            localDataProvider.setMultimediaCurrent(audio = uriAudio)
                        }
                    }
                }
            }

            return Result.success()
        } catch (e: Exception) {
            // Si hubo un fallo en el trabajo
            return Result.failure()
        }
    }
}