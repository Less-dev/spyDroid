package net.spydroid.server

import io.ktor.server.application.*
import io.ktor.server.netty.EngineMain
import net.spydroid.server.plugins.configureRouting

fun main(args: Array<String>) {
    EngineMain.main(args)
}

fun Application.module() {
    configureRouting()
}
