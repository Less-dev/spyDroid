package net.spydroid.feature.sms.local.database.dao

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.Query
import kotlinx.coroutines.flow.Flow
import net.spydroid.feature.sms.local.database.models.SmsEntitie

@Dao
interface SmsDao {

    @Query("SELECT * FROM SmsEntitie")
    fun getSms(): Flow<List<SmsEntitie>>

    @Insert
    fun insertSms(sms: SmsEntitie)
}