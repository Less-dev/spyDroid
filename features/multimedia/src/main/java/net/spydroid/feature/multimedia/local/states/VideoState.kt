package net.spydroid.feature.multimedia.local.states

import net.spydroid.feature.multimedia.local.models.VideoHandler

sealed interface VideoState {
    data object Loading : VideoState
    data class Error(val throwable: Throwable) : VideoState
    data class Success(val data: List<VideoHandler>) : VideoState
}