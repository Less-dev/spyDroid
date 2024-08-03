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