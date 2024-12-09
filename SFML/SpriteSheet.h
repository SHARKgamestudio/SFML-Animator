#pragma once

#pragma region External Dependencies

#include <SFML/Graphics.hpp>

#pragma endregion

class SpriteSheet : public sf::Drawable, public sf::Transformable {
private:
	int columns, rows;
	int hres, vres;

	sf::Texture texture;
	sf::Sprite sprite;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	int current;
	SpriteSheet(std::string path, int columns, int rows);
	
	void UpdateViewport();
};