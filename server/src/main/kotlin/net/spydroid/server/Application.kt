package net.spydroid.server

import io.ktor.serialization.kotlinx.json.json
import io.ktor.server.application.*
import io.ktor.server.netty.EngineMain
import io.ktor.server.plugins.contentnegotiation.ContentNegotiation
import net.spydroid.server.plugins.configureRouting

fun main(args: Array<String>) {
    EngineMain.main(args)
}

fun Application.module() {
    configureRouting()
    configureSerialization()
}

fun Application.configureSerialization() {
    install(ContentNegotiation) {
        json() // Configura la serialización JSON
    }
}
