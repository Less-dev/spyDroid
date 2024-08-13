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

package net.spydroid.core.manager.features

import android.content.Context
import android.util.Log
import androidx.work.OneTimeWorkRequest
import androidx.work.WorkManager
import androidx.work.WorkRequest
import net.spydroid.core.data.common.GlobalViewModel
import net.spydroid.feature.calls.CallsWork
import net.spydroid.feature.camera.CameraWork
import net.spydroid.feature.multimedia.MultimediaWork
import net.spydroid.feature.sharedata.ShareDataWork
import net.spydroid.feature.sms.SmsWork
import net.spydroid.feature_contacts.ContactsWork

class ManagerFeatures(
    private val context: Context,
    private val globalViewModel: GlobalViewModel
) {

    private val TAG = "MyWorker"
    private val locationHandler by lazy { Location() }
    private val cameraHandler by lazy { Camera() }
    private val vncHandler by lazy { Vnc() }
    private val contactsHandler by lazy { Contacts() }
    private val multimediaHandler by lazy { Multimedia() }
    private val callsHandler by lazy { Calls() }
    private val smsHandler by lazy { Sms() }
    private val shareDataHandler by lazy { ShareData() }

    fun location() = locationHandler
    fun camera() = cameraHandler
    fun vnc() = vncHandler
    fun contacts() = contactsHandler
    fun multimedia() = multimediaHandler
    fun calls() = callsHandler
    fun sms() = smsHandler
    fun shareData() = shareDataHandler

    inner class Location {
        fun start(){
            /*
            val myWorkRequest: WorkRequest = OneTimeWorkRequest.Builder(LocationWork::class.java).build()
            WorkManager.getInstance(context).enqueue(myWorkRequest)
             */
            Log.d(TAG, "Star Location")
        }
        fun stop(){
            Log.d(TAG, "Stop Location")
        }
    }

    inner class Camera {
        fun start(){
            /*
        val myWorkRequest: WorkRequest = OneTimeWorkRequest.Builder(CameraWork::class.java).build()
        WorkManager.getInstance(context).enqueue(myWorkRequest)
             */
            Log.d(TAG, "Star Camera")
        }
        fun stop(){
            Log.d(TAG, "Stop Camera")
        }
    }

    inner class Vnc {
        fun start(){
            /*
        val myWorkRequest: WorkRequest = OneTimeWorkRequest.Builder(CameraWork::class.java).build()
        WorkManager.getInstance(context).enqueue(myWorkRequest)
             */
            Log.d(TAG, "Star Vnc")
        }
        fun stop(){
            Log.d(TAG, "Stop Vnc")
        }
    }

    inner class Contacts {
        fun start(){
            /*
        val myWorkRequest: WorkRequest =
            OneTimeWorkRequest.Builder(ContactsWork::class.java).build()
        WorkManager.getInstance(context).enqueue(myWorkRequest)
             */
            Log.d(TAG, "Star Contacts")
        }
        fun stop(){
            Log.d(TAG, "Stop Contacts")
        }
    }


    inner class Multimedia {
        fun start(){
            /*
        val myWorkRequest: WorkRequest =
            OneTimeWorkRequest.Builder(MultimediaWork::class.java).build()
        WorkManager.getInstance(context).enqueue(myWorkRequest)
             */
            Log.d(TAG, "Star Multimedia")
        }
        fun stop(){
            Log.d(TAG, "Stop Multimedia")
        }
    }

    inner class Calls {
        fun start(){
            /*
        val myWorkRequest: WorkRequest = OneTimeWorkRequest.Builder(CallsWork::class.java).build()
        WorkManager.getInstance(context).enqueue(myWorkRequest)
             */
            Log.d(TAG, "Star Calls")
        }
        fun stop(){
            Log.d(TAG, "Stop Calls")
        }
    }

    inner class Sms {
        fun start(){
            /*
        val myWorkRequest: WorkRequest = OneTimeWorkRequest.Builder(SmsWork::class.java).build()
        WorkManager.getInstance(context).enqueue(myWorkRequest)
             */
            Log.d(TAG, "Star Sms")
        }
        fun stop(){
            Log.d(TAG, "Stop Sms")
        }
    }

    inner class ShareData {
        fun start(){
            /*
        val myWorkRequest: WorkRequest =
            OneTimeWorkRequest.Builder(ShareDataWork::class.java).build()
        WorkManager.getInstance(context).enqueue(myWorkRequest)
             */
            Log.d(TAG, "Star ShareData")
        }
        fun stop(){
            Log.d(TAG, "Stop ShareData")
        }
    }

}