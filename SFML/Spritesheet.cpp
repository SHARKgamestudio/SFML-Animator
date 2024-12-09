#include "Spritesheet.h"

#pragma region External Dependencies

#include <string>

#pragma endregion

SpriteSheet::SpriteSheet(std::string path, int columns, int rows) {
	this->current = 0;
	this->columns = columns; this->rows = rows;

	this->texture.loadFromFile(path.c_str());
	this->sprite.setTexture(this->texture);

	this->hres = this->texture.getSize().x / this->columns;
	this->vres = this->texture.getSize().y / this->rows;

	this->sprite.setTextureRect(sf::IntRect(0, 0, this->hres, this->vres));
	this->sprite.setOrigin(hres / 2.0f, vres / 2.0f);
}

void SpriteSheet::UpdateViewport() {
	int x = current % columns;
	int y = current / columns;

	this->sprite.setTextureRect(sf::IntRect(x * hres, y * vres, hres, vres));
}

void SpriteSheet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform.combine(this->getTransform());
	target.draw(this->sprite, states);
}