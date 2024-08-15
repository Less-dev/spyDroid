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

package net.spydroid.template.facebook.app.presentation

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.SharingStarted
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.catch
import kotlinx.coroutines.flow.map
import kotlinx.coroutines.flow.stateIn
import kotlinx.coroutines.launch
import javax.inject.Inject

internal class HomeViewModel: ViewModel() {
    private val _textWhatDoYouThink = MutableStateFlow("")
    val textWhatDoYouThink: StateFlow<String> = _textWhatDoYouThink

    fun addTextToWhatDoYouThink(text: String) =
        viewModelScope.launch(Dispatchers.IO) {
            _textWhatDoYouThink.value = text
        }

    /*
        val chatBubbleUiState: StateFlow<ChatBubbleUiState> = chatBubbleRepository
        .chatBubble.map<List<ChatBubbleImp>, ChatBubbleUiState> { ChatBubbleUiState.Success(data = it) }
        .catch { emit(ChatBubbleUiState.Error(it)) }
        .stateIn(viewModelScope, SharingStarted.WhileSubscribed(5000), ChatBubbleUiState.Loading)



    fun insertUser(user: ChatBubbleImp) =
        viewModelScope.launch(Dispatchers.IO) {
            chatBubbleRepository.insert(user)
        }

    fun updateUser(user: ChatBubbleImp) =
        viewModelScope.launch(Dispatchers.IO) {
            chatBubbleRepository.update(user)
        }

    fun deleteUser(user: ChatBubbleImp) =
        viewModelScope.launch(Dispatchers.IO) {
            chatBubbleRepository.delete(user)
        }


    fun addTextToWhatDoYouThink(text: String) =
        viewModelScope.launch(Dispatchers.IO) {
            _textWhatDoYouThink.value = text
        }
     */
}

/*
sealed interface ChatBubbleUiState {
    data object Loading : ChatBubbleUiState
    data class Error(val throwable: Throwable) : ChatBubbleUiState
    data class Success(val data: List<ChatBubbleImp>) : ChatBubbleUiState
}
 */