#include "VncConnect.h"
#include "../models/VncData.h"
#include "../../../../../../../features/vncviewer/vncviewer.h"

void VncConnect(Fl_Widget *w, void *data) {
    VncData* vncData = static_cast<VncData*>(data);
    connectToVNCServer(vncData->ip, vncData->puerto);
}