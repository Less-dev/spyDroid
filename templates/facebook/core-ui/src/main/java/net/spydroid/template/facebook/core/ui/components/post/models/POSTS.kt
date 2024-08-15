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

package net.spydroid.template.facebook.core.ui.components.post.models

interface POSTS {
    val imageProfile: Int?
    val name: String
    val hour: String
    val content: Int
    val shares: Int?
    val reactions: Int?
    val showAllReactions: Boolean
    val showFavoriteReaction: Boolean
    val showSadReaction: Boolean
    val showAmazedReaction: Boolean
    val showAngryReaction: Boolean
    val showLikeReaction: Boolean
    val showImportantReaction: Boolean
    val showLikes: Boolean
    val showComments: Boolean
    val showShares: Boolean
}