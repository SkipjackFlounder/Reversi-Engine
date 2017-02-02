#include "Game.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SW, SH), "Othello");
    sf::View view(sf::FloatRect(0, 0, SW, SH));
    window.setView(view);
	
	sf::Sprite menu;
	sf::Texture menuTex;
	menuTex.loadFromFile("Resources/Menu.png");
	menu.setTexture(menuTex);
	int mode = 0;
	
	while(window.isOpen()) //Go to the main menu
	{
		sf::Event event;
        while (window.pollEvent(event))
        {
		    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
			
        window.clear();
		    window.draw(menu);
        window.display();
        
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        if(helper::leftMouseClicked())
        {
        	if(helper::withinRectangle(mousePos, sf::Vector2f(165.0, 156.0), sf::Vector2f(551.0 , 236.0)))
        	{
        		mode = 0;
        		break;
        	}else if(helper::withinRectangle(mousePos, sf::Vector2f(165.0, 247.0), sf::Vector2f(551.0 , 328.0)))
        	{
        		mode = 1;
        		break;
        	}else if(helper::withinRectangle(mousePos, sf::Vector2f(165.0, 338.0), sf::Vector2f(551.0 , 419.0)))
        	{
        		mode = 2;
        		break;
        	}
        }
	}
	
	Game game(mode);
	
    while (window.isOpen())
    {
        sf::Event event;
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
			
        window.clear();
		    game.update(&window);
		    game.handleInput(&window, &view);
		    game.displayText(&window);
        window.display();
    }

    return 0;
}
