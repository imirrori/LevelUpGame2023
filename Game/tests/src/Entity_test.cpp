//
// Created by Dmitry Morozov on 9/4/23.
//

#include "Entity/Entity.hpp"

#include <gtest/gtest.h>

TEST(EntityTest, Constructor) {

  Entity e;

  EXPECT_EQ(e.GetTag(), "default");
  EXPECT_EQ(e.GetPosition(), glm::vec2(0.0f, 0.0f));
  EXPECT_EQ(e.GetRotation(), 0.0f);
  EXPECT_EQ(e.GetScale(), glm::vec2(1.0f, 1.0f));

}

TEST(EntityTest, SetTag) {
  Entity e;

  EXPECT_EQ(e.GetTag(), "default");
  std::string tag = "new tag";
  e.SetTag(tag);
  EXPECT_EQ(e.GetTag(), tag);

}


