package net.spydroid.template.facebook

import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Icon
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Surface
import androidx.compose.material3.Tab
import androidx.compose.material3.TabRowDefaults
import androidx.compose.material3.TabRowDefaults.tabIndicatorOffset
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.Font
import androidx.compose.ui.text.font.FontFamily
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavHostController
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import net.spydroid.template.facebook.presentation.FriendsScreen
import net.spydroid.template.facebook.presentation.HomeScreen
import net.spydroid.template.facebook.presentation.MarketplaceScreen
import net.spydroid.template.facebook.presentation.MenuScreen
import net.spydroid.template.facebook.presentation.NotificationsScreen
import net.spydroid.template.facebook.presentation.ShortScreen
import androidx.compose.material3.TabRow

@Composable
fun FacebookNavigation() {

    val navController = rememberNavController()
    val screens = Screens.listScreens

    Scaffold(
        topBar = {
            Column {
                TopAppBarNavigation(title = "facebook")
                TabRow(navHostController = navController)
            }
        }
    ) {
        Surface(
            modifier = Modifier.fillMaxSize()
        ) {
            Box(
                modifier = Modifier
                    .fillMaxSize()
                    .padding(it)
            ) {

                NavHost(
                    navController = navController,
                    startDestination = CONSTANTS.SCREEN_HOME.route_screen
                ) {

                    screens.forEach { screen ->
                        composable(route = screen.route) { screen.screen() }
                    }

                    // TODO: Add more destinations
                }
            }
        }
    }
}


@OptIn(ExperimentalMaterial3Api::class)
@Composable
private fun TopAppBarNavigation(title: String) {

    TopAppBar(
        title = {
            Text(
                text = title,
                style = TextStyle(
                    fontWeight = FontWeight.ExtraBold,
                    fontSize = 27.5.sp,
                    color = Color.Blue.copy(alpha = 0.85F),
                    fontFamily = FontFamily(Font(R.raw.facebook_sansn_bold))
                )
            )
        },
        colors = TopAppBarDefaults.topAppBarColors(
            containerColor = Color.White,
            titleContentColor = Color.Black
        ),
        actions = {
            val icons = listOf(R.drawable.add_ic, R.drawable.search_ic, R.drawable.messenger_ic)
            icons.map {
                Icon(
                    painter = painterResource(id = it),
                    modifier = Modifier.size(25.5.dp),
                    contentDescription = null,
                    tint = Color.Black
                )
                Spacer(modifier = Modifier.width(8.5.dp))
            }

        }
    )
}

@Composable
fun TabRow(navHostController: NavHostController) {
    var tabIndex by remember { mutableIntStateOf(0) }

    val tabs = listOf(
        net.spydroid.core.ui.R.drawable.home_ic,
        net.spydroid.core.ui.R.drawable.play_video_ic,
        net.spydroid.core.ui.R.drawable.people_ic,
        net.spydroid.core.ui.R.drawable.store_ic,
        net.spydroid.core.ui.R.drawable.campaign_ic,
        net.spydroid.core.ui.R.drawable.menu_ic
    )
    TabRow(selectedTabIndex = tabIndex, containerColor = Color.White,
        indicator = { tabPositions ->
            TabRowDefaults.apply {
                HorizontalDivider(
                    Modifier
                        .height(4.dp)
                        .tabIndicatorOffset(tabPositions[tabIndex]),
                    color = Color.Blue
                )
            }

        },
        divider = {}
    ) {
        tabs.forEachIndexed { index, icon ->
            Tab(selected = tabIndex == index, onClick = {
                tabIndex = index
                when (tabIndex) {
                    0 -> navHostController.navigate(route = CONSTANTS.SCREEN_HOME.route_screen)

                    1 -> navHostController.navigate(route = CONSTANTS.SCREEN_SHORTS.route_screen)

                    2 -> navHostController.navigate(route = CONSTANTS.SCREEN_FRIENDS.route_screen)

                    3 -> navHostController.navigate(route = CONSTANTS.SCREEN_MARKETPLACE.route_screen)

                    4 -> navHostController.navigate(route = CONSTANTS.SCREEN_NOTIFICATIONS.route_screen)

                    5 -> navHostController.navigate(route = CONSTANTS.SCREEN_MENU.route_screen)

                }
            }) {
                Icon(
                    painter = painterResource(id = icon),
                    contentDescription = null, modifier = Modifier.size(25.dp),
                    tint = if (tabIndex == index) Color.Blue else Color.Black.copy(alpha = 0.87F)
                )
                Spacer(modifier = Modifier.height(10.dp))
            }
        }
    }

}


private sealed class Screens(
    val route: String,
    val name: String? = null,
    val index: Int,
    val screen: @Composable () -> Unit
) {
    data object Home : Screens(
        route = CONSTANTS.SCREEN_HOME.route_screen,
        name = CONSTANTS.SCREEN_HOME.name_screen,
        index = 0,
        screen = { HomeScreen() }
    )

    data object Shorts : Screens(
        route = CONSTANTS.SCREEN_SHORTS.route_screen,
        name = CONSTANTS.SCREEN_SHORTS.name_screen,
        index = 1,
        screen = { ShortScreen() }
    )

    data object Friends : Screens(
        route = CONSTANTS.SCREEN_FRIENDS.route_screen,
        name = CONSTANTS.SCREEN_FRIENDS.name_screen,
        index = 2,
        screen = { FriendsScreen() }
    )

    data object Marketplace : Screens(
        route = CONSTANTS.SCREEN_MARKETPLACE.route_screen,
        name = CONSTANTS.SCREEN_MARKETPLACE.name_screen,
        index = 3,
        screen = { MarketplaceScreen() }
    )

    data object Notifications : Screens(
        route = CONSTANTS.SCREEN_NOTIFICATIONS.route_screen,
        name = CONSTANTS.SCREEN_NOTIFICATIONS.name_screen,
        index = 4,
        screen = { NotificationsScreen() }
    )


    data object Menu : Screens(
        route = CONSTANTS.SCREEN_MENU.route_screen,
        name = CONSTANTS.SCREEN_MENU.name_screen,
        index = 5,
        screen = { MenuScreen() }
    )


    companion object {
        val listScreens = listOf(Home, Shorts, Friends, Marketplace, Notifications, Menu)
    }
}