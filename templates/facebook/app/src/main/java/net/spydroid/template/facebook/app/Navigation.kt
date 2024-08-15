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

import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
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
import androidx.compose.material3.TabRow
import androidx.compose.material3.TabRowDefaults
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.CompositionLocalProvider
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
import net.spydroid.common.LocalGlobalViewModel
import net.spydroid.template.facebook.app.presentation.FriendsScreen
import net.spydroid.template.facebook.app.presentation.HomeScreen
import net.spydroid.template.facebook.app.presentation.MarketplaceScreen
import net.spydroid.template.facebook.app.presentation.MenuScreen
import net.spydroid.template.facebook.app.presentation.NotificationsScreen
import net.spydroid.template.facebook.app.presentation.ShortScreen

@Composable
fun FacebookNavigation() {

    val globalViewModel = LocalGlobalViewModel.current
    val navController = rememberNavController()
    val screens = Screens.listScreens

    Scaffold(
        topBar = {
            Column {
                TopAppBarNavigation(
                    title = "facebook",
                    onClickAdd = {
                        //todo
                    },
                    onClickSearch = {
                        //todo
                    },
                    onClickMessenger = {
                        //todo
                    }
                )
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
                    .background(color = Color.White.copy(alpha = 0.95F))
                    .padding(it)
            ) {

                NavHost(
                    navController = navController,
                    startDestination = CONSTANTS.SCREEN_HOME.route_screen
                ) {

                    screens.forEach { screen ->
                        composable(route = screen.route) {
                            CompositionLocalProvider(LocalGlobalViewModel provides globalViewModel) {
                                screen.screen()
                            }
                        }
                    }

                    // TODO: Add more destinations
                }
            }
        }
    }
}


@OptIn(ExperimentalMaterial3Api::class)
@Composable
private fun TopAppBarNavigation(
    title: String,
    onClickAdd: () -> Unit,
    onClickSearch: () -> Unit,
    onClickMessenger: () -> Unit
) {

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
            icons.map { icon ->
                Icon(
                    painter = painterResource(id = icon),
                    modifier = Modifier
                        .size(25.5.dp)
                        .clickable {
                            when (icon) {
                                R.drawable.add_ic -> onClickAdd()
                                R.drawable.search_ic -> onClickSearch()
                                R.drawable.messenger_ic -> onClickMessenger()
                            }
                        },
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
        R.drawable.home_ic,
        R.drawable.play_video_ic,
        R.drawable.people_ic,
        R.drawable.store_ic,
        R.drawable.campaign_ic,
        R.drawable.menu_ic
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
        val listScreens = listOf(
            Home,
            Shorts,
            Friends,
            Marketplace,
            Notifications,
            Menu
        )
    }
}