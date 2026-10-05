#include "NKCanvas/NkCanvasApp.h"

using namespace nkentseu;

using namespace nkentseu::renderer;

class Coquille : public NkCanvasApp {

public:

    Coquille()

        : NkCanvasApp("Carre mobile", 800, 600),

          x(100.0f) {}

    void OnUpdate(float32 dt) override {

        x += 100.0f * dt;

    }

    void OnRender() override {

        auto& renderer = GetRenderer2D();

        renderer.DrawFilledRect(

            NkRect2f{x, 275.0f, 50.0f, 50.0f},

            NkColor2D{255, 0, 0, 255}

        );

    }

private:

    float32 x;

};

int nkmain(const NkEntryState&) {

    Coquille app;

    return app.Run();

}