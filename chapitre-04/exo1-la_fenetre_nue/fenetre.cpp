#include "NKWindow/NKMain.h"

#include "NKCanvas/NKCanvasApp.h"

class Fenetre : public NkCanvasApp {

public:

    Fenetre()

        : NkCanvasApp("La fenetre nue", 1280, 720, NkColor2D(18, 18, 24))

    {

    }

};

int nkmain(const NkEntryState& state) {

    return NkCanvasApp::Run<Fenetre>(state);

}