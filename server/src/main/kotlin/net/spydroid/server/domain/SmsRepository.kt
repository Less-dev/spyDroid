package net.spydroid.server.domain

import net.spydroid.server.models.SmsHandler

interface SmsRepository {
    suspend fun getSms(): List<SmsHandler>
    suspend fun filerWithAlias(alias: String): List<SmsHandler>
    suspend fun insert(sms: SmsHandler)
    suspend fun update(sms: SmsHandler)
    suspend fun delete(sms: SmsHandler)
}