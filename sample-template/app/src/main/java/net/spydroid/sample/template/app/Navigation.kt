package net.spydroid.sample.template.app


import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.lazy.LazyRow
import androidx.compose.foundation.lazy.items
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.AddCircle
import androidx.compose.material3.BottomAppBar
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.CompositionLocalProvider
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavHostController
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import net.spydroid.sample.template.app.presentation.ALlPermissionsScreen
import net.spydroid.sample.template.app.presentation.HomeScreen

@Composable
fun SampleNavigation2() {
    val navController = rememberNavController()
    val screens = Screens.listScreens
    var title by remember {
        mutableStateOf("")
    }

    Scaffold(
        topBar = { TopAppBarNavigation(title = title) },
        bottomBar = { BottomAppBarNavigation(navHostController = navController, screens = screens) }
    ) {
        Surface(
            modifier = Modifier.fillMaxSize()
        ) {
            Box(
                modifier = Modifier
                    .fillMaxSize()
                    .padding(it)
            ) {

                NavHost(navController = navController, startDestination = "/home") {
                    screens.forEach { screen ->
                        composable(screen.route) {
                            screen.content()
                            title = screen.title
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
            containerColor = Color(0xFF460000),
            titleContentColor = Color.White
        )
    )
}

@Composable
fun BottomAppBarNavigation(navHostController: NavHostController, screens: List<Screens>) {

    BottomAppBar(
        contentColor = Color(0xFF460000),
        containerColor = Color(0xFF460000),
        modifier = Modifier.height(45.dp)
    ) {
        screens.forEach {
            Spacer(modifier = Modifier.weight(1F))
            Icon(
                imageVector = Icons.Default.AddCircle,
                contentDescription = null,
                modifier = Modifier
                    .size(25.dp)
                    .clickable { navHostController.navigate(it.route) },
                tint = Color.White
            )
            Spacer(modifier = Modifier.weight(1F))
        }
    }
}


sealed class Screens(
    val title: String,
    val route: String,
    val content: @Composable () -> Unit
) {
    data object HOME : Screens(
        title = "INICIO",
        route = "/home",
        content = { HomeScreen() }
    )

    data object PERMISSIONS : Screens(
        title = "ESTADOS DE PERMISOS",
        route = "/permissions",
        content = { ALlPermissionsScreen()}
    )

    companion object {
        val listScreens = listOf(HOME, PERMISSIONS)
    }
}