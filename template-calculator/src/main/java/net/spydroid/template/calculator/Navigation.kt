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

package net.spydroid.template.calculator

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.runtime.Composable
import androidx.compose.runtime.CompositionLocalProvider
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import net.spydroid.core.data.common.LocalGlobalViewModel
import net.spydroid.template.calculator.presentation.HomeScreen

@Composable
fun CalculatorNavigation() {
    val globalViewModel = LocalGlobalViewModel.current
    val navController = rememberNavController()

    Scaffold {
        Box(modifier = Modifier
            .fillMaxSize()
            .background(color = Color(0xFF000214))
            .padding(it)
        ) {
            NavHost(navController = navController, startDestination = "/home") {
                composable("/home") {
                    CompositionLocalProvider(LocalGlobalViewModel provides globalViewModel) {
                        HomeScreen()
                    }
                }
            }
        }
    }
}