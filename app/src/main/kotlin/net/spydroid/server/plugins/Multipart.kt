package net.spydroid.server.plugins

import io.ktor.http.HttpStatusCode
import io.ktor.http.content.*
import io.ktor.server.application.*
import io.ktor.server.response.*
import io.ktor.server.routing.*
import io.ktor.server.request.*
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import java.io.File

fun Application.configurationMultipart(validTokens: Set<String>) {

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

    routing {
        var fileDescription = ""
        var fileName = ""

        post("/upload/{type}") {
            val type = call.parameters["type"] ?: "unknown" // Get file type

            val accessToken = call.request.queryParameters["access_token"]
            if (accessToken == null) {
                call.respondText("Access token is missing!", status = HttpStatusCode.Unauthorized)
                return@post
            }

            if (!validTokens.contains(accessToken)) {
                call.respondText("Invalid access token!", status = HttpStatusCode.Forbidden)
                return@post
            }

            val multipartData = call.receiveMultipart()

            val targetDir = when (type.lowercase()) {
                "image" -> dirs.IMAGES
                "video" -> dirs.VIDEOS
                "audio" -> dirs.AUDIOS
                "document" -> dirs.DOCS
                else -> null
            }

            if (targetDir == null) {
                call.respondText("File type must be one of: image, video, audio or document!", status = HttpStatusCode.BadRequest)
                return@post
            }

            // Multipart Process
            multipartData.forEachPart { part ->
                when (part) {
                    is PartData.FormItem -> {
                        fileDescription = part.value
                    }

                    is PartData.FileItem -> {
                        fileName = part.originalFileName as String

                        val fileBytes = part.streamProvider().use { inputStream ->
                            inputStream.readBytes()
                        }

                        // Aquí se asegura que la escritura sea asincrónica
                        launch(Dispatchers.IO) {
                            File("${targetDir.path}/$fileName").writeBytes(fileBytes)
                        }
                    }

                    else -> {}
                }
                part.dispose()
            }

            call.respondText("$fileName has been successfully uploaded to 'uploads/$type' !!")
        }
    }
}
