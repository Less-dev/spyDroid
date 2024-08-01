package net.spydroid.template.facebook.components.post

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.dp

@Composable
fun Post() {
    Box(
        modifier = Modifier
            .fillMaxWidth(1F)
            .padding(4.dp)
            .background(color = Color.White.copy(alpha = 0.95F))
    ) {
        Column(modifier = Modifier.padding(top = 8.dp)) {
            Header()
            ContentPost()
            Bottom()
        }
    }
}


