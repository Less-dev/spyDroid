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

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.material3.Icon
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import net.spydroid.template.facebook.R


internal object OPTIONS {
    const val LIKE = "Me gusta"
    const val COMMENT = "Comentar"
    const val SHARE = "Compartir"
}

@Composable
internal fun OptionsPost(listOptions: List<String>? = null) {

    val options = mapOf(
        OPTIONS.LIKE to R.drawable.option_like,
        OPTIONS.COMMENT to R.drawable.option_comment,
        OPTIONS.SHARE to R.drawable.option_shares
    )

    val colorContent = Color.Gray.copy(alpha = 0.87F)

    Row(modifier = Modifier.fillMaxWidth(1F).padding(vertical = 10.dp), horizontalArrangement = Arrangement.SpaceAround) {
        options.map { option ->
            listOptions?.map {
                if (option.key == it) {
                    Row(verticalAlignment = Alignment.CenterVertically) {
                        Icon(
                            painter = painterResource(id = option.value),
                            contentDescription = null,
                            modifier = Modifier.size(22.4.dp),
                            tint = colorContent
                        )
                        Spacer(modifier = Modifier.width(3.dp))

                        Text(
                            text = option.key, style = TextStyle(
                                color = colorContent,
                                fontWeight = FontWeight.Light,
                                fontSize = 14.5.sp
                            )
                        )

                    }
                }
            }
        }
    }
}