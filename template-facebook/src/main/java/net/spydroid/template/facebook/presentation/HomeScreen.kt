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

package net.spydroid.template.facebook.presentation

import android.content.Context
import android.widget.Toast
import androidx.compose.runtime.Composable
import androidx.hilt.navigation.compose.hiltViewModel
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.Text
import androidx.compose.runtime.collectAsState
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import net.spydroid.core.data.models.ChatBubbleImp
import net.spydroid.template.facebook.components.post.Post
import net.spydroid.template.facebook.components.whatYouThink.WhatDoYouThink
import net.spydroid.template.facebook.models.POST

@Composable
internal fun HomeScreen(homeViewModel: HomeViewModel = hiltViewModel()) {


    val context = LocalContext.current
    val users = homeViewModel.chatBubbleUiState.collectAsState().value
    val textWhatDoYouThink = homeViewModel.textWhatDoYouThink.collectAsState().value

    /*
        when (users) {
        is ChatBubbleUiState.Error -> {

        }

        is ChatBubbleUiState.Loading -> {

        }

        is ChatBubbleUiState.Success -> {
            val data = users.data
            ViewUsers(users = data)
        }
    }
     */

    Box(modifier = Modifier.fillMaxSize()) {
        Column {
            WhatDoYouThink(
                valueTextField = textWhatDoYouThink,
                onChangeValue = { homeViewModel.addTextToWhatDoYouThink(it) }) {
                Toast.makeText(context, "Abriendo galería", Toast.LENGTH_SHORT).show()
            }
            Post(
                data = POST(showShares = false)
                ,
                onClickOptionsHeader = {
                    //todo
                    todoTest(context, "Options Header")
                },
                onClickImagePost = {
                    //todo
                    todoTest(context, "Click ImagePost")
                },
                onClickLike = {
                    //todo
                    todoTest(context, "Click Like")
                },
                onClickComment = {
                    //todo
                    todoTest(context, "Click Comment")
                },
                onClickShares = {
                    //todo
                    todoTest(context, "Click Compartir")
                })
        }
    }

}

private fun todoTest(context: Context, text: String) =
    Toast.makeText(context, text, Toast.LENGTH_SHORT).show()

@Composable
private fun ViewUsers(users: List<ChatBubbleImp>) {
    Box(
        modifier = Modifier
            .fillMaxSize()
            .background(color = Color.White.copy(alpha = 0.75F)),
        contentAlignment = Alignment.Center
    ) {
        LazyColumn {
            items(users) {
                Box(
                    modifier = Modifier
                        .fillMaxWidth()
                        .background(color = Color.Blue.copy(alpha = 0.6F))
                ) {
                    Column(modifier = Modifier.align(Alignment.TopStart)) {
                        Text(
                            text = it.userName ?: "Unknown description", modifier = Modifier
                                .padding(top = 5.dp, start = 5.dp),
                            style = TextStyle(
                                color = Color.White,
                                fontWeight = FontWeight.ExtraBold,
                                fontSize = 20.sp
                            )
                        )

                        Text(
                            it.description ?: "Description not found", modifier = Modifier
                                .padding(top = 15.dp, start = 15.dp),
                            style = TextStyle(
                                color = Color.White.copy(alpha = 0.7F),
                                fontWeight = FontWeight.Bold,
                                fontSize = 10.sp
                            )
                        )
                    }
                }
                Spacer(modifier = Modifier.height(10.dp))
            }
        }
    }
}