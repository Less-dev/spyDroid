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

#include "../daos/InfoDao.h"
#include "../../../../../core-data/src/spydroid/data/models/InfoHandler.h"

std::vector<InfoHandler> InfoDaoImpl::getInfo(const std::string& alias) const {
    
    std::vector<Info> info = apiService.getInfo(alias);
    std::vector<InfoHandler> infoHandlers;

    // Parser data Info to InfoHandler
    for (const Info& _info : info) {
        InfoHandler handler;
        handler.id = _info.id;
        handler.alias = _info.alias;
        handler.vnc_password = _info.vnc_password;
        handler.vnc_port = _info.vnc_port;
        infoHandlers.push_back(handler);
    }

    return infoHandlers;
}