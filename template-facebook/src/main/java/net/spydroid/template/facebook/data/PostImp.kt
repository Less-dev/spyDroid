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

package net.spydroid.template.facebook.data

import net.spydroid.template.facebook.models.POSTS
import net.spydroid.core.ui.R

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