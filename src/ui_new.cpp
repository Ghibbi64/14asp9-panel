#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include <thread>
#include <iostream>
#include "ui_new.h"
#include "ec/ec.h"
#include "ec/other.h"

using namespace ftxui;

int f0[6] = {0,0,0,0,0,0};
int f1[6] = {0,0,0,0,0,0};

void fetch_fans_data(ScreenInteractive* screen);
 
int show_ui() {

    auto screen = ScreenInteractive::Fullscreen();
    std::thread t_fans(fetch_fans_data, &screen);
    t_fans.detach();

    auto ui = Renderer([&]{
      return vbox({
        text("Lenovo Yoga Pro 7 Control Panel") | bold | center,
        separator(),
        hbox({
          vbox({
            text("     Fans     ") | center,
            text("Keyboard") | center,
            text("Camera") | center,
          }) | border,
          vbox({
            vbox({
              text("Fans Infos") | center | bold,
              text("RPM Sensor"),
              hbox({
                  text("FAN0: "+ std::to_string(f0[0])+" ") | center,
                  border(gauge(f0[0]/10000.0)),
              }),
              hbox({
                  text("FAN1: "+  std::to_string(f1[0])+" ") | center,
                  border(gauge(f1[0]/10000.0)),
              }),
            }),
            separator(),
            text("Footer Information") | dim,
          }) | border | flex,
        }) | flex,
      });
    });


    ui = CatchEvent(ui, [&](Event event) {
      if (event == Event::Character('q') || event == Event::Escape) {
        screen.Exit();
        return true;
      }
      return false;
    });

    screen.Loop(ui);  // blocks until screen.Exit() is called
    return 0;
}

void fetch_fans_data(ScreenInteractive* screen) {
    while (true) {
        getFanInfos(0, f0);
        getFanInfos(1, f1);
        screen->PostEvent(Event::Custom);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}