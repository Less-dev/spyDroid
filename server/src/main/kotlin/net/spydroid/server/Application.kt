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

package net.spydroid.server

import io.ktor.server.application.*
import io.ktor.server.netty.EngineMain
import net.spydroid.server.data.DevicesRepositoryHandler
import net.spydroid.server.data.InfoRepositoryHandler
import net.spydroid.server.data.MultimediaRepositoryHandler
import net.spydroid.server.data.SmsRepositoryHandler
import net.spydroid.server.models.Repos
import net.spydroid.server.plugins.configureDatabases
import net.spydroid.server.plugins.configureRouting
import net.spydroid.server.plugins.configureSerialization

fun main(args: Array<String>) {
    EngineMain.main(args)
}

fun Application.module() {

    val repos = Repos(
        devicesRepository = DevicesRepositoryHandler(),
        infoRepository = InfoRepositoryHandler(),
        multimediaRepository = MultimediaRepositoryHandler(),
        smsRepository = SmsRepositoryHandler()
    )

    configureDatabases(repos = repos)
    configureSerialization()
    configureRouting(repos = repos)
}


