package net.spydroid.template.facebook


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


