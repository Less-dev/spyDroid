package net.spydroid.server.data

import net.spydroid.server.db.domain.InfoDao
import net.spydroid.server.domain.InfoRepository
import net.spydroid.server.models.InfoHandler
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject

class InfoRepositoryHandler: InfoRepository, KoinComponent {

    val infoDao: InfoDao by inject()

    override suspend fun getInfo(): List<InfoHandler> =
        infoDao.getInfo()

    override suspend fun filerWithAlias(alias: String): List<InfoHandler> =
        infoDao.filerWithAlias(alias)
    override suspend fun insert(info: InfoHandler) =
        infoDao.insert(info)

    override suspend fun update(info: InfoHandler) =
        infoDao.update(info)

    override suspend fun delete(info: InfoHandler) =
        infoDao.delete(info)
}