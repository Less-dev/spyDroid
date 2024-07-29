package net.spydroid.core.data.di

import dagger.Binds
import dagger.Module
import dagger.hilt.InstallIn
import dagger.hilt.components.SingletonComponent
import net.spydroid.core.data.repository.ChatBubbleRepository
import net.spydroid.core.data.repository.ChatBubbleRepositoryImp
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
interface DataModule {

    @Singleton
    @Binds
    fun bindsChatBubbleRepository(
        chatBubbleRepositoryImp: ChatBubbleRepositoryImp
    ): ChatBubbleRepository
    
}