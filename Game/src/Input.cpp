//
// Created by Dmitry Morozov on 30/3/23.
//

#include "Input.hpp"

bool Input::keys[1024];
bool Input::keyUp[1024];

bool Input::GetKey(int key) {
  return keys[key];
}

bool Input::GetKeyDown(int key) {
  if (!keyUp[key] && keys[key]) {
	keyUp[key] = true;
	return true;
  }
  else
  {
	return false;
  }
}