
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
  virtual ~MainMenu()=0;
  virtual void Paint()=0;
  virtual void Time()=0;
  virtual void  StartPrint();
  virtual void  PrintRow();
  virtual void EndPrint();

 private:

  virtual void PaintBorder()=0;
  virtual void DrawBorderPlank(int plankIndex, int left, int top)=0;
  virtual void PaintCursor(int left, int top)=0;
  virtual void update()=0;
  int m_CursorIndex;
  int m_MaxCursorIndex;
};

#endif //LEVELUPGAME2023_GAME_MAINMENU_H_
