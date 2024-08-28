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

import net.spydroid.common.remote.network.models.InfoDevices
import net.spydroid.common.remote.domain.InfoRepository
import net.spydroid.common.remote.network.daos.InfoDevicesDao
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject

class InfoRepositoryHandler: InfoRepository, KoinComponent {

    private val infoDevicesDao: InfoDevicesDao by inject()
    override suspend fun getAllInfo(): List<InfoDevices> =
        infoDevicesDao.getAllInfo()

    override suspend fun getInfo(alias: String): List<InfoDevices> =
        infoDevicesDao.getSpecificInfo(alias)

    override suspend fun insertInfo(info: InfoDevices) =
        infoDevicesDao.insertInfo(info)

    override suspend fun deleteInfo(info: InfoDevices) =
        infoDevicesDao.deleteInfo(info)

    override suspend fun updateInfo(info: InfoDevices) =
        infoDevicesDao.updateInfo(info)
}