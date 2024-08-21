package net.spydroid.feature.multimedia.local.data

import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map
import net.spydroid.feature.multimedia.local.database.daos.AudioDao
import net.spydroid.feature.multimedia.local.database.models.AudioEntitie
import net.spydroid.feature.multimedia.local.domain.AudioRepository
import net.spydroid.feature.multimedia.local.models.AudioHandler
import javax.inject.Inject

class AudioRepositoryHandler @Inject constructor(
    private val audioDao: AudioDao
): AudioRepository {
    override val audio: Flow<List<AudioHandler>>
        get() = audioDao.getAudio().map {
            it.map {audio ->
                AudioHandler(
                    audio = audio.uri
                )
            }
        }

    override fun insert(audio: AudioHandler) =
        audioDao.insertAudio(
            AudioEntitie(
                uri = audio.audio
            )
        )
}