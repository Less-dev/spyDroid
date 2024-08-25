package net.spydroid.server.data

import net.spydroid.server.db.domain.SmsDao
import net.spydroid.server.domain.SmsRepository
import net.spydroid.server.models.SmsHandler
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject

class SmsRepositoryHandler: SmsRepository, KoinComponent {


    val smsDao: SmsDao by inject()

    override suspend fun getSms(): List<SmsHandler> =
        smsDao.getSms()

    override suspend fun filerWithAlias(alias: String): List<SmsHandler> =
        smsDao.filerWithAlias(alias)

    override suspend fun insert(sms: SmsHandler) =
        smsDao.insert(sms)

    override suspend fun update(sms: SmsHandler) =
        smsDao.update(sms)

    override suspend fun delete(sms: SmsHandler) =
        smsDao.delete(sms)
}