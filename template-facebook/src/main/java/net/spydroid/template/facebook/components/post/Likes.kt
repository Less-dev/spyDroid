/*
 * Copyright (C) 2024 Daniel Gómez(Less)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

package net.spydroid.template.facebook.components.post

import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import net.spydroid.core.ui.R
import net.spydroid.template.facebook.models.POST


internal object REACTIONS {
    const val FAVORITE = "favorite"
    const val SAD = "sad"
    const val AMAZED = "amazed"
    const val ANGRY = "angry"
    const val LIKE = "like"
    const val IMPORT = "import"
}

internal data class SHOWREACTIONS(
    val showAllReactions: Boolean = false,
    val showFavoriteReaction: Boolean = false,
    val showSadReaction: Boolean = false,
    val showAmazedReaction: Boolean = false,
    val showAngryReaction: Boolean = false,
    val showLikeReaction: Boolean = false,
    val showImportantReaction: Boolean = false,
)

@Composable
internal fun Likes(data: POST, likes: Int? = null) {

    Row(verticalAlignment = Alignment.CenterVertically) {

        with(data) {
            val sizeDefault = 21.5.dp
            val contentScale = ContentScale.Crop

            if (this.showLikeReaction) Image(painter = painterResource(id = R.drawable.like_ic), contentDescription = null, modifier = Modifier.size(29.5.dp), contentScale = contentScale)
            if (this.showAmazedReaction) Image(painter = painterResource(id = R.drawable.amazed_ic), contentDescription = null, modifier = Modifier.size(sizeDefault), contentScale = contentScale)
            if (this.showFavoriteReaction) Image(painter = painterResource(id = R.drawable.favorite_ic), contentDescription = null, modifier = Modifier.size(27.dp), contentScale = contentScale)
            if (this.showSadReaction) Image(painter = painterResource(id = R.drawable.sad_ic), contentDescription = null, modifier = Modifier.size(29.dp), contentScale = contentScale)
            if (this.showAngryReaction) Image(painter = painterResource(id = R.drawable.angry_ic), contentDescription = null, modifier = Modifier.size(31.44.dp), contentScale = contentScale)
            if (this.showImportantReaction) Image(painter = painterResource(id = R.drawable.import_ic), contentDescription = null, modifier = Modifier.size(sizeDefault), contentScale = contentScale)
            if (this.showAllReactions) {
                Image(painter = painterResource(id = R.drawable.like_ic), contentDescription = null, modifier = Modifier.size(29.5.dp), contentScale = contentScale)
                Image(painter = painterResource(id = R.drawable.amazed_ic), contentDescription = null, modifier = Modifier.size(sizeDefault), contentScale = contentScale)
                Image(painter = painterResource(id = R.drawable.favorite_ic), contentDescription = null, modifier = Modifier.size(27.dp), contentScale = contentScale)
                Image(painter = painterResource(id = R.drawable.sad_ic), contentDescription = null, modifier = Modifier.size(29.dp), contentScale = contentScale)
                Image(painter = painterResource(id = R.drawable.angry_ic), contentDescription = null, modifier = Modifier.size(31.44.dp), contentScale = contentScale)
                Image(painter = painterResource(id = R.drawable.import_ic), contentDescription = null, modifier = Modifier.size(sizeDefault), contentScale = contentScale)
            }
        }
        Spacer(modifier = Modifier.width(5.dp))
        Text(
            text = "${likes ?: ""}",
            style = TextStyle(color = Color.Black),
            fontWeight = FontWeight.SemiBold,
            fontSize = 14.sp
        )
    }
}
