//
// Created by Dmitry Morozov on 16/4/23.
//

#include "Menu/MainMenu.hpp"

MainMenu::MainMenu() {

  width_ = static_cast<float>(VideoMode::getDesktopMode().width);
  height_ = static_cast<float>(VideoMode::getDesktopMode().height);

  Init();

}

int MainMenu::Init() {

  window_.create(VideoMode(2000, 1600), L"On create()", Style::Default);
  window_.setMouseCursorVisible(false);

  textLand_.loadFromFile("Resources/image/z1.png");

  homeCls_ = std::make_unique<RectangleShape>(Vector2f(640, 280));

  if (homeCls_==nullptr) {
	throw std::runtime_error("Error: can't allocate memory for homeCls_");
  }

  homeCls_->setTexture(&textLand_);

  homeCls_->setPosition(Vector2f(width_/2 - homeCls_->getLocalBounds().width/2,
								 height_/2 - homeCls_->getLocalBounds().height/2));

  window_.draw(*homeCls_);
  window_.display();

  if (!buffer.loadFromFile("Resources/audio/audiomenu2.wav")) return 22;
  if (!buf_return.loadFromFile("Resources/audio/audiomenu5.wav")) return 22;

  sound.setBuffer(buffer);
  sound_return.setBuffer(buf_return);

  if (!music.openFromFile("audio/horror.ogg")) return 25;

  music.setLoop(true);
  music.setVolume(50);
  music.play();

  if (!musicFire.openFromFile("Resources/audio/faer.ogg")) return 28;

  musicFire.setLoop(true);
  musicFire.setVolume(50);
  musicFire.play();

  mainMenu_ = std::make_unique<game::GameMenu>(window_, 950, 350, 100, 120, menuItems);

  mainMenu_->setColorTextMenu(Color(237, 147, 0), Color::Red, Color::Black);
  mainMenu_->AlignMenu(2);

  if (!textureBack.loadFromFile("Resources/image/t.jpg")) return 51;

  Sprite backgroundBlack;

  backgroundBlack.setColor(sf::Color(255, 255, 255, 255));
  backgroundBlack.setTexture(textureBack);
  backgroundBlack.setTextureRect(IntRect(0, 0, static_cast<int>(width_), static_cast<int>(height_)));

  float alpha = 255;

  background_ = std::make_unique<RectangleShape>(Vector2f(width_, height_));

  if (!textureWindow.loadFromFile("Resources/image/menu9.jpg")) return 4;

  background_->setTexture(&textureWindow);

  if (!font_.loadFromFile("Resources/font/troika.otf")) return 5;

  Title_.setFont(font_);

  fText_.fontSize = 150;
  fText_.menu_text_color = Color(237, 147, 0);
  fText_.bord = 3;

  InitText(Title_, 480, 50, L"InitText", fText_);

}

void MainMenu::InitText(Text &m_text, float x_pos, float y_pos, const String &str, TextFormat f_text) {

  m_text.setCharacterSize(f_text.fontSize);
  m_text.setPosition(x_pos, y_pos);
  m_text.setString(str);
  m_text.setFillColor(f_text.menu_text_color);
  m_text.setOutlineThickness(f_text.bord);
  m_text.setOutlineColor(f_text.border_color);

}

MainMenu::~MainMenu() {

  homeCls_.reset();

}
