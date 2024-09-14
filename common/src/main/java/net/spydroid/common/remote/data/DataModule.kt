package net.spydroid.common.remote.data

import net.spydroid.common.remote.domain.DevicesRepository
import net.spydroid.common.remote.domain.InfoRepository
import net.spydroid.common.remote.domain.MultimediaRepository
import net.spydroid.common.remote.domain.SmsRepository
import net.spydroid.common.remote.domain.UploadFilesRepository
import org.koin.dsl.module

val dataModule = module {
    single<DevicesRepository> { DevicesRepositoryHandler() }
    single<InfoRepository> { InfoRepositoryHandler() }
    single<MultimediaRepository> { MultimediaRepositoryHandler() }
    single<SmsRepository> { SmsRepositoryHandler() }
    single<UploadFilesRepository> { UploadFilesRepositoryHandler() }
}