package net.spydroid.feature.sms.local.di

import dagger.Binds
import dagger.Module
import dagger.hilt.InstallIn
import dagger.hilt.components.SingletonComponent
import net.spydroid.feature.sms.local.data.SmsRepositoryHandler
import net.spydroid.feature.sms.local.domain.SmsRepository
import javax.inject.Singleton


@Module
@InstallIn(SingletonComponent::class)
interface DataModule {
    @Singleton
    @Binds
    fun provideSmsRepository(smsRepositoryHandler: SmsRepositoryHandler): SmsRepository
}