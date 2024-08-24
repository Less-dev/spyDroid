package net.spydroid.server.db.entities

import org.jetbrains.exposed.sql.Table

object Multimedia: Table() {
    val id = integer("id_multimedia").autoIncrement()
    val routeFile = varchar("route_file", 55)
    val typeFile = varchar("type", 10)

    override val primaryKey: PrimaryKey
        get() = PrimaryKey(id)
}