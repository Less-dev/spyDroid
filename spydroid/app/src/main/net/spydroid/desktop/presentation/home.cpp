#include "home.h"
#include "profile.h"
#include <FL/Fl.H>


Home::Home() {
    int screen_width = Fl::w();
    int screen_height = Fl::h();
    
    window = new Fl_Window(50, 50, screen_width - 100, screen_height - 100, "home");
    
    window->size_range(500, 300);
    window->resizable(window);
    btnToProfile = new Fl_Button(100, 80, 100, 40, "Ir a Profile");
    
    // Asignar el callback para el botón
    btnToProfile->callback(navigateToProfile, this);
    
    window->end();
}

void Home::show() {
    window->show();
}

void Home::navigateToProfile(Fl_Widget* w, void* data) {
    Home* home = static_cast<Home*>(data);
    Fl::delete_widget(w->window());
    
    Profile profile;
    profile.show();  // Mostrar la ventana Profile
}
