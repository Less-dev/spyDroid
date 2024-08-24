package net.spydroid.server.db.entities

import org.jetbrains.exposed.sql.Table

object Sms: Table() {
    private val id = integer("id_sms")
    val sms = text("sms")
    override val primaryKey: PrimaryKey
        get() = PrimaryKey(id)
}
