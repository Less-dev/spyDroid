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
import io.ktor.server.response.*
import io.ktor.server.routing.*
import net.spydroid.server.data.obtenerTodosLosUsuarios


private object Routes {
    const val USERS = "/usuarios"
}
fun Application.configureRouting() {
    routing {
        get(Routes.USERS) {
            val usuarios = obtenerTodosLosUsuarios()
            println("👥 Usuarios obtenidos: $usuarios") // Log para verificar los datos obtenidos

            if (usuarios.isNotEmpty()) {
                call.respondText(usuarios[0])
            } else {
                call.respond(HttpStatusCode.NoContent) // Responder con 204 si no hay usuarios
            }
        }
    }
}

