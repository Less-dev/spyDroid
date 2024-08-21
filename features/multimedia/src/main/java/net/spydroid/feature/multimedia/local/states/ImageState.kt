package net.spydroid.feature.multimedia.local.states

import net.spydroid.feature.multimedia.local.models.ImageHandler

sealed interface ImageState {
    data object Loading : ImageState
    data class Error(val throwable: Throwable) : ImageState
    data class Success(val data: List<ImageHandler>) : ImageState
}