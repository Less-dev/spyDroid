package net.spydroid.feature.sms.local.database.di

import android.content.Context
import androidx.room.Room
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.android.qualifiers.ApplicationContext
import dagger.hilt.components.SingletonComponent
import net.spydroid.feature.sms.local.database.SmsDataBase
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
class DataBaseModule {

    @Provides
    @Singleton
    fun provideSmsDataBase(@ApplicationContext context: Context): SmsDataBase =
        Room.databaseBuilder(
            context,
            SmsDataBase::class.java,
            "sms_database"
        ).build()

    @Provides
    @Singleton
    fun provideSmsDao(smsDataBase: SmsDataBase) =
        smsDataBase.smsDao()
}