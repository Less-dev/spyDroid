package net.spydroid.feature.sms.local.database

import androidx.room.Database
import androidx.room.RoomDatabase
import net.spydroid.feature.sms.local.database.dao.SmsDao
import net.spydroid.feature.sms.local.database.models.SmsEntitie

@Database(entities = [SmsEntitie::class], version = 2)
abstract class SmsDataBase: RoomDatabase() {
    abstract fun smsDao(): SmsDao
}