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

package net.spydroid.server.db

import kotlinx.coroutines.runBlocking
import net.spydroid.server.db.entities.Devices
import net.spydroid.server.db.entities.Info
import net.spydroid.server.db.entities.Multimedia
import net.spydroid.server.db.entities.Sms
import org.jetbrains.exposed.sql.Database
import org.jetbrains.exposed.sql.SchemaUtils
import org.jetbrains.exposed.sql.transactions.experimental.newSuspendedTransaction

class DbManager {

    private val dbUrl = System.getenv("DB_URL") ?: "jdbc:mysql://localhost:3306/mi_base_de_datos"
    private val dbUser = System.getenv("DB_USER") ?: "karlos"
    private val dbPassword = System.getenv("DB_PASSWORD") ?: "juankarlos1234"

    fun connectToDb() =
        Database.connect(
            url = dbUrl,
            driver = "com.mysql.cj.jdbc.Driver",
            user = dbUser,
            password = dbPassword
        )

    fun createTables() = runBlocking {
        newSuspendedTransaction {
            SchemaUtils.createMissingTablesAndColumns(Devices)
            SchemaUtils.createMissingTablesAndColumns(Info)
            SchemaUtils.createMissingTablesAndColumns(Multimedia)
            SchemaUtils.createMissingTablesAndColumns(Sms)
        }
    }

}