#include "../../../../../../features/vncviewer/vncviewer.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <iostream>

struct ButtonData {
    std::string ip;
    int puerto;
};

void button_callback(Fl_Widget *w, void *data) {
    // Reinterpretar el puntero de datos
    ButtonData* btnData = static_cast<ButtonData*>(data);

    // Marcar la ventana para ser eliminada
    Fl::delete_widget(w->window());

    // Llamar a la función connectToVNCServer después de cerrar la ventana
   connectToVNCServer(btnData->ip, btnData->puerto);

    // Cerrar la ventana después de realizar la conexión
    Fl::delete_widget(w->window());
}

int main(int argc, char** argv) {

    std::string ip = "192.168.100.242";
    int puerto = 5300;

    ButtonData btnData = { ip, puerto };

    int screen_width = Fl::w();
    int screen_height = Fl::h();
    
    Fl_Window *window = new Fl_Window(50, 50, screen_width - 100, screen_height - 100, "spydroid");
    
    window->size_range(500, 300);
    window->resizable(window);
    
    Fl_Button *button = new Fl_Button(10, 10, 150, 30, "open vnc server");
    

    button->callback(button_callback, &btnData);

    window->show();
    
    return Fl::run();
}