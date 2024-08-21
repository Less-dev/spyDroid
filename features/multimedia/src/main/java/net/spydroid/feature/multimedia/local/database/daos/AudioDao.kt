package net.spydroid.feature.multimedia.local.database.daos

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.Query
import kotlinx.coroutines.flow.Flow
import net.spydroid.feature.multimedia.local.database.models.AudioEntitie

@Dao
interface AudioDao{
    @Query("SELECT * FROM AUDIOENTITIE")
    fun getAudio(): Flow<List<AudioEntitie>>

    @Insert
    fun insertAudio(audio: AudioEntitie)
}
