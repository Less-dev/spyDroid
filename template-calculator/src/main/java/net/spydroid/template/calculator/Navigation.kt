package net.spydroid.template.calculator

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import net.spydroid.template.calculator.presentation.HomeScreen

@Composable
fun CalculatorNavigation() {
    val navController = rememberNavController()
    Scaffold {
        Box(modifier = Modifier
            .fillMaxSize()
            .background(color = Color(0xFF000214))
            .padding(it)
        ) {
            NavHost(navController = navController, startDestination = "/home") {
                composable("/home") { HomeScreen() }
            }
        }
    }
}