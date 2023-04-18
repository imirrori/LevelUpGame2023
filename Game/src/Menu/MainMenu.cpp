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

  textLand_.loadFromFile("Resources/image/z1.png");

  homeCls_ = std::make_unique<RectangleShape>(Vector2f(640, 280));

  if (homeCls_==nullptr) {
	throw std::runtime_error("Error: can't allocate memory for homeCls_");
  }

  homeCls_->setTexture(&textLand_);

  homeCls_->setPosition(Vector2f(width_/2 - homeCls_->getLocalBounds().width/2,
								 height_/2 - homeCls_->getLocalBounds().height/2));

  if (!buffer.loadFromFile("Resources/audio/audiomenu2.wav")) return 22;
  if (!buf_return.loadFromFile("Resources/audio/audiomenu5.wav")) return 22;

  sound.setBuffer(buffer);
  sound_return.setBuffer(buf_return);

  if (!music.openFromFile("audio/horror.ogg")) return 25;

  music.setLoop(true);
  music.setVolume(50);


  if (!musicFire.openFromFile("Resources/audio/faer.ogg")) return 28;

  musicFire.setLoop(true);
  musicFire.setVolume(50);


  mainMenu_ = std::make_unique<game::GameMenu>(window_, 950, 350, 100, 120, menuItems);

  mainMenu_->setColorTextMenu(Color(237, 147, 0), Color::Red, Color::Black);
  mainMenu_->AlignMenu(2);

  if (!textureBack.loadFromFile("Resources/image/t.jpg")) return 51;

  backgroundBlack.setColor(sf::Color(255, 255, 255, 255));
  backgroundBlack.setTexture(textureBack);
  backgroundBlack.setTextureRect(IntRect(0, 0, static_cast<int>(width_), static_cast<int>(height_)));

  background_ = std::make_unique<RectangleShape>(Vector2f(width_, height_));

  if (!textureWindow.loadFromFile("Resources/image/menu9.jpg")) return 4;

  background_->setTexture(&textureWindow);

  if (!font_.loadFromFile("Resources/font/troika.otf")) return 5;

  Title_.setFont(font_);

  fText_.fontSize = 150;
  fText_.menu_text_color = Color(237, 147, 0);
  fText_.bord = 3;

  InitText(Title_, 480, 50, L"Super Mario", fText_);

  spriteSize_ = std::make_unique<Vector2i>(300, 313);

  sprite.setPosition(440, 780);

  animator = std::make_unique<Animator>(sprite);

  return 0;
}

void MainMenu::InitText(Text &m_text, float x_pos, float y_pos, const String &str, TextFormat f_text) {

  m_text.setCharacterSize(f_text.fontSize);
  m_text.setPosition(x_pos, y_pos);
  m_text.setString(str);
  m_text.setFillColor(f_text.menu_text_color);
  m_text.setOutlineThickness(f_text.bord);
  m_text.setOutlineColor(f_text.border_color);

}

void MainMenu::Run() {

  window_.create(VideoMode(2000, 1600), L"Super Mario", Style::Default);
  window_.setMouseCursorVisible(false);

  window_.draw(*homeCls_);
  window_.display();

  music.play();
  musicFire.play();

//  auto &idleAnimation = animator->CreateAnimation("Idle", "Resources/image/f.png", seconds(1), true);
//
//  idleAnimation.AddFrames(Vector2i(0, 0), *spriteSize_, 5, 4);

  Clock clock;

  while (window_.isOpen()) {

	Event event{};

	while (window_.pollEvent(event)) {

	  if (event.type==Event::KeyReleased) {

		if (event.key.code==Keyboard::Up) {

		  sound.play();
		  mainMenu_->MoveUp();

		}

		if (event.key.code==Keyboard::Down) {

		  sound.play();
		  mainMenu_->MoveDown();

		}

		if (event.key.code==Keyboard::Return) {

		  music.pause();
		  musicFire.pause();
		  sound_return.play();

		  switch (mainMenu_->getSelectedMenuNumber()) {

			case 0:GameStart();
			  break;

			case 1:Options();
			  break;

			case 2:About_Game();
			  break;

			case 3:window_.close();
			  break;

			default:break;
		  }

		  music.play();
		  musicFire.play();
		}
	  }
	}

	Time deltaTime = clock.restart();
	animator->Update(deltaTime);

	if (alpha > 0) {
	  alpha -= 0.05f;
	  backgroundBlack.setColor(Color(255, 255, 255, static_cast<unsigned char>(alpha)));
	}

	window_.clear();
	window_.draw(*background_);
	window_.draw(Title_);
	mainMenu_->draw();
	window_.draw(sprite);
	window_.draw(backgroundBlack);
	window_.display();

  }

}

MainMenu::~MainMenu() {

  window_.close();

}
