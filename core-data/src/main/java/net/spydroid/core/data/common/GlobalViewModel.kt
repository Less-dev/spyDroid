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

package net.spydroid.core.data.common

import android.content.Context
import androidx.compose.runtime.compositionLocalOf
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.launch
import net.spydroid.core.data.local.PreferencesManager



val LocalGlobalViewModel = compositionLocalOf<GlobalViewModel> { error("No GlobalViewModel found!") }

class GlobalViewModel(
    private val context: Context
): ViewModel() {

    private val preferencesManager = PreferencesManager(context)
    private val _stateVncServer = MutableStateFlow(preferencesManager.getData("state"))
    val stateVncServer: StateFlow<Boolean> = _stateVncServer

    fun changeValueVncServer(value: Boolean) =
        viewModelScope.launch(Dispatchers.IO) {
            preferencesManager.saveData(key = "state", value = value)
            _stateVncServer.value = value
        }

}