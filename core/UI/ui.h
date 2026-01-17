#pragma once

#include <iostream>
#include <vector>

namespace UI
{
  class UI
  {
  public:
    UI();
    ~UI();
    void renderUI();
    void initUI(); //for renderer selection, other specifications.
    bool enableGUI{};

  private:
    int m_state = 0;
    bool m_GUI_enabled = false;
    unsigned int m_fps{};
    std::string initMsg;
    std::vector<std::string> TextCmdList;
  };
}