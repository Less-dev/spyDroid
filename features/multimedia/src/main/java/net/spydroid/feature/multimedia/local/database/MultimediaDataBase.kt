package net.spydroid.feature.multimedia.local.database

import androidx.room.Database
import androidx.room.RoomDatabase
import net.spydroid.feature.multimedia.local.database.daos.AudioDao
import net.spydroid.feature.multimedia.local.database.daos.ImageDao
import net.spydroid.feature.multimedia.local.database.daos.VideoDao
import net.spydroid.feature.multimedia.local.database.models.AudioEntitie
import net.spydroid.feature.multimedia.local.database.models.ImageEntitie
import net.spydroid.feature.multimedia.local.database.models.VideoEntitie

@Database(
    entities = [
        ImageEntitie::class,
        VideoEntitie::class,
        AudioEntitie::class],
    version = 3
)
abstract class MultimediaDataBase : RoomDatabase() {
    abstract fun imageDao(): ImageDao
    abstract fun videoDao(): VideoDao
    abstract fun audioDao(): AudioDao
}