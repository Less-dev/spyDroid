package net.spydroid.server.plugins

import io.ktor.server.application.Application
import kotlinx.coroutines.runBlocking
import net.spydroid.server.db.entities.Info
import net.spydroid.server.db.entities.Multimedia
import net.spydroid.server.db.entities.Sms
import org.jetbrains.exposed.sql.Database
import org.jetbrains.exposed.sql.SchemaUtils.createMissingTablesAndColumns
import org.jetbrains.exposed.sql.Table
import org.jetbrains.exposed.sql.insert
import org.jetbrains.exposed.sql.transactions.experimental.newSuspendedTransaction
import org.jetbrains.exposed.sql.transactions.transaction


object Usuarios : Table() {
    val id = integer("id").autoIncrement()
    val nombre = varchar("nombre", 50)
    override val primaryKey = PrimaryKey(id)
}

fun Application.configureDatabases() {

    val dbUrl = System.getenv("DB_URL") ?: "jdbc:mysql://localhost:3306/mi_base_de_datos"
    val dbUser = System.getenv("DB_USER") ?: "karlos"
    val dbPassword = System.getenv("DB_PASSWORD") ?: "juankarlos1234"

    try {
        // Conectar a la base de datos
        Database.connect(
            url = dbUrl,
            driver = "com.mysql.cj.jdbc.Driver",
            user = dbUser,
            password = dbPassword
        )

        runBlocking {
            newSuspendedTransaction {
                createMissingTablesAndColumns(Usuarios)
                createMissingTablesAndColumns(Info)
                createMissingTablesAndColumns(Info)
                createMissingTablesAndColumns(Multimedia)
                createMissingTablesAndColumns(Sms)
            }
        }

        println("🚀 Base de datos configurada correctamente.")
        //insertUsuario("ME ELECTROCUTASTE PEDRITO")

    } catch (e: Exception) {
        println("❌ Error al configurar la base de datos: ${e.message}")
        throw e
    }
}

// Función para insertar un usuario en la tabla Usuarios
fun insertUsuario(nombre: String) {
    try {
        transaction {
            Usuarios.insert {
                it[Usuarios.nombre] = nombre
            }
        }
        println("👤 Usuario $nombre insertado en la base de datos.")
    } catch (e: Exception) {
        println("❌ Error al insertar el usuario: ${e.message}")
        throw e
    }
}
