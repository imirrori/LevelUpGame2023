#include "Settings.hpp"

#include <gtest/gtest.h>

TEST(SettingsTests, CreateTest)
{
  std::istringstream stream;
  Settings::Settings settings(stream);
}

TEST(SettingsTests, GetValueTest)
{
  std::stringstream  stream{ R"--(
[subsystem]
name1=123
name2="value")--" };
  Settings::Settings settings(stream);

  EXPECT_EQ(std::get<int>(settings.GetValue("subsystem", "name1")), 123);
  EXPECT_STREQ(std::get<std::string>(settings.GetValue("subsystem",
                                                       "name2")).c_str(),
               "value");
}

TEST(SettingsTests, SetValueTest)
{
  std::stringstream  stream{};
  Settings::Settings settings(stream);

  settings.SetValue("subsystem", "name1", 123);
  settings.SetValue("subsystem", "name2", "value");

  EXPECT_EQ(std::get<int>(settings.GetValue("subsystem", "name1")), 123);
  EXPECT_STREQ(std::get<std::string>(settings.GetValue("subsystem",
                                                       "name2")).c_str(),
               "value");
}
