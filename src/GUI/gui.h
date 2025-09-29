#pragma once
#include <string>

//FIXME name 'GUI' could be conflicting
//FIXME an interface should be used in future, when other options are implemented.

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