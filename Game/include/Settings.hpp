#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "interface/ISettings.hpp"

#include <istream>
#include <unordered_map>
#include <string>

namespace Settings {
class Settings
  : public ISettings {
public:

  explicit Settings(std::istream& inStream);
  ~Settings() override;

  ValueType GetValue(const std::string& subsystem,
                     const std::string& name) override;

  bool      SetValue(const std::string& subsystem,
                     const std::string& name,
                     const ValueType  & value) override;

private:

  std::unordered_map<std::string,
                     std::unordered_map<std::string, ValueType> >data_;
};
} // namespace Settings

#endif // SETTINGS_HPP
