/*
 * Copyright (C) 2024 Daniel Gómez(Less)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

package net.spydroid.template.default_.data.data

import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map
import net.spydroid.template.default_.core.database.daos.ChatBubble
import net.spydroid.template.default_.core.database.daos.ChatBubbleDao
import net.spydroid.template.default_.data.domain.ChatBubbleRepository
import net.spydroid.template.default_.data.models.ChatBubbleImp
import javax.inject.Inject

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