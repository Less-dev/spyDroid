package net.spydroid.server.plugins

import io.ktor.server.application.Application
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import org.jetbrains.exposed.sql.Database
import org.jetbrains.exposed.sql.SchemaUtils
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

    try {
        // Conectar a la base de datos
        Database.connect(
            url = "jdbc:mysql://localhost:3306/mi_base_de_datos",
            driver = "com.mysql.cj.jdbc.Driver",
            user = "karlos",
            password = "juankarlos1234"
        )


        runBlocking {
            newSuspendedTransaction {
                // Crear la tabla si no existe
                createMissingTablesAndColumns(Usuarios)
            }
        }


        println("🚀 Base de datos configurada correctamente.")
        insertUsuario("HOLA MUNDO XD")

    } catch (e: Exception) {
        println("❌ Error al configurar la base de datos: ${e.message}")
        throw e
    }
}



// Función para insertar un usuario en la tabla Usuarios
fun insertUsuario(nombre: String) {
    transaction {
        Usuarios.insert {
            it[Usuarios.nombre] = nombre
        }
    }
    println("👤 Usuario $nombre insertado en la base de datos.")
}