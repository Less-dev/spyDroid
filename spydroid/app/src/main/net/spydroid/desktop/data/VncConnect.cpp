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

#include "VncConnect.h"
#include "../models/VncData.h"
#include "../../../../../../../features/vncviewer/vncviewer.h"

void VncConnect(Fl_Widget *w, void *data) {
    VncData* vncData = static_cast<VncData*>(data);
    connectToVNCServer(vncData->ip, vncData->port);
}