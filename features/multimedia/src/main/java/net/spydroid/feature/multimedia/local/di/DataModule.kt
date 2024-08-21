package net.spydroid.feature.multimedia.local.di

import dagger.Binds
import dagger.Module
import dagger.hilt.InstallIn
import dagger.hilt.components.SingletonComponent
import net.spydroid.feature.multimedia.local.data.AudioRepositoryHandler
import net.spydroid.feature.multimedia.local.data.ImageRepositoryHandler
import net.spydroid.feature.multimedia.local.data.VideoRepositoryHandler
import net.spydroid.feature.multimedia.local.domain.AudioRepository
import net.spydroid.feature.multimedia.local.domain.ImageRepository
import net.spydroid.feature.multimedia.local.domain.VideoRepository
import javax.inject.Singleton


@Module
@InstallIn(SingletonComponent::class)
interface DataModule {
    @Singleton
    @Binds
    fun provideImageRepository(imageRepositoryHandler: ImageRepositoryHandler): ImageRepository

    @Singleton
    @Binds
    fun provideVideoRepository(videoRepositoryHandler: VideoRepositoryHandler): VideoRepository

    @Singleton
    @Binds
    fun provideAudioRepository(audioRepositoryHandler: AudioRepositoryHandler): AudioRepository
}