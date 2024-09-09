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

#ifndef INFORMATION_MAIN_H
#define INFORMATION_MAIN_H

#include <iostream>
#include "../remote/models/DevicesHandler.h"
#include "../remote/models/InfoHandler.h"

struct INFORMATION_MAIN {
    std::vector<DevicesHandler> devicesHandler;
    std::vector<InfoHandler> infoHandler;
};

#endif // INFORMATION_MAIN_H