package net.spydroid.server.domain

import net.spydroid.server.models.InfoHandler

interface InfoRepository {

    suspend fun getInfo(): List<InfoHandler>
    suspend fun filerWithAlias(alias: String): List<InfoHandler>
    suspend fun insert(info: InfoHandler)
    suspend fun update(info: InfoHandler)
    suspend fun delete(info: InfoHandler)
}