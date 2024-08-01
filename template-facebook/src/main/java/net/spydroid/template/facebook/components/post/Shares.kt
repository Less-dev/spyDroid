package net.spydroid.template.facebook.components.post

import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.TextStyle


@Composable
internal fun Shares(shares: String? = null) {
    Text(
        text = "${shares ?: 5} compartidos", style = TextStyle(
            color = Color.Black.copy(alpha = 0.65F)
        )
    )
}