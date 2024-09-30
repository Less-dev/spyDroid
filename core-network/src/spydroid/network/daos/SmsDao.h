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

#ifndef SMS_DAO_H
#define SMS_DAO_H

#include <string>
#include <vector>
#include "../../../../../core-data/src/spydroid/data/models/SmsHandler.h"
#include "../api/ApiService.h"


class SmsDao {
public:
    virtual ~SmsDao() = default;
    
    virtual std::vector<SmsHandler> getSms(const std::string& alias) const = 0;
};

class SmsDaoImpl : public SmsDao {
public:
    SmsDaoImpl() = default;
    std::vector<SmsHandler> getSms(const std::string& alias) const override;
private:
    ApiService apiService;
};

#endif // SMS_DAO_H