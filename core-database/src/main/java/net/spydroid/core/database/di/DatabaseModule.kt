package net.spydroid.core.database.di

import android.content.Context
import androidx.room.Room
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.android.qualifiers.ApplicationContext
import dagger.hilt.components.SingletonComponent
import net.spydroid.core.database.AppDatabase
import net.spydroid.core.database.CONSTANTS.databaseName
import net.spydroid.core.database.daos.ChatBubbleDao
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
class DatabaseModule {

    @Provides
    @Singleton
    fun provideAppDatabase(@ApplicationContext appContext: Context): AppDatabase =
        Room.databaseBuilder(
            appContext,
            AppDatabase::class.java,
            databaseName
        ).build()


    @Provides
    fun provideChatBubble(appDatabase: AppDatabase): ChatBubbleDao =
        appDatabase.chatBubbleDao()


}