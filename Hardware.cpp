#include "Hardware.hpp"

std::string helper::intToString (int number)
{
	std::ostringstream oss;
	oss << number;
	return oss.str();
}

float helper::distance(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

bool helper::withinRectangle(sf::Vector2f object, sf::Vector2f bound1, sf::Vector2f bound2)
{
	if(object.x > bound1.x and object.y > bound1.y and object.x < bound2.x and object.y < bound2.y)
		return true;
	else
		return false;	
}

bool helper::leftMouseClicked(){
	static bool pressed = false;
	if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		pressed = false;
	else
	if(!pressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		pressed = true;
		return true;
	}
	return false;
}

bool helper::rightMouseClicked(){
	static bool pressed = false;
	if(!sf::Mouse::isButtonPressed(sf::Mouse::Right))
		pressed = false;
	else
	if(!pressed && sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		pressed = true;
		return true;
	}
	return false;
}

sf::Vector2f helper::vectorIntToFloat(sf::Vector2i var)
{
	return sf::Vector2f((float)var.x, (float)var.y);
}
