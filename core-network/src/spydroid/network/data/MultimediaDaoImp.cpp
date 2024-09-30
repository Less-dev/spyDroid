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

#include "../daos/MultimediaDao.h"
#include "../../../../../core-data/src/spydroid/data/models/MultimediaHandler.h"

std::vector<MultimediaHandler> MultimediaDaoImpl::getMultimedia(const std::string& alias) const {
    std::vector<Multimedia> multimedia = apiService.getMultimeida(alias);
    std::vector<MultimediaHandler> multimediaHandlers;

    // Parser data Multimedia to MultimediaHandler
    for (const Multimedia& _multimedia : multimedia) {
        MultimediaHandler handler;
        handler.id = _multimedia.id;
        handler.alias = _multimedia.alias;
        handler.routeFile = _multimedia.routeFile;
        handler.type = _multimedia.type;
        multimediaHandlers.push_back(handler);
    }

    return multimediaHandlers;
}


// IMAGES
void MultimediaDaoImpl::getImages(const std::string& alias) const {
    return apiService.getImages(alias);
}
// VIDEOS
void MultimediaDaoImpl::getVideos(const std::string& alias) const {
    return apiService.getVideos(alias);
}
// DOCUMENTS
void MultimediaDaoImpl::getDocuments(const std::string& alias) const {
    return apiService.getDocuments(alias);
}

// AUDIOS
void MultimediaDaoImpl::getAudios(const std::string& alias) const {
    return apiService.getAudios(alias);
}

