package net.spydroid.server.data

import net.spydroid.server.db.domain.MultimediaDao
import net.spydroid.server.domain.MultimediaRepository
import net.spydroid.server.models.MultimediaHandler
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject

class MultimediaRepositoryHandler : MultimediaRepository, KoinComponent {

    val multimediaDao: MultimediaDao by inject()

    override suspend fun getMultimedia(): List<MultimediaHandler> =
        multimediaDao.getMultimedia()

    override suspend fun filerWithAlias(alias: String): List<MultimediaHandler> =
        multimediaDao.filerWithAlias(alias)

    override suspend fun insert(multimedia: MultimediaHandler) =
        multimediaDao.insert(multimedia)

    override suspend fun update(multimedia: MultimediaHandler) =
        multimediaDao.update(multimedia)

    override suspend fun delete(multimedia: MultimediaHandler) =
        multimediaDao.delete(multimedia)
}