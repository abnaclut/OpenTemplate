#pragma once

#include <iostream>
#include <vector>

namespace UI
{
  class UI
  {
  public:
    UI();
    UI(bool GUI_enabled, std::string UI_mode);
    ~UI();
    void renderUI(bool GUI_enabled);
    void initUI(); //for renderer selection, other specifications.

  private:
    int m_state = 0; //for later
    bool m_GUI_enabled = false;
    std::string initMsg = "Initializing UI with parameters:\n";

    std::vector<std::string> TextCmdList =
      {
      "help",
      "gen",
      "setPath",
      "exit"
      //TODO: other
    };

    std::string m_UI_mode = "text"; //for later (imgui/qt/etc)
  };
}