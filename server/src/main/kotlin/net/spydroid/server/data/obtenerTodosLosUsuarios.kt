package net.spydroid.server.data

import net.spydroid.server.plugins.Usuarios
import org.jetbrains.exposed.sql.select
import org.jetbrains.exposed.sql.selectAll
import org.jetbrains.exposed.sql.transactions.transaction

// Función para obtener todos los usuarios


fun obtenerTodosLosUsuarios(): List<String> {
    return transaction {
        Usuarios.selectAll().map {
            it[Usuarios.nombre]
        }
    }
}

// Función para obtener un usuario por su ID
fun obtenerUsuarioPorId(id: Int): String? {
    return transaction {
        Usuarios.select { Usuarios.id eq id }
            .map { it[Usuarios.nombre] }
            .singleOrNull() // Si esperas un solo resultado, usa singleOrNull para obtener null si no hay resultados.
    }
}

// Función para obtener usuarios por nombre (ejemplo con LIKE)
fun buscarUsuariosPorNombre(parcialNombre: String): List<String> {
    return transaction {
        Usuarios.select { Usuarios.nombre like "%$parcialNombre%" }
            .map { it[Usuarios.nombre] }
    }
}
