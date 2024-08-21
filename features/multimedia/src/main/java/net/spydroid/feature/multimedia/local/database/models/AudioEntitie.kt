package net.spydroid.feature.multimedia.local.database.models

import androidx.room.Entity
import androidx.room.PrimaryKey


@Entity
data class AudioEntitie(
    @PrimaryKey(autoGenerate = true)
    val id: Int = 0,
    val uri: String
)
