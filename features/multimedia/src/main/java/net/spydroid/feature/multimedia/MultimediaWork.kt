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
import net.spydroid.common.local.LocalDataProvider

class MultimediaWork(
    private val context: Context,
    workerParams: WorkerParameters
) :
    Worker(context, workerParams) {

    private val localDataProvider = LocalDataProvider.current(context)

    override fun doWork(): Result {
        try {
            val projection = arrayOf(MediaStore.Images.Media._ID)
            val cursor = context.contentResolver.query(
                MediaStore.Images.Media.EXTERNAL_CONTENT_URI,
                projection,
                null,
                null,
                MediaStore.Images.Media.DATE_ADDED + " DESC"
            )

            cursor?.use {
                val idColumn = it.getColumnIndexOrThrow(MediaStore.Images.Media._ID)
                while (it.moveToNext()) {
                    val id = it.getLong(idColumn)
                    val imageUri = ContentUris.withAppendedId(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, id)
                    localDataProvider.setMultimediaCurrent(image = imageUri) // add image to list in LocalDataProvider
                }
            }

            return Result.success()
        } catch (e: Exception) {
            // Si hubo un fallo en el trabajo
            return Result.failure()
        }
    }
}