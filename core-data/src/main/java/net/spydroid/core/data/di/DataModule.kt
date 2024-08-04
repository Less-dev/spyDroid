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

import android.content.Context
import dagger.Binds
import dagger.Module
import dagger.hilt.InstallIn
import dagger.hilt.android.qualifiers.ApplicationContext
import dagger.hilt.components.SingletonComponent
import net.spydroid.core.data.repository.ChatBubbleRepository
import net.spydroid.core.data.repository.ChatBubbleRepositoryImp
import net.spydroid.core.data.repository.PreferenceManagerRepository
import net.spydroid.core.data.repository.PreferenceManagerRepositoryImp
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