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

#ifndef MULTIMEDIA_DAO_H
#define MULTIMEDIA_DAO_H

#include <string>
#include <vector>
#include "../../../../../core-data/src/spydroid/data/models/MultimediaHandler.h"
#include "../services/ApiService.h"


class MultimediaDao {
public:
    virtual ~MultimediaDao() = default;
    
    virtual std::vector<MultimediaHandler> getMultimedia(const std::string& alias) const = 0;
    virtual void getImages(const std::string& alias) const = 0;
    virtual void getVideos(const std::string& alias) const = 0;
    virtual void getDocuments(const std::string& alias) const = 0;
    virtual void getAudios(const std::string& alias) const = 0;
};

class MultimediaDaoImpl : public MultimediaDao {
public:
    MultimediaDaoImpl() = default;
    std::vector<MultimediaHandler> getMultimedia(const std::string& alias) const override;
    void getImages(const std::string& alias) const override;
    void getVideos(const std::string& alias) const override;
    void getDocuments(const std::string& alias) const override;
    void getAudios(const std::string& alias) const override;
private:
    ApiService apiService;
};

#endif // MULTIMEDIA_DAO_H