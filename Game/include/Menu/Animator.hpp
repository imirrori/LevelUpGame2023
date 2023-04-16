//
// Created by Dmitry Morozov on 16/4/23.
//

#ifndef MARIO_GAME_SRC_MENU_ANIMATOR_HPP_
#define MARIO_GAME_SRC_MENU_ANIMATOR_HPP_

#include "Menu/AssetManager.hpp"

#include<iostream>
#include<list>
#include <SFML/Graphics.hpp>
#include<vector>

class Animator {

 public:

  struct Animation {
	std::string m_Name;
	std::string m_TextureName;
	std::vector<sf::IntRect> m_Frames;
	sf::Time m_Duration;
	bool m_Looping;

	Animation(std::string const &name, std::string const &textureName,
			  sf::Time const &duration, bool looping) : m_Name(name), m_TextureName(textureName),
														m_Duration(duration), m_Looping(looping) {}

	void AddFrames(sf::Vector2i const &startFrom,
				   sf::Vector2i const &frameSize, unsigned int frames, unsigned int traccia) {
	  sf::Vector2i current = startFrom;

	  for (unsigned int t = 0; t < traccia; t++) {

		for (unsigned int i = 0; i < frames; i++) {

		  m_Frames.emplace_back(current.x, current.y, frameSize.x, frameSize.y);

		  current.x += frameSize.x;
		}
		current.y += frameSize.y;
		current.x = startFrom.x;
	  }
	}
  };

  Animator(sf::Sprite &sprite);

  Animator::Animation &CreateAnimation(std::string const &name,
									   std::string const &textureName, sf::Time const &duration, bool loop = false
  );

  void Update(sf::Time const &dt);

  bool SwitchAnimation(std::string const &name);

  std::string GetCurrentAnimationName() const;

 private:

  Animator::Animation *FindAnimation(std::string const &name);

  void SwitchAnimation(Animator::Animation *animation);

  sf::Sprite &m_Sprite;
  sf::Time m_CurrentTime;
  std::list<Animator::Animation> m_Animations;
  Animator::Animation *m_CurrentAnimation;

};

#endif //MARIO_GAME_SRC_MENU_ANIMATOR_HPP_
