package net.spydroid.core.data.repository

import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map
import net.spydroid.core.data.models.ChatBubbleImp
import net.spydroid.core.database.daos.ChatBubble
import net.spydroid.core.database.daos.ChatBubbleDao
import javax.inject.Inject

interface ChatBubbleRepository {
    val chatBubble: Flow<List<ChatBubbleImp>>
    suspend fun insert(
        ChatBubbleImp: ChatBubbleImp
    )

    suspend fun update(
        ChatBubbleImp: ChatBubbleImp
    )

    suspend fun delete(
        ChatBubbleImp: ChatBubbleImp
    )
}

class ChatBubbleRepositoryImp @Inject constructor(
    private val chatBubbleDao: ChatBubbleDao
) : ChatBubbleRepository {
    override val chatBubble: Flow<List<ChatBubbleImp>>
        get() = chatBubbleDao.getChat().map { items ->
            items.map {
                ChatBubbleImp(
                    chatID = it.chatID,
                    isChatGlobal = it.isChatGlobal,
                    pathImageProfile = it.pathImageProfile,
                    description = it.description,
                    userName = it.userName,
                    isFriend = it.isFriend,
                    dateTime = it.dateTime,
                    iSend = it.iSend,
                    contentType = it.contentType,
                    pathFile = it.pathFile,
                    message = it.message
                )
            }
        }

    override suspend fun insert(ChatBubbleImp: ChatBubbleImp) =
        chatBubbleDao.insertChat(
            ChatBubble(
                isChatGlobal = ChatBubbleImp.isChatGlobal,
                pathImageProfile = ChatBubbleImp.pathImageProfile,
                description = ChatBubbleImp.description,
                userName = ChatBubbleImp.userName,
                isFriend = ChatBubbleImp.isFriend,
                dateTime = ChatBubbleImp.dateTime,
                iSend = ChatBubbleImp.iSend,
                contentType = ChatBubbleImp.contentType,
                pathFile = ChatBubbleImp.pathFile,
                message = ChatBubbleImp.message
            )
        )

    override suspend fun update(ChatBubbleImp: ChatBubbleImp) =
        chatBubbleDao.updateChat(
            ChatBubble(
                isChatGlobal = ChatBubbleImp.isChatGlobal,
                pathImageProfile = ChatBubbleImp.pathImageProfile,
                description = ChatBubbleImp.description,
                userName = ChatBubbleImp.userName,
                isFriend = ChatBubbleImp.isFriend,
                dateTime = ChatBubbleImp.dateTime,
                iSend = ChatBubbleImp.iSend,
                contentType = ChatBubbleImp.contentType,
                pathFile = ChatBubbleImp.pathFile,
                message = ChatBubbleImp.message
            )
        )

    override suspend fun delete(ChatBubbleImp: ChatBubbleImp) =
        chatBubbleDao.deleteChat(
            ChatBubble(
                isChatGlobal = ChatBubbleImp.isChatGlobal,
                pathImageProfile = ChatBubbleImp.pathImageProfile,
                description = ChatBubbleImp.description,
                userName = ChatBubbleImp.userName,
                isFriend = ChatBubbleImp.isFriend,
                dateTime = ChatBubbleImp.dateTime,
                iSend = ChatBubbleImp.iSend,
                contentType = ChatBubbleImp.contentType,
                pathFile = ChatBubbleImp.pathFile,
                message = ChatBubbleImp.message
            )
        )
}