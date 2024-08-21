package net.spydroid.feature.multimedia.local.domain

import kotlinx.coroutines.flow.Flow
import net.spydroid.feature.multimedia.local.models.VideoHandler

interface VideoRepository {
    val video: Flow<List<VideoHandler>>
    fun insert(video: VideoHandler)
}