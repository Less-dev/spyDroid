package net.spydroid.core.data.models

data class ChatBubbleImp(
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