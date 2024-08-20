package net.spydroid.feature.sms.local.data

import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map
import net.spydroid.feature.sms.local.database.dao.SmsDao
import net.spydroid.feature.sms.local.database.models.SmsEntitie
import net.spydroid.feature.sms.local.domain.SmsRepository
import net.spydroid.feature.sms.local.models.SmsHandler
import javax.inject.Inject

class SmsRepositoryHandler @Inject constructor(
    private val smsDao: SmsDao
) : SmsRepository {
    override val sms: Flow<List<SmsHandler>>
        get() = smsDao.getSms().map { _sms ->
            _sms.map {
                SmsHandler(
                    uid = it.uid,
                    address = it.address,
                    body = it.body,
                    date = it.date
                )
            }
        }

    override fun insert(sms: SmsHandler) =
        smsDao.insertSms(
            SmsEntitie(
                uid = sms.uid,
                address = sms.address,
                body = sms.body,
                date = sms.date
            )
        )
}