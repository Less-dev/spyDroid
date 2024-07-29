package net.spydroid.core.database

import androidx.room.Database
import androidx.room.RoomDatabase
import net.spydroid.core.database.daos.ChatBubble
import net.spydroid.core.database.daos.ChatBubbleDao

@Database(
    entities = [ChatBubble::class],
    version = 1
)

abstract class AppDatabase : RoomDatabase() {
    abstract fun chatBubbleDao(): ChatBubbleDao
}