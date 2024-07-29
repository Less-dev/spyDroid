package net.spydroid.template.facebook.presentation

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
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import net.spydroid.core.data.models.ChatBubbleImp

@Composable
internal fun HomeScreen(homeViewModel: HomeViewModel = hiltViewModel()) {


    val users = homeViewModel.chatBubbleUiState.collectAsState().value

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