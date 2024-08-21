package net.spydroid.feature.multimedia.local.data

import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map
import net.spydroid.feature.multimedia.local.database.daos.ImageDao
import net.spydroid.feature.multimedia.local.database.models.ImageEntitie
import net.spydroid.feature.multimedia.local.domain.ImageRepository
import net.spydroid.feature.multimedia.local.models.ImageHandler
import javax.inject.Inject

class ImageRepositoryHandler @Inject constructor(
    private val imageDao: ImageDao
): ImageRepository {
    override val image: Flow<List<ImageHandler>>
        get() = imageDao.getImage().map {
            it.map { image ->
                ImageHandler(
                    image = image.uri
                )
            }
        }

    override fun insert(image: ImageHandler) =
        imageDao.insertImager(
            ImageEntitie(
                uri = image.image
            )
        )
}