package net.spydroid.common.remote.data

import android.content.Context
import net.spydroid.common.remote.domain.UploadFilesRepository
import net.spydroid.common.remote.network.daos.UploadFilesDao
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import java.io.File

class UploadFilesRepositoryHandler: UploadFilesRepository, KoinComponent {

    private val uploadFilesDao: UploadFilesDao by inject()
    override fun insertFile(context: Context, file: File, type: String, alias: String) =
        uploadFilesDao.insertFile(context, file, type, alias)
}