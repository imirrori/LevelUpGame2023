#ifndef GAME_HPP
#define GAME_HPP

#include "MainMenu.hpp"
#include "Settings.hpp"
#include "Visualizer.hpp"
#include "KeyManager.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Score.hpp"
#include <Coin.hpp>

#include <memory>
#include <array>

class Game {
public:

  Game();

  void Init();
  void Run();

private:

  class IState {
public:

    enum STATES
    {
      BEGIN_SATE,
      PLAY_SATE,

      // -----
      COUNT
    };

    explicit IState(std::vector<std::shared_ptr<IEntity> >showObjects = {})
      : showObjects_(std::move(showObjects))
    {}

    virtual ~IState() = default;

    virtual IState*                                 ProcessingKey(
      KeyManager::Key key) = 0;
    virtual std::vector<std::shared_ptr<IEntity> >& GetShowObjects()
    {
      return showObjects_;
    }

private:

    std::vector<std::shared_ptr<IEntity> >showObjects_;
  };

  class BeginState
    : public IState {
public:

    explicit BeginState(std::shared_ptr<MainMenu>             menu,
                        std::vector<std::shared_ptr<IEntity> >showObjects = {})
      : IState(std::move(showObjects))
      , menu_(std::move(menu))
    {}

    IState* ProcessingKey(KeyManager::Key key) override
    {
      switch (key.key) {
        case 264: // DOWN
          menu_->PressKey(MainMenu::DOWN);
          break;
        case 265: // UP
          menu_->PressKey(MainMenu::UP);
          break;
        case 257: // ENTER

          if (menu_->PressKey(MainMenu::ENTER))
          {
            return states_[IState::PLAY_SATE].get();
          }

          break;
        case 256: // ESC
          exit(0);
          break;
      }
      return this;
    }

private:

    std::shared_ptr<MainMenu>menu_;
  };

  class PlayState
    : public IState {
public:

    explicit PlayState(std::shared_ptr<Player>               player,
                       std::vector<std::shared_ptr<IEntity> >showObjects = {})
      : IState(std::move(showObjects))
      , player_(std::move(player))
    {}

    IState* ProcessingKey(KeyManager::Key key) override
    {
      switch (key.key) {
        case 264: // DOWN
          player_->PressPlayerKey(Player::DOWN);
          break;
        case 265: // UP
          player_->PressPlayerKey(Player::UP);
          break;
        case 262: // RIGHT
          player_->PressPlayerKey(Player::RIGHT);
          break;
        case 263: // LEFT
          player_->PressPlayerKey(Player::LEFT);
          break;
        case 256: // ESC
          return states_[STATES::BEGIN_SATE].get();
      }
      return this;
    }

private:

    std::shared_ptr<Player>player_;
  };

  static std::array<std::unique_ptr<IState>, IState::STATES::COUNT>states_;

  IState *state_;
  std::shared_ptr<Settings::Settings>setting_;
  std::shared_ptr<KeyManager>keyManager_;
  std::shared_ptr<Visual::Visualizer>viz_;
  std::shared_ptr<MainMenu>menu_;
  std::shared_ptr<Player>player_;
  std::shared_ptr<Coin>coins_;
  std::shared_ptr<Map>map_;
  std::shared_ptr<Score>score_;
};

#endif // GAME_HPP
