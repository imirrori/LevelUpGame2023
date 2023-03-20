//
// Created by Dmitry Morozov on 20/3/23.
//

#include "Game.h"

#include <gtest/gtest.h>

TEST(Game, Constructor_Test) {

	Game game;

	EXPECT_NO_THROW(game.Run());

}
