#ifndef ISETTINGS_HPP
#define ISETTINGS_HPP

#include <variant>
#include <string>

class ISettings {
public:

  using ValueType = std::variant<std::string, int>;

  virtual ~ISettings() = default;

  virtual ValueType GetValue(const std::string& subsystem,
                             const std::string& name);

  virtual bool      SetValue(const std::string& subsystem,
                             const std::string& name,
                             const ValueType  & value);
};

#endif // ISETTINGS_HPP
