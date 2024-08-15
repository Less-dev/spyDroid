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

data class POST(
    val imageProfile: Int? = null,
    val nameUser: String? = null,
    val hour: String? = null,
    val content: Int? = null,
    val reactions: Int? = null,
    val shares: Int? = null,
    val showAllReactions: Boolean = false,
    val showFavoriteReaction: Boolean = false,
    val showSadReaction: Boolean = false,
    val showAmazedReaction: Boolean = false,
    val showAngryReaction: Boolean = false,
    val showLikeReaction: Boolean = false,
    val showImportantReaction: Boolean = false,
    val showLikes: Boolean = true,
    val showComments: Boolean = true,
    val showShares: Boolean = true
)
