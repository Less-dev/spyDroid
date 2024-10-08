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

#ifndef INFO_REPOSITORY_H
#define INFO_REPOSITORY_H

#include <vector>
#include <memory>
#include "../../../../../core-network/src/spydroid/network/models/Info.h"
#include "../../../../../core-network/src/spydroid/network/services/ApiService.h"
#include "../../../../../core-network/src/spydroid/network/daos/InfoDao.h"
#include "../models/InfoHandler.h"

class InfoRepository {
public:
    virtual ~InfoRepository() = default;

    
    virtual std::vector<InfoHandler> getInfo(const std::string& alias) const = 0;
};

class InfoRepositoryImp: public InfoRepository {
public:

    InfoRepositoryImp() = default;

    std::vector<InfoHandler> getInfo(const std::string& alias) const override;

private:
    InfoDaoImpl infoDao;
};

#endif // INFO_REPOSITORY_H
