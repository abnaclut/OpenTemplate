#pragma once
#include <string>

//FIXME name 'GUI' could be conflicting
//FIXME an interface should be used in future, when other options are implemented.

class Button;
class CheckBox;
class Label;
class MenuButton;
class Timer;
//TODO:IMPLEMENT ME zaebal halturit

class GUI
{
  //FIXME to be reworked a lot, so its bad, but it works
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