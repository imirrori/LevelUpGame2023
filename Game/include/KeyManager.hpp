#ifndef KEYMANAGER_HPP
#define KEYMANAGER_HPP

#include <vector>

class KeyManager {
public:

  enum KEY_ACTION
  {
    RELEASE,
    PRESS,
    REPEAT
  };

  enum KEY_MODS
  {
    MOD_SHIFT     = 0x0001,
    MOD_CONTROL   = 0x0002,
    MOD_ALT       = 0x0004,
    MOD_SUPER     = 0x0008,
    MOD_CAPS_LOCK = 0x0010,
    MOD_NUM_LOCK  = 0x0010
  };

  struct Key
  {
    int key;
    int scancode;
    int mods;
  };

  void KeyAction(int        key,
                 int        scancode,
                 KEY_ACTION action,
                 int        mods);

  std::vector<Key>GetKeysDown();

private:

  std::vector<Key>keysDown_;
};

#endif // KEYMANAGER_HPP
