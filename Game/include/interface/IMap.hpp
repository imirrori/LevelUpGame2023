//
// Created by Dmitry Morozov on 8/4/23.
//

#ifndef MARIO_GAME_INCLUDE_INTERFACE_IMAP_HPP_
#define MARIO_GAME_INCLUDE_INTERFACE_IMAP_HPP_

#include <string>

class IMap {
 public:
  IMap() = default;
  explicit IMap(const std::string &file_name) {};

  virtual ~IMap() = default;

  [[nodiscard]] virtual std::size_t width() const = 0;
  [[nodiscard]] virtual std::size_t height() const = 0;
  [[nodiscard]] virtual const std::string &GetMap() const = 0;

  virtual void PrintMap(const std::string &map) = 0; // This is interface requested by Valeria

};

#endif //MARIO_GAME_INCLUDE_INTERFACE_IMAP_HPP_
