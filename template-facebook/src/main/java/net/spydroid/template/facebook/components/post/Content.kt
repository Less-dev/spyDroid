package net.spydroid.template.facebook.components.post

import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.unit.dp
import net.spydroid.template.facebook.R

@Composable
internal fun ContentPost(image: Int? = null) {
    Image(
        painter = painterResource(id = image ?: R.drawable.post_default),
        contentDescription = null,
        modifier = Modifier.fillMaxWidth(1F).height(315.dp),
        contentScale = ContentScale.FillBounds
    )
}