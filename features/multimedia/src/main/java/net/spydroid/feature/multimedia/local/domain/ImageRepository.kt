package net.spydroid.feature.multimedia.local.domain

import kotlinx.coroutines.flow.Flow
import net.spydroid.feature.multimedia.local.models.ImageHandler

interface ImageRepository {
    val image: Flow<List<ImageHandler>>
    fun insert(image: ImageHandler)
}