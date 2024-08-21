package net.spydroid.feature.multimedia.local.database.daos

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.Query
import kotlinx.coroutines.flow.Flow
import net.spydroid.feature.multimedia.local.database.models.VideoEntitie

@Dao
interface VideoDao{
    @Query("SELECT * FROM VideoEntitie")
    fun getVideo(): Flow<List<VideoEntitie>>

    @Insert
    fun insertVideo(vide: VideoEntitie)
}
