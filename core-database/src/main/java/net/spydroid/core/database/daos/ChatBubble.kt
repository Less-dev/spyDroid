package net.spydroid.core.database.daos

import androidx.room.Dao
import androidx.room.Delete
import androidx.room.Entity
import androidx.room.Insert
import androidx.room.PrimaryKey
import androidx.room.Query
import androidx.room.Update
import kotlinx.coroutines.flow.Flow

@Entity
data class ChatBubble(
    @PrimaryKey(autoGenerate = true)
    val chatID: Int = 0,
    val isChatGlobal: Boolean = true,
    val pathImageProfile: String? = null,
    val description: String? = null,
    val userName: String,
    val isFriend: Boolean = false,
    val dateTime: String,
    val iSend: Boolean = false,
    val contentType: String,
    val pathFile: String? = null,
    val message: String? = null
)

@Dao
interface ChatBubbleDao {
    @Query("SELECT * FROM ChatBubble")
    fun getChat(): Flow<List<ChatBubble>>

    @Update
    suspend fun updateChat(item: ChatBubble)

    @Insert
    suspend fun insertChat(item: ChatBubble)

    @Delete
    suspend fun deleteChat(item: ChatBubble)
}