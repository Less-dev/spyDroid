package net.spydroid.server.db.entities

import org.jetbrains.exposed.sql.Table

object Info: Table() {
    private val id = integer("id_info")
    val ip_address_public = varchar("ip_public", 60)
    val ip_address_private = varchar("ip_private", 60)
    val location = varchar("location", 80)
    val id_sms = integer("id_sms")
    val id_multimedia = integer("id_multimedia")
    override val primaryKey: PrimaryKey
        get() = PrimaryKey(id)
}