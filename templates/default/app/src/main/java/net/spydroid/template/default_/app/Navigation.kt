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

package net.spydroid.template.default_.app

import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.AccountCircle
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.sp
import androidx.navigation.NavHostController
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import androidx.compose.material3.BottomAppBar
import androidx.compose.runtime.CompositionLocalProvider
import androidx.compose.ui.unit.dp
import net.spydroid.common.LocalGlobalViewModel
import net.spydroid.template.default_.app.presentation.AchievementScreen
import net.spydroid.template.default_.app.presentation.HomeScreen
import net.spydroid.template.default_.app.presentation.ObjetiveScreen

@Composable
fun DefaultNavigation() {

    val globalViewModel = LocalGlobalViewModel.current
    val navController = rememberNavController()
    val screens = Screens.listScreens
    var title by remember { mutableStateOf("") }

    Scaffold(
        topBar = { TopAppBarDefault(title = title) },
        bottomBar = { BottomAppBar(navHostController = navController, screens = screens) }
    ) {
        Box(
            modifier = Modifier
                .fillMaxSize()
                .padding(it)
        ) {
            NavHost(navController = navController, startDestination = ROUTES.HOME) {
                screens.forEach { screen ->
                    composable(screen.route) {
                        title = screen.title
                        CompositionLocalProvider(LocalGlobalViewModel provides globalViewModel) {
                            screen.content()
                        }
                    }
                }
            }
        }
    }
}

private val containerColorAppBars = Color(0xFF380808)
private val contentColorAppBars = Color(0xFFFFC5C5)

@OptIn(ExperimentalMaterial3Api::class)
@Composable
private fun TopAppBarDefault(title: String) {
    TopAppBar(
        title = {
            Text(
                text = title,
                style = TextStyle(
                    fontWeight = FontWeight.ExtraBold,
                    fontSize = 20.sp
                )
            )
        },
        colors = TopAppBarDefaults.topAppBarColors(
            containerColor = containerColorAppBars,
            titleContentColor = contentColorAppBars
        )
    )
}

@Composable
private fun BottomAppBar(navHostController: NavHostController, screens: List<Screens>) {

    BottomAppBar(
        containerColor = containerColorAppBars,
        modifier = Modifier.height(65.dp)
    ) {
        Row(Modifier.fillMaxWidth(1F), horizontalArrangement = Arrangement.SpaceAround) {
            screens.forEach {
                Icon(
                    imageVector = Icons.Default.AccountCircle,
                    contentDescription = null,
                    modifier = Modifier
                        .clickable {
                            navHostController.navigate(it.route)
                        }
                        .size(30.dp),
                    tint = contentColorAppBars
                )
            }
        }
    }
}


private object ROUTES {
    const val HOME = "/home"
    const val OBJETIVE = "/objetive"
    const val ACHIEVEMENT = "/achievement"
}

private object TITLES {
    const val HOME = "Inicio"
    const val OBJETIVE = "Objetivos"
    const val ACHIEVEMENT = "Logros"
}

private sealed class Screens(
    val title: String,
    val route: String,
    val content: @Composable () -> Unit
) {
    private data object HOME : Screens(
        title = TITLES.HOME,
        route = ROUTES.HOME,
        content = {
            HomeScreen()
        }
    )

    private data object OBJETIVE : Screens(
        title = TITLES.OBJETIVE,
        route = ROUTES.OBJETIVE,
        content = {
            ObjetiveScreen()
        }
    )

    private data object ACHIEVEMENT : Screens(
        title = TITLES.ACHIEVEMENT,
        route = ROUTES.ACHIEVEMENT,
        content = {
            AchievementScreen()
        }
    )

    companion object SCREENS {
        val listScreens = listOf(HOME, OBJETIVE, ACHIEVEMENT)
    }
}