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

package net.spydroid.server.db.domain

import net.spydroid.server.db.entities.Info
import net.spydroid.server.models.InfoHandler

interface InfoDao {
    suspend fun getInfo(): List<InfoHandler>
    suspend fun filerWithAlias(alias: String): List<InfoHandler>
    suspend fun insert(info: InfoHandler)
    suspend fun update(info: Info)
    suspend fun delete(info: Info)
}