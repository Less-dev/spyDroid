package net.spydroid.feature.multimedia.local.database.daos

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.Query
import kotlinx.coroutines.flow.Flow
import net.spydroid.feature.multimedia.local.database.models.ImageEntitie


@Dao
interface ImageDao{
    @Query("SELECT * FROM IMAGEENTITIE")
    fun getImage(): Flow<List<ImageEntitie>>

    @Insert
    fun insertImager(image: ImageEntitie)
}
