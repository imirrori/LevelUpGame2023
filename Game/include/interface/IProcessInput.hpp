//
// Created by Dmitry Morozov on 27/4/23.
//

#ifndef MARIO_GAME_INCLUDE_INTERFACE_IPROCESSINPUT_HPP_
#define MARIO_GAME_INCLUDE_INTERFACE_IPROCESSINPUT_HPP_

class IProcessInput {

 public:

	virtual void processInput(float delta) = 0;

};

#endif //MARIO_GAME_INCLUDE_INTERFACE_IPROCESSINPUT_HPP_
