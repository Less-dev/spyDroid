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

package net.spydroid.server.plugins

import io.ktor.server.application.Application
import net.spydroid.server.db.DbManager
import net.spydroid.server.domain.DevicesRepository
import net.spydroid.server.domain.InfoRepository
import net.spydroid.server.domain.MultimediaRepository
import net.spydroid.server.domain.SmsRepository
import net.spydroid.server.models.Repos

fun Application.configureDatabases(
    repos: Repos
) {

    try {
        val dbManager = DbManager()

        dbManager.connectToDb()
        dbManager.createTables()
        dbManager.insertDevice(repos.devicesRepository)
        dbManager.insertInfo(repos.infoRepository)
        dbManager.insertMultimedia(repos.multimediaRepository)
        dbManager.insertSms(repos.smsRepository)

    } catch (e: Exception) {
        println("Error connecting to the database${e.message}")
        throw e
    }
}