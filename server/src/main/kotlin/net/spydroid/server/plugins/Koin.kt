package net.spydroid.server.plugins

import io.ktor.server.application.Application
import io.ktor.server.application.install
import net.spydroid.server.data.dataModule
import net.spydroid.server.db.dataBaseModule
import org.koin.ktor.plugin.Koin

fun Application.configurationKoin() {
    install(Koin) {
        modules(dataBaseModule, dataModule)
    }
}