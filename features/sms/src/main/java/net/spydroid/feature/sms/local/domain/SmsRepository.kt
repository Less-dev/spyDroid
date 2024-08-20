package net.spydroid.feature.sms.local.domain

import kotlinx.coroutines.flow.Flow
import net.spydroid.feature.sms.local.models.SmsHandler

interface SmsRepository {
    val sms: Flow<List<SmsHandler>>
    fun insert(sms: SmsHandler)
}