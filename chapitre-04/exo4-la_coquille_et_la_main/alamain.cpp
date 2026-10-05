#include "NKWindow/NKWindow.h"

#include "NKWindow/NKMain.h"

#include "NKTime/NkTime.h"

#include "NKCanvas/Core/NkContextDesc.h"

#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"

#include "NKCanvas/Renderer/Core/NkRenderer2D.h"

using namespace nkentseu;

using namespace nkentseu::renderer;

int nkmain(const NkEntryState&) {

    NkWindowConfig cfg;

    cfg.title = "Carre mobile";

    cfg.width = 800;

    cfg.height = 600;

    NkWindow window;

    if (!window.Create(cfg))

        return -1;

    NkContextDesc desc;

    NkRenderWindow target(window, desc);

    if (!target.IsValid()) {

        window.Close();

        return -2;

    }

    NkClock clock;

    float32 x = 100.0f;

    while (window.IsOpen()) {

        float32 dt = clock.Tick().delta;

        while (NkEvent* event = NkEvents().PollEvent()) {

            (void)event;

        }

        x += 100.0f * dt;

        target.Clear(NkColor2D{18, 18, 24, 255});

        auto& renderer = target.GetRenderer2D();

        renderer.DrawFilledRect(

            NkRect2f{x, 275.0f, 50.0f, 50.0f},

            NkColor2D{255, 0, 0, 255}

        );

        target.Display();

    }

    return 0;

}