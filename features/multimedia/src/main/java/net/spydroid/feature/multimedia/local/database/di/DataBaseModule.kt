package net.spydroid.feature.multimedia.local.database.di

import android.content.Context
import androidx.room.Room
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.android.qualifiers.ApplicationContext
import dagger.hilt.components.SingletonComponent
import net.spydroid.feature.multimedia.local.database.MultimediaDataBase
import javax.inject.Singleton


@Module
@InstallIn(SingletonComponent::class)
class DataBaseModule {
    @Provides
    @Singleton
    fun provideDataBase(@ApplicationContext context: Context) =
        Room.databaseBuilder(
            context,
            MultimediaDataBase::class.java,
            "multimedia_data_base"
        ).build()

    @Provides
    @Singleton
    fun provideImageDao(multimediaDataBase: MultimediaDataBase) =
        multimediaDataBase.imageDao()

    @Provides
    @Singleton
    fun provideVideoDao(multimediaDataBase: MultimediaDataBase) =
        multimediaDataBase.videoDao()

    @Provides
    @Singleton
    fun provideAudioDao(multimediaDataBase: MultimediaDataBase) =
        multimediaDataBase.audioDao()

}