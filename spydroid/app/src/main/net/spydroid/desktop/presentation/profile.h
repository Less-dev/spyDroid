#ifndef PROFILE_H
#define PROFILE_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

class Profile {
public:
    Profile();     // Constructor
    void show();   // Método para mostrar la ventana
    
private:
    Fl_Window *window;
    Fl_Button *btnBackToHome;
    
    static void navigateToHome(Fl_Widget* w, void* data); // Callback para navegar de vuelta a Home
};

#endif // PROFILE_H
