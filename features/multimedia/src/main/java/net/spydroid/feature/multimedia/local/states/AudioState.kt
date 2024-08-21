package net.spydroid.feature.multimedia.local.states

import net.spydroid.feature.multimedia.local.models.AudioHandler

sealed interface AudioState {
    data object Loading : AudioState
    data class Error(val throwable: Throwable) : AudioState
    data class Success(val data: List<AudioHandler>) : AudioState
}