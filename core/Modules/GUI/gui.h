#pragma once
#ifndef OT_GUI_H
#define OT_GUI_H
#include "../ui.h"

//FIXME name 'GUI' could be conflicting
//FIXME an interface should be used in future, when other options are implemented.

namespace GUI
{
  class Button;
  class CheckBox;
  class Label;
  class MenuButton;
  class Timer;
//TODO:IMPLEMENT ME zaebal halturit (spasite)

  class GUI
  {
    GUI() = delete;
    explicit GUI(const std::string& name, unsigned int ID);
    ~GUI();
  public:
    static void init();
    static void update();
    static void render();
    static void shutdown();
  private:
    std::string m_name;
    unsigned int m_GUI_ID;
  };
}
#endif // OT_GUI_H