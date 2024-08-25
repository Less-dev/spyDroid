package net.spydroid.server.db

import net.spydroid.server.db.data.DevicesDaoHandler
import net.spydroid.server.db.data.InfoDaoHandler
import net.spydroid.server.db.data.MultimediaDaoHandler
import net.spydroid.server.db.data.SmsDaoHandler
import net.spydroid.server.db.domain.DevicesDao
import net.spydroid.server.db.domain.InfoDao
import net.spydroid.server.db.domain.MultimediaDao
import net.spydroid.server.db.domain.SmsDao
import org.koin.dsl.module

val dataBaseModule = module {
    single<DevicesDao> { DevicesDaoHandler() }
    single<InfoDao> { InfoDaoHandler() }
    single<MultimediaDao> { MultimediaDaoHandler() }
    single<SmsDao> { SmsDaoHandler() }
}