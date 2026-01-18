#include "ui.h"

#include <utility>

namespace UI
{
  UI::UI() = default;
  UI::~UI() = default;

  UI::UI(const bool GUI_enabled, std::string UI_mode)
  {
    m_GUI_enabled = GUI_enabled;
    m_UI_mode = std::move(UI_mode);
  }

  void UI::renderUI(const bool GUI_enabled)
  {
    if (GUI_enabled)
    {
      //renderGUI();
    }

    if (!GUI_enabled)
    {
      //render text UI

    }
  }
}
