package net.spydroid.feature.multimedia.local.data

import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map
import net.spydroid.feature.multimedia.local.database.daos.VideoDao
import net.spydroid.feature.multimedia.local.database.models.VideoEntitie
import net.spydroid.feature.multimedia.local.domain.VideoRepository
import net.spydroid.feature.multimedia.local.models.VideoHandler
import javax.inject.Inject

class VideoRepositoryHandler @Inject constructor(
    private val videoDao: VideoDao
): VideoRepository {
    override val video: Flow<List<VideoHandler>>
        get() = videoDao.getVideo().map {
            it.map {video ->
                VideoHandler(
                    video = video.uri
                )
            }
        }

    override fun insert(video: VideoHandler) =
        videoDao.insertVideo(
            VideoEntitie(
                uri = video.video
            )
        )
}