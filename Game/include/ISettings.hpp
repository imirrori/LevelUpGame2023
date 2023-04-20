#ifndef ISETTINGS_HPP
#define ISETTINGS_HPP

#include <variant>
#include <string>

namespace Settings {
class ISettings {
public:

  using ValueType = std::variant<std::string, int>;

  virtual ~ISettings() = default;

  virtual ValueType GetValue(const std::string& subsystem,
                             const std::string& name) = 0;

  virtual bool      SetValue(const std::string& subsystem,
                             const std::string& name,
                             const ValueType  & value) = 0;
};
} // namespace Settings

#endif // ISETTINGS_HPP
