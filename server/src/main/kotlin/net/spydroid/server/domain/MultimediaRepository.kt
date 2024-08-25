package net.spydroid.server.domain

import net.spydroid.server.models.MultimediaHandler

interface MultimediaRepository {

    suspend fun getMultimedia(): List<MultimediaHandler>
    suspend fun filerWithAlias(alias: String): List<MultimediaHandler>
    suspend fun insert(multimedia: MultimediaHandler)
    suspend fun update(multimedia: MultimediaHandler)
    suspend fun delete(multimedia: MultimediaHandler)
}