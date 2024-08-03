package net.spydroid.template.facebook.data

import net.spydroid.template.facebook.R
import net.spydroid.template.facebook.models.POSTS

object PostImp {
    data object POST_01: POSTS {
        override val imageProfile: Int?
            get() = null
        override val name: String
            get() = "Juan Pedro"
        override val hour: String
            get() = "22:28 PM"
        override val content: Int
            get() = R.drawable.post_01
        override val shares: Int?
            get() = null
        override val reactions: Int?
            get() = 4
        override val showAllReactions: Boolean
            get() = false
        override val showFavoriteReaction: Boolean
            get() = true
        override val showSadReaction: Boolean
            get() = true
        override val showAmazedReaction: Boolean
            get() = false
        override val showAngryReaction: Boolean
            get() = false
        override val showLikeReaction: Boolean
            get() = false
        override val showImportantReaction: Boolean
            get() = true
        override val showLikes: Boolean
            get() = true
        override val showComments: Boolean
            get() = true
        override val showShares: Boolean
            get() = false
    }

    data object POST_02: POSTS {
        override val imageProfile: Int?
            get() = null
        override val name: String
            get() = "Luis"
        override val hour: String
            get() = "11:45 AM"
        override val content: Int
            get() = R.drawable.post_02
        override val shares: Int
            get() = 25
        override val reactions: Int
            get() = 7
        override val showAllReactions: Boolean
            get() = false
        override val showFavoriteReaction: Boolean
            get() = true
        override val showSadReaction: Boolean
            get() = true
        override val showAmazedReaction: Boolean
            get() = false
        override val showAngryReaction: Boolean
            get() = false
        override val showLikeReaction: Boolean
            get() = false
        override val showImportantReaction: Boolean
            get() = false
        override val showLikes: Boolean
            get() = false
        override val showComments: Boolean
            get() = true
        override val showShares: Boolean
            get() = true
    }


    data object POST_03: POSTS {
        override val imageProfile: Int?
            get() = null
        override val name: String
            get() = "Luis"
        override val hour: String
            get() = "00:45 AM"
        override val content: Int
            get() = R.drawable.post_default
        override val shares: Int
            get() = 276
        override val reactions: Int
            get() = 415
        override val showAllReactions: Boolean
            get() = false
        override val showFavoriteReaction: Boolean
            get() = true
        override val showSadReaction: Boolean
            get() = false
        override val showAmazedReaction: Boolean
            get() = false
        override val showAngryReaction: Boolean
            get() = false
        override val showLikeReaction: Boolean
            get() = false
        override val showImportantReaction: Boolean
            get() = true
        override val showLikes: Boolean
            get() = true
        override val showComments: Boolean
            get() = true
        override val showShares: Boolean
            get() = true
    }
}