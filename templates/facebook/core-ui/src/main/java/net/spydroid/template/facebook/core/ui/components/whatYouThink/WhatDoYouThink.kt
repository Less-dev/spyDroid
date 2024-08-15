package net.spydroid.template.facebook.core.ui.components.whatYouThink

import androidx.compose.foundation.Image
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Icon
import androidx.compose.material3.OutlinedTextField
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
import androidx.compose.ui.unit.sp
import net.spydroid.template.facebook.core.ui.R

@Composable
fun WhatDoYouThink(
    modifier: Modifier = Modifier,
    valueTextField: String,
    onClickImageProfile: () -> Unit,
    onChangeValue: (String) -> Unit,
    onClickImage: () -> Unit
) {
    HorizontalDivider(color = Color.Gray.copy(alpha = 0.54F))

    Row(
        modifier
            .fillMaxWidth()
            .padding(10.dp),
        horizontalArrangement = Arrangement.SpaceBetween,
        verticalAlignment = Alignment.CenterVertically
    ) {


        ImageProfile {
            onClickImageProfile()
        }

        TextFieldTask(valueTextField) {
            onChangeValue(it)
        }

        IconImage {
            onClickImage()
        }
    }
    HorizontalDivider(color = Color.Gray.copy(alpha = 0.54F))
}


@Composable
private fun ImageProfile(image: Int? = null, onClickImageProfile: () -> Unit) {
    Image(
        painter = painterResource(id = image ?: R.drawable.profile_default),
        contentDescription = null,
        modifier = Modifier
            .size(40.dp)
            .clip(CircleShape)
            .clickable { onClickImageProfile() }
    )
}

@Composable
private fun TextFieldTask(value: String, onChangeValue: (String) -> Unit) {
    OutlinedTextField(
        value = value,
        onValueChange = { onChangeValue(it) },
        modifier = Modifier
            .height(45.dp)
            .width(250.dp),
        placeholder = {
            Text(
                text = " ¿Qué estás pensando? ", style = TextStyle(
                    color = Color.Black.copy(alpha = 0.75F),
                    fontSize = 11.76.sp,
                    fontWeight = FontWeight.Light
                )
            )
        },
        shape = RoundedCornerShape(50.dp)
    )
}

@Composable
private fun IconImage(onClick: () -> Unit) {
    Icon(
        painter = painterResource(id = R.drawable.image_ic),
        contentDescription = null,
        tint = Color(
            0xFF1D770A
        ),
        modifier = Modifier
            .height(40.dp)
            .width(31.5.dp)
            .clickable { onClick() }
    )
}