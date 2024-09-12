package net.spydroid.server.plugins

import io.ktor.http.content.*
import io.ktor.server.application.*
import io.ktor.server.response.*
import io.ktor.server.routing.*
import io.ktor.server.request.*
import java.io.File

fun Application.configurationMultipart() {
    routing {
        var fileDescription = ""
        var fileName = ""

        post("/upload/{type}") { // Se recibe el tipo de archivo como parámetro en la URL
            val type = call.parameters["type"] ?: "unknown" // Obtiene el tipo de archivo
            val multipartData = call.receiveMultipart()

            val dirs = object {
                private val UPLOADS = "uploads"
                val ROOT = File(UPLOADS)
                val IMAGES = File("$UPLOADS/images")
                val VIDEOS = File("$UPLOADS/videos")
                val DOCS = File("$UPLOADS/docs")
                val AUDIOS = File("$UPLOADS/audios")
            }

            if (!dirs.ROOT.exists()) dirs.ROOT.mkdirs()
            if (!dirs.IMAGES.exists()) dirs.IMAGES.mkdirs()
            if (!dirs.VIDEOS.exists()) dirs.VIDEOS.mkdirs()
            if (!dirs.DOCS.exists()) dirs.DOCS.mkdirs()
            if (!dirs.AUDIOS.exists()) dirs.AUDIOS.mkdirs()

            val targetDir = when (type.lowercase()) {
                "image" -> dirs.IMAGES
                "video" -> dirs.VIDEOS
                "audio" -> dirs.AUDIOS
                "document" -> dirs.DOCS
                else -> null
            }

            if (targetDir == null) {
                call.respondText("image, video, audio or document !!")
                return@post
            }

            // Procesa los datos multipart
            multipartData.forEachPart { part ->
                when (part) {
                    is PartData.FormItem -> {
                        fileDescription = part.value
                    }

                    is PartData.FileItem -> {
                        fileName = part.originalFileName as String
                        val fileBytes = part.streamProvider().readBytes()

                        // Guarda el archivo en el directorio correspondiente
                        File("${targetDir.path}/$fileName").writeBytes(fileBytes)
                    }

                    else -> {}
                }
                part.dispose()
            }

            call.respondText("$fileName ha sido subido correctamente a 'uploads/$type'")
        }
    }
}
