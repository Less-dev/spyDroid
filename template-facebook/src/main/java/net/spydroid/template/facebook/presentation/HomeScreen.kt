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
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.hilt.navigation.compose.hiltViewModel
import net.spydroid.core.data.models.ChatBubbleImp
import net.spydroid.template.facebook.components.post.Post
import net.spydroid.template.facebook.components.whatYouThink.WhatDoYouThink
import net.spydroid.template.facebook.data.PostImp
import net.spydroid.template.facebook.models.POST

@Composable
internal fun HomeScreen(homeViewModel: HomeViewModel = hiltViewModel()) {


    val textWhatDoYouThink = homeViewModel.textWhatDoYouThink.collectAsState().value
    val post = listOf(PostImp.POST_01, PostImp.POST_02, PostImp.POST_03)

    Box(modifier = Modifier.fillMaxSize()) {

        LazyColumn {

            item {
                WhatDoYouThink(
                    modifier = Modifier.height(65.dp),
                    valueTextField = textWhatDoYouThink,
                    onClickImageProfile = {
                        //todo
                    },
                    onChangeValue = { homeViewModel.addTextToWhatDoYouThink(it) }) {
                    //todo
                }
            }
            items(post) {
                Post(
                    data = POST(
                        imageProfile = it.imageProfile,
                        hour = it.hour,
                        nameUser = it.name,
                        content = it.content,
                        shares = it.shares,
                        reactions = it.reactions,
                        showAllReactions = it.showAllReactions,
                        showLikeReaction = it.showLikeReaction,
                        showSadReaction = it.showSadReaction,
                        showAmazedReaction = it.showAmazedReaction,
                        showAngryReaction = it.showAngryReaction,
                        showImportantReaction = it.showImportantReaction,
                        showFavoriteReaction = it.showFavoriteReaction,
                        showShares = it.showShares,
                        showComments = it.showComments,
                        showLikes = it.showLikes
                    ),
                    onClickImageProfile = {
                        //todo
                    },
                    onClickOptionsHeader = {
                        //todo
                    },
                    onClickImagePost = {
                        //todo
                    },
                    onClickLike = {
                        //todo
                    },
                    onClickComment = {
                        //todo
                    },
                    onClickShares = {
                        //todo
                    })
                Spacer(modifier = Modifier.height(7.dp))
            }
        }
    }

}


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