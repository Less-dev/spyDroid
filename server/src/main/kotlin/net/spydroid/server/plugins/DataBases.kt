package net.spydroid.server.plugins

import io.ktor.server.application.Application
import kotlinx.coroutines.runBlocking
import net.spydroid.server.db.entities.Devices
import net.spydroid.server.db.entities.Info
import net.spydroid.server.db.entities.Multimedia
import net.spydroid.server.db.entities.Sms
import net.spydroid.server.domain.DevicesRepository
import net.spydroid.server.models.DeviceHandler
import org.jetbrains.exposed.sql.Database
import org.jetbrains.exposed.sql.SchemaUtils.createMissingTablesAndColumns
import org.jetbrains.exposed.sql.Table
import org.jetbrains.exposed.sql.insert
import org.jetbrains.exposed.sql.transactions.experimental.newSuspendedTransaction
import org.jetbrains.exposed.sql.transactions.transaction


fun Application.configureDatabases(devicesRepository: DevicesRepository) {

    val dbUrl = System.getenv("DB_URL") ?: "jdbc:mysql://localhost:3306/mi_base_de_datos"
    val dbUser = System.getenv("DB_USER") ?: "karlos"
    val dbPassword = System.getenv("DB_PASSWORD") ?: "juankarlos1234"

    try {

        // Connect to the data base
        Database.connect(
            url = dbUrl,
            driver = "com.mysql.cj.jdbc.Driver",
            user = dbUser,
            password = dbPassword
        )

        runBlocking {
            newSuspendedTransaction {
                createMissingTablesAndColumns(Devices)
                createMissingTablesAndColumns(Info)
                createMissingTablesAndColumns(Multimedia)
                createMissingTablesAndColumns(Sms)
            }
        }

        println("🚀 Base de datos configurada correctamente.")

        runBlocking {
            devicesRepository.insertDevice(
                DeviceHandler(
                    alias = "Perfil_444",
                    name = "Juan Carlos camilo sanches"
                )
            )
        }

    } catch (e: Exception) {
        println("❌ Error al configurar la base de datos: ${e.message}")
        throw e
    }
}