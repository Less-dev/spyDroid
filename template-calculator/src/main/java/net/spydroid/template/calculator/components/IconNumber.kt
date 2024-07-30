package net.spydroid.template.calculator.components

import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.TextUnit
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp


@Composable
internal fun IconNumber(
    number: String,
    fontSize: TextUnit = 50.sp,
    color: Color = Color.Gray.copy(alpha = 0.85F),
    onClick: () -> Unit
) {
    Box(
        modifier = Modifier
            .size(80.dp)
            .clip(CircleShape)
            .border(width = 2.dp, color = Color(0x61FFADAD), shape = CircleShape)
            .background(color = color)
            .clickable { onClick() },
        contentAlignment = Alignment.Center
    ) {
        Text(
            text = number, style = TextStyle(
                color = Color.Black.copy(alpha = 0.8F),
                fontSize = fontSize,
                fontWeight = FontWeight.ExtraBold
            )
        )
    }
}