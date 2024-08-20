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

package net.spydroid.feature.sms

import android.Manifest
import android.content.ContentResolver
import android.content.Context
import android.content.pm.PackageManager
import android.database.Cursor
import android.icu.text.SimpleDateFormat
import android.net.Uri
import android.provider.Telephony
import android.util.Log
import androidx.core.content.ContextCompat
import androidx.work.Worker
import androidx.work.WorkerParameters
import net.spydroid.common.local.LocalDataProvider
import net.spydroid.common.local.models.CurrentSms
import net.spydroid.feature.sms.local.domain.SmsRepository
import net.spydroid.feature.sms.local.models.SmsHandler
import java.util.Date
import java.util.Locale
import javax.inject.Inject
class SmsWork(private val context: Context, workerParams: WorkerParameters) :
    Worker(context, workerParams) {

    private val contentResolver: ContentResolver = context.contentResolver
    private val localDataProvider = LocalDataProvider.current(context)

    override fun doWork(): Result {
        try {
            val uri: Uri = Telephony.Sms.CONTENT_URI
            val cursor: Cursor? = contentResolver.query(uri, null, null, null, null)

            cursor?.use {
                val indexBody = it.getColumnIndex(Telephony.Sms.BODY)
                val indexAddress = it.getColumnIndex(Telephony.Sms.ADDRESS)
                val indexDate = it.getColumnIndex(Telephony.Sms.DATE)

                while (it.moveToNext()) {
                    val body = it.getString(indexBody)
                    val address = it.getString(indexAddress)
                    val date = it.getLong(indexDate)

                    val dateSent = Date(date)
                    val format = SimpleDateFormat("dd/MM/yyyy HH:mm:ss", Locale.getDefault())
                    val dateSentFormatted = format.format(dateSent)

                    localDataProvider.setSmsCurrent(
                        CurrentSms(
                            address = address,
                            body = body,
                            date = dateSentFormatted
                        )
                    )
                }
            } ?: run {
                return Result.failure()
            }
            return Result.success()
        } catch (e: Exception) {
            return Result.failure()
        }
    }
}
