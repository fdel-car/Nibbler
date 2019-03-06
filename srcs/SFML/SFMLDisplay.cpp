#include "SFML/SFMLDisplay.hpp"

SFMLDisplay::SFMLDisplay(int w, int h)
    : _window(sf::VideoMode(w, h), "Nibbler - SFML", sf::Style::Close) {
  std::cout << "SFML start" << std::endl;
  _window.setFramerateLimit(60);
}

SFMLDisplay::~SFMLDisplay(void) {}

bool SFMLDisplay::windowIsOpen(void) const { return _window.isOpen(); }

void SFMLDisplay::pollEvent(std::map<std::string, KeyState> &keyMap) {
  while (_window.pollEvent(_event)) {
    if (_event.type == sf::Event::Closed) _window.close();

    if (_event.type == sf::Event::KeyPressed ||
        _event.type == sf::Event::KeyReleased) {
      auto it = _keyMap.find(_event.key.code);
      if (it == _keyMap.end()) continue;
      if (_event.type == sf::Event::KeyReleased)
        keyMap[it->second].currFrame = false;
      else {
        if (it->second == "ESC") _window.close();
        keyMap[it->second].currFrame = true;
      }
    }
  }
}

void SFMLDisplay::_drawSnake(std::vector<glm::ivec2> const &snakeCoords,
                             std::vector<sf::CircleShape> *bodySnake) {
  size_t bodySize = bodySnake->size();
  for (size_t i = 0; i < snakeCoords.size() - bodySize; i++) {
    bodySnake->push_back(sf::CircleShape(15.f));
  }
  for (size_t i = 0; i < snakeCoords.size(); i++) {
    bodySnake->at(i).setPosition(snakeCoords.at(i).x, snakeCoords.at(i).y);
    _window.draw(bodySnake->at(i));
  }
}

void SFMLDisplay::_drawApple(glm::ivec2 apple) {
	_apple = sf::CircleShape(15.f);
	_apple.setPosition(apple.x, apple.y);
	_apple.setFillColor(sf::Color(255, 0, 0));
	_window.draw(_apple);
}

void SFMLDisplay::renderScene(glm::ivec2 apple,
							  std::vector<glm::ivec2> const &fstCoords,
                              std::vector<glm::ivec2> const &sndCoords) {
  _window.clear(sf::Color::Black);
  _drawSnake(fstCoords, &_fstBody);
  _drawApple(apple);
  if (sndCoords.size() != 0) _drawSnake(sndCoords, &_sndBody);
  _window.display();
}

std::map<ushort, std::string> SFMLDisplay::_initKeyMap(void) {
  std::map<ushort, std::string> keyMap;

  keyMap[sf::Keyboard::Escape] = "ESC";
  keyMap[sf::Keyboard::W] = "W";
  keyMap[sf::Keyboard::A] = "A";
  keyMap[sf::Keyboard::S] = "S";
  keyMap[sf::Keyboard::D] = "D";
  keyMap[sf::Keyboard::Num1] = "1";
  keyMap[sf::Keyboard::Num2] = "2";
  keyMap[sf::Keyboard::Num3] = "3";

  return keyMap;
}

std::map<ushort, std::string> SFMLDisplay::_keyMap = _initKeyMap();

SFMLDisplay *createDisplay(int w, int h) { return new SFMLDisplay(w, h); }

void deleteDisplay(SFMLDisplay *display) { delete display; }
