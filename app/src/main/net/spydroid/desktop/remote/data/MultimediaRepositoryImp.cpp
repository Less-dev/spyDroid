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

#include "../domain/MultimediaRepository.h"
#include "../models/MultimediaHandler.h"

std::vector<MultimediaHandler> MultimediaRepositoryImp::getMultimedia(const std::string& alias) const {
    return multimediaDao.getMultimedia(alias);
}

// IMAGES
void MultimediaRepositoryImp::getImages(const std::string& alias) const {
    return multimediaDao.getImages(alias);
}
// VIDEOS
void MultimediaRepositoryImp::getVideos(const std::string& alias) const {
    return multimediaDao.getVideos(alias);
}
// DOCUMENTS 

void MultimediaRepositoryImp::getDocuments(const std::string& alias) const {
    return multimediaDao.getDocuments(alias);
}
// AUDIOS
void MultimediaRepositoryImp::getAudios(const std::string& alias) const {
    return multimediaDao.getAudios(alias);
}