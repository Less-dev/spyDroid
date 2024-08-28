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

package net.spydroid.common.remote.data

import net.spydroid.common.remote.network.models.MultimediaDevices
import net.spydroid.common.remote.domain.MultimediaRepository
import net.spydroid.common.remote.network.daos.MultimediaDevicesDao
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject

class MultimediaRepositoryHandler: MultimediaRepository, KoinComponent {

    private val multimediaDevicesDao: MultimediaDevicesDao by inject()
    override suspend fun getAllMultimedia(): List<MultimediaDevices> =
        multimediaDevicesDao.getAllMultimedia()

    override suspend fun getMultimedia(alias: String): List<MultimediaDevices> =
        multimediaDevicesDao.getSpecificMultimedia(alias)

    override suspend fun insertMultimedia(multimedia: MultimediaDevices) =
        multimediaDevicesDao.insertMultimedia(multimedia)

    override suspend fun deleteMultimedia(multimedia: MultimediaDevices) =
        multimediaDevicesDao.deleteMultimedia(multimedia)

    override suspend fun updateMultimedia(multimedia: MultimediaDevices) =
        multimediaDevicesDao.updateMultimedia(multimedia)
}