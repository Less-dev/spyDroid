package net.spydroid.template.facebook.components.tabs

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.size
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Icon
import androidx.compose.material3.TabRow
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.UiComposable
import net.spydroid.template.facebook.presentation.HomeScreen
import androidx.compose.material3.Tab
import androidx.compose.material3.TabRowDefaults
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.unit.dp
import net.spydroid.core.ui.R

@Composable
fun TabRow() {
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
                HorizontalDivider(Modifier
                    .height(2.dp)
                    .tabIndicatorOffset(tabPositions[tabIndex]),
                    color = Color.Blue
                )
            }

        },
        divider = {}
    ) {
        tabs.forEachIndexed { index, icon ->
            Tab(selected = tabIndex == index, onClick = { tabIndex = index }) {
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