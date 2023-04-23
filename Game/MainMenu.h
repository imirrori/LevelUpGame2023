
#ifndef LEVELUPGAME2023_GAME_MAINMENU_H_
#define LEVELUPGAME2023_GAME_MAINMENU_H_
using namespace std;
#include <map>
#include <vector>
#include "IEntity.hpp"

class Option_cursor
{
 public:
  bool update();
  Option_cursor();
  std::map<std::string, int>levels_top_score;
 private:
  bool render();
  int level_id = -1;
  std::vector<std::string>levels;

};
class MainMenu: public IEntity{
 public:
  MainMenu();
  virtual ~MainMenu() = 0;
   void Paint();
  void StartPrint();
  void PrintRow();
  void EndPrint();

 private:
  void PaintBorder();
  void DrawBorderPlank(int plankIndex, int left, int top);
  void PaintCursor(int left, int top);
  void update();
  int m_CursorIndex;
  int m_MaxCursorIndex;
};

#endif //LEVELUPGAME2023_GAME_MAINMENU_H_
