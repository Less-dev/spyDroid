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

#include "profile.h"
#include "home.h"
#include <FL/Fl.H>
#include "../models/VncData.h"
#include "../data/VncConnect.h"
#include "../data/colors.h"
#include "iostream"



static VncData vncData;

Profile::Profile() {
    int screen_width = Fl::w();
    int screen_height = Fl::h();

    window = new Fl_Window(50, 50, screen_width - 100, screen_height - 100, "profile");
    window->color(background);
    window->size_range(500, 300);
    window->resizable(window);

    vncData.ip = "192.168.100.242";
    vncData.port = 5300;


    btnBackToHome = new Fl_Button(100, 80, 100, 40, "Volver a Home");
    
    // Asignar el callback para el botón
    btnBackToHome->callback(navigateToHome, this);

    Fl_Button *button = new Fl_Button(10, 10, 150, 30, "open vnc server");

    button->callback(VncConnect, &vncData);
    
    window->end();
}

void Profile::show() {
    window->show();
}

void Profile::navigateToHome(Fl_Widget* w, void* data) {
    Profile* profile = static_cast<Profile*>(data);
    Fl::delete_widget(w->window());
    
    Home home;
    home.show();  // Mostrar la ventana Home
}
