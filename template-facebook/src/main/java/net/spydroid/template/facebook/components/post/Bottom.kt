package net.spydroid.template.facebook.components.post

import androidx.compose.foundation.layout.Arrangement
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
            HorizontalDivider(color = Color.Gray.copy(alpha = 0.65F))
            Row(modifier = Modifier.padding(horizontal = 15.dp, vertical = 10.dp)) {
                Likes(listReactions = listOf(REACTIONS.IMPORT, REACTIONS.ANGRY))
                Spacer(modifier = Modifier.weight(1F))
                Shares()
            }
            HorizontalDivider(color = Color.Gray.copy(alpha = 0.65F))

            OptionsPost(listOptions = listOf(OPTIONS.COMMENT, OPTIONS.LIKE, OPTIONS.SHARE))
        }
    }
}