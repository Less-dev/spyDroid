#ifndef HOME_H
#define HOME_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

class Home {
public:
    Home();     // Constructor
    void show(); // Método para mostrar la ventana
    
private:
    Fl_Window *window;
    Fl_Button *btnToProfile;
    
    static void navigateToProfile(Fl_Widget* w, void* data); // Callback para navegar a la vista Profile
};

#endif // HOME_H
