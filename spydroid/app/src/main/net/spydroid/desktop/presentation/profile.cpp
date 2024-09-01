#include "profile.h"
#include "home.h"
#include <FL/Fl.H>
#include "../models/VncData.h"
#include "../data/VncConnect.h"
#include "iostream"


static VncData vncData;

Profile::Profile() {
    int screen_width = Fl::w();
    int screen_height = Fl::h();

    vncData.ip = "192.168.100.242";
    vncData.puerto = 5300;

    
    window = new Fl_Window(50, 50, screen_width - 100, screen_height - 100, "profile");
    
    window->size_range(500, 300);
    window->resizable(window);

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
