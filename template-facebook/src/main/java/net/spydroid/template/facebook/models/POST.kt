package net.spydroid.template.facebook.models

internal data class POST(
    val imageProfile: Int? = null,
    val nameUser: String? = null,
    val hour: String? = null,
    val content: Int? = null,
    val reactions: Int? = null,
    val shares: String? = null,
    val showAllReactions: Boolean = false,
    val showFavoriteReaction: Boolean = false,
    val showSadReaction: Boolean = false,
    val showAmazedReaction: Boolean = false,
    val showAngryReaction: Boolean = false,
    val showLikeReaction: Boolean = false,
    val showImportantReaction: Boolean = false,
    val showLikes: Boolean = true,
    val showComments: Boolean = true,
    val showShares: Boolean = true,
)
