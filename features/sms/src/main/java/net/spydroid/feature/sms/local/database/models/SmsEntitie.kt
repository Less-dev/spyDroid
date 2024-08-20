package net.spydroid.feature.sms.local.database.models

import androidx.room.Entity
import androidx.room.PrimaryKey


@Entity
data class SmsEntitie(
    @PrimaryKey(autoGenerate = true)
    val id: Int = 0,
    val address: String,
    val body: String,
    val date: String
)