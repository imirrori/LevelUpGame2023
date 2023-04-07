
#ifndef LEVELUPGAME2023_GAME_MAINMENU_H_
#define LEVELUPGAME2023_GAME_MAINMENU_H_
#include "BaseMenu.h"
enum class Screen
{
  START, SAVE_SELECTION, ERASE,
};

class MainMenu {
 public:
  MainMenu();
  ~MainMenu();
  void Paint();
  void Time();

 private:

  void PaintBorder();
  void DrawBorderPlank(int plankIndex, int left, int top);
  void PaintCursor(int left, int top);
  void update();
  int m_CursorIndex;
  int m_MaxCursorIndex;
};

#endif //LEVELUPGAME2023_GAME_MAINMENU_H_
