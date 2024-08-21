package net.spydroid.feature.multimedia.local.domain

import kotlinx.coroutines.flow.Flow
import net.spydroid.feature.multimedia.local.models.AudioHandler

interface AudioRepository {
    val audio: Flow<List<AudioHandler>>
    fun insert(audio: AudioHandler)
}