#ifndef _HARDWARE_HPP
#define _HARDWARE_HPP
#define SW 1300
#define SH 800
#define PI 3.1415926536

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <time.h>

namespace helper
{	
	std::string intToString(int);
	float distance(sf::Vector2f, sf::Vector2f);
	bool withinRectangle(sf::Vector2f, sf::Vector2f, sf::Vector2f);
	bool leftMouseClicked();
	bool rightMouseClicked();
	sf::Vector2f vectorIntToFloat(sf::Vector2i);
}


#endif
