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
int f0_raw_t = 0;
int f1_raw_t = 0;

void update(ScreenInteractive* screen);

Element fans_panel(Component& slider_f0, Component& slider_f1) {
    return vbox({
        text("Fans Infos") | center | bold,
        text((f0[3]==0 && f1[3]==0) ? "AUTO MODE" : "MANUAL MODE") | bold,
        text("RPM Sensor"),
        hbox({
            text("FAN0: " + std::to_string(f0[0]) + " ") | center,
            gauge(f0[0] / 6250.0f) | border | flex, //max seems to be 6250~6300
        }),
        hbox({
            text("FAN1: " + std::to_string(f1[0]) + " ") | center,
            gauge(f1[0] / 6250.0f) | border | flex, //max seems to be 6250~6300
        }),
        text(""),
        text("Manual speed override (set everything to 0 for AUTO MODE)"),
        slider_f0->Render(),
        slider_f1->Render(),
    });
}
 
int show_ui() {

    auto screen = ScreenInteractive::Fullscreen();
    std::thread t_fans(update, &screen);
    t_fans.detach();

    auto slider_f0 = Slider("FAN0 CONTROL: ["+std::to_string(f0_raw_t)+"]", &f0_raw_t, 0, 127, 1);
    auto slider_f1 = Slider("FAN1 CONTROL: ["+std::to_string(f1_raw_t)+"]", &f1_raw_t, 0, 127, 1);

    auto sliders = Container::Vertical({
        slider_f0,
        slider_f1,
    });

    auto ui = Renderer(sliders, [&]{
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
            fans_panel(slider_f0, slider_f1),
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

    screen.Loop(ui);
    return 0;
}

void update(ScreenInteractive* screen) {
    while (true) {
        getFanInfos(0, f0);
        getFanInfos(1, f1);
        if(f0_raw_t==0 && f1_raw_t==0){ //set to auto
            setAuto();
        }else{
            if(f0_raw_t==0){
                setRAW(0, 1);
            }else{
                setRAW(0, f0_raw_t);
            }
            
            if(f1_raw_t==0){
                setRAW(1, 1);
            }else{
                setRAW(1, f1_raw_t);
            }
        }
        
        screen->PostEvent(Event::Custom);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}