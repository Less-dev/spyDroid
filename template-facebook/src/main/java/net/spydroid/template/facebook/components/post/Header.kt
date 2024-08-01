package net.spydroid.template.facebook.components.post

import androidx.compose.foundation.Image
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.material3.Icon
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import net.spydroid.template.facebook.R

@Composable
internal fun Header() {
    Row(
        Modifier
            .fillMaxWidth(1F)
    ) {
        ImageProfile(modifier = Modifier.align(Alignment.Top))
        Spacer(modifier = Modifier.width(4.dp))
        NameAndHour(modifier = Modifier.align(Alignment.Top))
        Spacer(modifier = Modifier.weight(1F))
        Options {

        }
    }
}


@Composable
private fun ImageProfile(modifier: Modifier = Modifier, image: Int? = null) {
    Image(
        painter = painterResource(id = image ?: R.drawable.profile_default),
        contentDescription = null, modifier = modifier
            .clip(
                CircleShape
            )
            .size(40.dp)
    )
}

@Composable
private fun NameAndHour(modifier: Modifier = Modifier, name: String? = null, hour: String? = null) {
    Column(modifier = modifier) {
        Text(
            text = name ?: "Unknown", style = TextStyle(
                color = Color.Black,
                fontWeight = FontWeight.Bold
            )
        )

        Spacer(modifier = Modifier.height(4.dp))

        Text(
            text = hour ?: "10:20 AM", style = TextStyle(
                color = Color.Black.copy(alpha = 0.5F),
                fontWeight = FontWeight.Light
            )
        )
    }
}

@Composable
private fun Options(onClick: () -> Unit) {
    Icon(
        painterResource(id = R.drawable.three_points_ic),
        contentDescription = null,
        modifier = Modifier
            .size(45.dp)
            .clickable { onClick() },
        tint = Color.Black.copy(alpha = 0.8F)
    )
}