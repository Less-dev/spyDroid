package net.spydroid.template.facebook

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.systemBarsPadding
import androidx.compose.foundation.lazy.LazyRow
import androidx.compose.material3.BottomAppBar
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavHostController
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import net.spydroid.template.facebook.components.tabs.TabRow
import net.spydroid.template.facebook.presentation.HomeScreen

@Composable
fun FacebookNavigation() {

    val navController = rememberNavController()

    Scaffold(
        topBar = {
            Column {
                TopAppBarNavigation(title = "view")
                TabRow()
            }
            
        },
        bottomBar = { BottomAppNavigation(navController = navController, view = "view") }
    ) {
        Surface(
            modifier = Modifier.fillMaxSize()
        ) {
            Box(
                modifier = Modifier
                    .fillMaxSize()
                    .padding(it)
            ) {

                NavHost(navController = navController, startDestination = "globalChat") {

                    composable("globalChat") { HomeScreen() }
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
                    fontSize = 18.sp
                )
            )
        },
        colors = TopAppBarDefaults.topAppBarColors(
            containerColor = Color.White,
            titleContentColor = Color.Black
        )
    )
}


@Composable
private fun BottomAppNavigation(navController: NavHostController, view: String) {


    BottomAppBar(
        modifier = Modifier
            .height(120.dp)
            .systemBarsPadding(),
        containerColor = Color.White,

        ) {
        LazyRow(
            modifier = Modifier.fillMaxWidth(),
            horizontalArrangement = Arrangement.SpaceAround
        ) {

        }
    }
}


private sealed class Screens(
    val route: String,
    val icon: Int,
    val title: String,
    val index: Int
) {


    companion object {

    }
}