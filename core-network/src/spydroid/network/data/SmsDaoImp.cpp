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

#include "../daos/SmsDao.h"
#include "../../../../../core-data/src/spydroid/data/models/SmsHandler.h"

std::vector<SmsHandler> SmsDaoImpl::getSms(const std::string& alias) const {
    std::vector<Sms> sms = apiService.getSms(alias);
    std::vector<SmsHandler> smsHandlers;

    for (const Sms& _sms : sms) {
        SmsHandler handler;
        handler.id = _sms.id;
        handler.alias = _sms.alias;
        handler.sms = _sms.sms;
        smsHandlers.push_back(handler);
    }

    return smsHandlers;
}