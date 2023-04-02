//
// Created by Dmitry Morozov on 30/3/23.
//

#include "Input.hpp"

 bool Input::GetKey(int key) {
   return keys[key];
 }

bool Input::GetKeyDown(int key)
{
  if (!keyUp[key] && keys[key])
  {
	keyUp[key] = true;
	return true;
  }
  else
  {
	return false;
  }
}