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

package net.spydroid.server.plugins

import io.ktor.http.ContentType
import io.ktor.http.HttpHeaders
import io.ktor.http.HttpStatusCode
import io.ktor.server.application.*
import io.ktor.server.response.*
import io.ktor.server.routing.*
import java.io.BufferedInputStream
import java.io.File
import java.io.FileInputStream
import java.util.zip.ZipEntry
import java.util.zip.ZipOutputStream


fun Application.configureFileDownload(validTokens: Set<String>) {

    val dirs = object {
        private val UPLOADS = "uploads"
        val IMAGES = File("$UPLOADS/images")
        val VIDEOS = File("$UPLOADS/videos")
        val DOCS = File("$UPLOADS/docs")
        val AUDIOS = File("$UPLOADS/audios")
    }

    routing {
        get("/download/{type}") {
            val type = call.parameters["type"] ?: return@get call.respond(HttpStatusCode.BadRequest, "File type require")
            val alias = call.request.queryParameters["alias"]?.replace("..", "") ?: return@get call.respond(HttpStatusCode.BadRequest, "Alias es requerido")
            val accessToken = call.request.queryParameters["access_token"]

            if (accessToken == null || !validTokens.contains(accessToken)) {
                return@get call.respond(HttpStatusCode.Forbidden,
                    "Access granted. Invalid Token"
                )
            }

            val targetDir = when (type.lowercase()) {
                "image" -> File(dirs.IMAGES, alias)
                "video" -> File(dirs.VIDEOS, alias)
                "audio" -> File(dirs.AUDIOS, alias)
                "document" -> File(dirs.DOCS, alias)
                else -> return@get call.respond(HttpStatusCode.BadRequest,
                    "image, video, audio or document !!"
                )
            }

            if (!targetDir.exists() || !targetDir.isDirectory) {
                return@get call.respond(HttpStatusCode.NotFound,
                    "'$alias' does no exists in category '$type'"
                )
            }

            val files = targetDir.listFiles()
            if (files.isNullOrEmpty()) {
                return@get call.respond(HttpStatusCode.NotFound,
                    "Does not exists '$alias' in '$type'" +
                            "")
            }

            // Prepare zip for the response
            call.response.header(HttpHeaders.ContentDisposition, "attachment; filename=\"$alias-$type.zip\"")
            call.respondOutputStream(ContentType.Application.Zip) {
                ZipOutputStream(this).use { zip ->
                    files.forEach { file ->
                        zip.putNextEntry(ZipEntry(file.name))
                        FileInputStream(file).use { fis ->
                            BufferedInputStream(fis).use { bis ->
                                bis.copyTo(zip)
                            }
                        }
                        zip.closeEntry()
                    }
                }
            }
        }
    }
}
