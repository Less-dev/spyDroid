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

package net.spydroid.core.data.di

import dagger.Binds
import dagger.Module
import dagger.hilt.InstallIn
import dagger.hilt.components.SingletonComponent
import net.spydroid.core.data.data.ChatBubbleRepositoryImp
import net.spydroid.core.data.data.PreferenceManagerRepositoryImp
import net.spydroid.core.data.domain.ChatBubbleRepository
import net.spydroid.core.data.domain.PreferenceManagerRepository
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
interface DataModule {

    @Singleton
    @Binds
    fun bindsChatBubbleRepository(
        chatBubbleRepositoryImp: ChatBubbleRepositoryImp
    ): ChatBubbleRepository

    @Binds
    @Singleton
    fun bindPreferenceManagerRepository(
        preferenceManagerRepositoryImp: PreferenceManagerRepositoryImp
    ): PreferenceManagerRepository

}