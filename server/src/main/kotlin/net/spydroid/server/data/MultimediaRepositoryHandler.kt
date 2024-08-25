/*
 * Copyright (C) 2024 Daniel Gómez(Less)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

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