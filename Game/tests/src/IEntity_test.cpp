//
// Created by Dmitry Morozov on 20/3/23.
//

#include "interface/IEntity.hpp"

#include <gtest/gtest.h>

class TestClass : public IEntity {
 public:
  ~TestClass() override = default;

  [[nodiscard]] std::string GetTag() const override { return vTag; };
  void SetTag(std::string &tag) override { vTag = tag; };

  [[nodiscard]] glm::vec2 GetPosition() const override { return vPosition; };
  [[nodiscard]] float GetRotation() const override { return vRotation; };
  [[nodiscard]] glm::vec2 GetScale() const override { return vScale; };

  void onUpdate(float delta) override {};
  void onRender() override {};
  void onCollision(IEntity *collision_entity) override {};

 protected:

  static constexpr float pixelToM_ = 150.f;

  std::string vTag = "default";

  glm::vec2 vPosition = glm::vec2(0.0f, 0.0f);
  float vRotation = 0.0f;
  glm::vec2 vScale = glm::vec2(1.0f, 1.0f);
};

TEST(IEntityTest, Ingeritance_Test) {

  EXPECT_NO_THROW(TestClass test_object = TestClass());

  TestClass test_object = TestClass();

  EXPECT_EQ(test_object.GetTag(), "default");
  EXPECT_EQ(test_object.GetPosition(), glm::vec2(0.0f, 0.0f));
  EXPECT_EQ(test_object.GetRotation(), 0.0f);
  EXPECT_EQ(test_object.GetScale(), glm::vec2(1.0f, 1.0f));
  EXPECT_EQ(test_object.GetPosition().x, 0.0f);
  EXPECT_EQ(test_object.GetPosition().y, 0.0f);
  EXPECT_EQ(test_object.GetRotation(), 0.0f);
  EXPECT_EQ(test_object.GetScale().x, 1.0f);
  EXPECT_EQ(test_object.GetScale().y, 1.0f);

  std::string test_tag = "TestTag";
  test_object.SetTag(test_tag);

  EXPECT_EQ(test_object.GetTag(), test_tag);
}