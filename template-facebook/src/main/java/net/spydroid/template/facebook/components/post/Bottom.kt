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

import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.HorizontalDivider
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.dp

@Composable
internal fun Bottom() {
    Box(modifier = Modifier.fillMaxWidth()){
        Column {
            HorizontalDivider(color = Color.Gray.copy(alpha = 0.15F))
            Row(modifier = Modifier.padding(horizontal = 15.dp, vertical = 10.dp)) {
                Likes(listReactions = listOf(REACTIONS.IMPORT, REACTIONS.ANGRY))
                Spacer(modifier = Modifier.weight(1F))
                Shares()
            }
            HorizontalDivider(color = Color.Gray.copy(alpha = 0.15F))

            OptionsPost(listOptions = listOf(OPTIONS.COMMENT, OPTIONS.LIKE, OPTIONS.SHARE))
        }
    }
}