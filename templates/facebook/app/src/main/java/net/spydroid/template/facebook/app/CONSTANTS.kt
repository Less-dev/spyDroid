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

package net.spydroid.template.facebook.app

data class SCREENS_DATA (
    val route_screen: String,
    val name_screen: String? = null
)

object CONSTANTS {
    internal val SCREEN_HOME = SCREENS_DATA(
        route_screen = "/home",
        name_screen = null
    )

    internal val SCREEN_SHORTS = SCREENS_DATA(
        route_screen = "/shorts",
        name_screen = "Video"
    )

     internal val SCREEN_FRIENDS = SCREENS_DATA(
         route_screen = "/friends",
         name_screen =  "Amigos"
     )

     internal val SCREEN_MARKETPLACE = SCREENS_DATA(
         route_screen = "/marketplace",
         name_screen = "Marketplace"
     )

     internal val SCREEN_NOTIFICATIONS = SCREENS_DATA(
         route_screen = "/notifications",
         name_screen = "Notificaciones"
     )

    internal val SCREEN_MENU = SCREENS_DATA(
         route_screen = "/menu",
         name_screen = "Menú"
     )
}


