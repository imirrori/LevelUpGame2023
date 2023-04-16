#include "Settings.hpp"

namespace Settings {
Settings::Settings(std::istream& inStream)
{
  std::string temp;
  std::string subsustem;

  while (std::getline(inStream, temp))
  {
    if (temp.empty()) {
      continue;
    }

    if ((temp.front() == '[') && (temp.back() == ']')) {
      subsustem = temp.substr(1, temp.size() - 2);
      continue;
    }

    auto pos = temp.find('=');

    if (pos == std::string::npos) {
      continue;
    }

    const std::string key   = temp.substr(0, pos);
    const std::string value = temp.substr(pos + 1);

    if ((value.front() == '"') && (value.back() == '"')) {
      data_[subsustem][key] = value.substr(1, value.size() - 2);
    } else {
      data_[subsustem][key] = std::stoi(value);
    }
  }
}

Settings::~Settings() = default;

Settings::ValueType Settings::GetValue(const std::string& subsystem,
                                       const std::string& name)
{
  return data_[subsystem][name];
}

bool Settings::SetValue(const std::string        & subsystem,
                        const std::string        & name,
                        const Settings::ValueType& value)
{
  data_[subsystem][name] = value;
  return true;
}
} // namespace Settings
