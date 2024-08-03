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

package net.spydroid.template_default.presentation

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.launch
import net.spydroid.core.data.models.ChatBubbleImp
import net.spydroid.core.data.repository.ChatBubbleRepository
import javax.inject.Inject


@HiltViewModel
class HomeViewModel @Inject constructor(
    private val chatBubbleRepository: ChatBubbleRepository
) : ViewModel() {

    private val _newTask = MutableStateFlow("")
    val newTask: StateFlow<String> = _newTask

    fun addNewTextToTask(text: String) =
        viewModelScope.launch(Dispatchers.IO) {
            _newTask.value = text
        }

    fun createTask() =
        viewModelScope.launch(Dispatchers.IO) {
            chatBubbleRepository.insert(
                ChatBubbleImp(
                    userName = "",
                    contentType = "",
                    dateTime = ""
                )
            )
        }
}