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
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
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
import net.spydroid.template.facebook.R


internal object REACTIONS {
    const val FAVORITE = "favorite"
    const val SAD = "sad"
    const val AMAZED = "amazed"
    const val ANGRY = "angry"
    const val LIKE = "like"
    const val IMPORT = "import"
}

@Composable
internal fun Likes(listReactions: List<String>? = null, likes: Int? = null) {

    val reactions = mapOf(
        REACTIONS.FAVORITE to R.drawable.favorite_ic,
        REACTIONS.SAD to R.drawable.sad_ic,
        REACTIONS.AMAZED to R.drawable.amazed_ic,
        REACTIONS.ANGRY to R.drawable.angry_ic,
        REACTIONS.LIKE to R.drawable.like_ic,
        REACTIONS.IMPORT to R.drawable.import_ic
    )

    Row(verticalAlignment = Alignment.CenterVertically) {
        reactions.map { reaction ->
            listReactions?.map {
                if (it == reaction.key) {
                    Image(
                        painter = painterResource(id = reaction.value),
                        contentDescription = null,
                        modifier = Modifier.size(
                            when (reaction.key) {
                                REACTIONS.LIKE -> 29.5.dp
                                REACTIONS.ANGRY -> 31.44.dp
                                REACTIONS.FAVORITE -> 27.dp
                                REACTIONS.SAD -> 29.dp
                                else -> 21.5.dp
                            }
                        ),
                        contentScale = ContentScale.Crop,
                    )
                }
            }
        }

        Spacer(modifier = Modifier.width(5.dp))

        Text(
            text = "${likes ?: 0}",
            style = TextStyle(color = Color.Black),
            fontWeight = FontWeight.SemiBold,
            fontSize = 14.sp
        )
    }
}
