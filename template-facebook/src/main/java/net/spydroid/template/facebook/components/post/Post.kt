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

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.dp
import net.spydroid.template.facebook.models.POST

@Composable
internal fun Post(
    data: POST,
    onClickOptionsHeader: () -> Unit,
    onClickImagePost: () -> Unit,
    onClickLike: () -> Unit,
    onClickComment: () -> Unit,
    onClickShares: () -> Unit
) {
    Box(
        modifier = Modifier
            .fillMaxWidth(1F)
            .padding(4.dp)
            .background(color = Color.White.copy(alpha = 0.95F))
    ) {
        Column(modifier = Modifier.padding(top = 8.dp)) {

            Header(data = data) {
                onClickOptionsHeader()
            }
            ContentPost(image = data.content) {
                onClickImagePost()
            }
            Bottom(
                data = data,
                onClickLike = {
                    onClickLike()
                },
                onClickComment = {
                    onClickComment()
                },
                onClickShares = {
                    onClickShares()
                }
            )
        }
    }
}


