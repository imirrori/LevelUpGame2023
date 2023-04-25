#include "KeyManager.hpp"

#include <algorithm>

void KeyManager::KeyAction(int                    key,
                           int                    scancode,
                           KeyManager::KEY_ACTION action,
                           int                    mods)
{
  auto itr = std::find_if(
    keysDown_.begin(),
    keysDown_.end(),
    [key](const Key& currentkey) {
    return currentkey.key == key;
  });

  switch (action)
  {
    case PRESS:

      if (itr != keysDown_.end()) {
        itr->mods = mods;
      } else {
        keysDown_.push_back(Key{ key, scancode, mods });
      }
      break;
    case RELEASE:

      if (itr != keysDown_.end()) {
        keysDown_.erase(itr);
      }
      break;
    default:
    case REPEAT:
      return;
  }
}

std::vector<KeyManager::Key>KeyManager::GetKeysDown()
{
  return keysDown_;
}
