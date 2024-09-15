package net.spydroid.server.plugins

import io.ktor.http.HttpStatusCode
import io.ktor.http.content.*
import io.ktor.server.application.*
import io.ktor.server.response.*
import io.ktor.server.routing.*
import io.ktor.server.request.*
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
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

    // Crear directorios si no existen
    if (!dirs.ROOT.exists()) dirs.ROOT.mkdirs()
    if (!dirs.IMAGES.exists()) dirs.IMAGES.mkdirs()
    if (!dirs.VIDEOS.exists()) dirs.VIDEOS.mkdirs()
    if (!dirs.DOCS.exists()) dirs.DOCS.mkdirs()
    if (!dirs.AUDIOS.exists()) dirs.AUDIOS.mkdirs()

    routing {
        post("/upload/{type}") {
            val type = call.parameters["type"] ?: "unknown"
            val alias = call.request.queryParameters["alias"] ?: "default"
            val accessToken = call.request.queryParameters["access_token"]

            if (accessToken == null || !validTokens.contains(accessToken)) {
                call.respondText("Acceso denegado o token inválido!", status = HttpStatusCode.Forbidden)
                return@post
            }

            val targetDir = when (type.lowercase()) {
                "image" -> File(dirs.IMAGES, alias)
                "video" -> File(dirs.VIDEOS, alias)
                "audio" -> File(dirs.AUDIOS, alias)
                "document" -> File(dirs.DOCS, alias)
                else -> null
            }

            if (targetDir == null) {
                call.respondText("El tipo de archivo debe ser: image, video, audio o document.", status = HttpStatusCode.BadRequest)
                return@post
            }

            if (!targetDir.exists()) targetDir.mkdirs()

            val multipartData = call.receiveMultipart()

            // Procesar los archivos subidos
            var fileName = ""
            var fileDescription = ""

            multipartData.forEachPart { part ->
                when (part) {
                    is PartData.FormItem -> {
                        fileDescription = part.value
                    }
                    is PartData.FileItem -> {
                        fileName = part.originalFileName as String

                        val targetFile = File(targetDir, fileName)
                        if (targetFile.exists()) {
                            call.respondText("El archivo '$fileName' ya existe en '$alias'!", status = HttpStatusCode.Conflict)
                            part.dispose() // Liberar el recurso del part
                            return@forEachPart
                        }

                        val fileBytes = part.streamProvider().use { it.readBytes() }

                        try {
                            withContext(Dispatchers.IO) {
                                targetFile.writeBytes(fileBytes)
                            }
                        } catch (e: Exception) {
                            call.respondText("Error al subir el archivo: ${e.localizedMessage}", status = HttpStatusCode.InternalServerError)
                            part.dispose()
                            return@forEachPart
                        }
                    }
                    else -> {}
                }
                part.dispose() // Clean resources
            }

            call.respondText("$fileName ha sido subido exitosamente a 'uploads/$type/$alias'!")
        }
    }
}
