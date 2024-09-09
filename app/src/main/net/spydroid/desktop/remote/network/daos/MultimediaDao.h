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
#include "../api/ApiService.h"
#include "../../models/MultimediaHandler.h"


class MultimediaDao {
public:
    virtual ~MultimediaDao() = default;
    
    // Método que retorna un dispositivo basado en un alias
    virtual std::vector<MultimediaHandler> getMultimedia(const std::string& alias) const = 0;
};

class MultimediaDaoImpl : public MultimediaDao {
public:
    MultimediaDaoImpl() = default;
    std::vector<MultimediaHandler> getMultimedia(const std::string& alias) const override;
private:
    ApiService apiService;  // Instancia de ApiService manejada internamente
};

#endif // MULTIMEDIA_DAO_H