#include <FL/Fl.H>
#include "presentation/home.h"


int main(int argc, char **argv) {
    Home home;  // Home Instance
    home.show(); // Show view main
    
    return Fl::run(); // Init fltk
}