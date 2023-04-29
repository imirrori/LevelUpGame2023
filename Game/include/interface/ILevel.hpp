//
// Created by Dmitry Morozov on 8/4/23.
//

#ifndef MARIO_GAME_INCLUDE_INTERFACE_ILEVEL_HPP_
#define MARIO_GAME_INCLUDE_INTERFACE_ILEVEL_HPP_

#include "interface/IEntity.hpp"

class ILevel : public IEntity {
 public:
	virtual ~ILevel() = default;

	virtual std::vector<std::shared_ptr<IEntity>> getAllObjects() const = 0;

};

#endif //MARIO_GAME_INCLUDE_INTERFACE_ILEVEL_HPP_
