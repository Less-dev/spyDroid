package net.spydroid.server.data

import net.spydroid.server.domain.DevicesRepository
import net.spydroid.server.domain.InfoRepository
import net.spydroid.server.domain.MultimediaRepository
import net.spydroid.server.domain.SmsRepository
import org.koin.dsl.module


val dataModule = module {
    single<DevicesRepository> { DevicesRepositoryHandler() }
    single<InfoRepository> { InfoRepositoryHandler() }
    single<SmsRepository> { SmsRepositoryHandler() }
    single<MultimediaRepository> { MultimediaRepositoryHandler() }
}