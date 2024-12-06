#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

struct Animation;

struct Slot {
	std::string animation;
	sf::Vector2i position;

	Slot(std::string animation, sf::Vector2i position);
	Slot(std::string animation, int x, int y);
};

class BlendTree {
private:
	std::string name;
	sf::Vector2f cursor;
	std::vector<Slot*> slots;

	std::string GetCurrent();
public:
	BlendTree(std::string name, std::vector<Slot*> slots = {});
	void AddSlot(std::string animation, sf::Vector2i position);
	
	void SetHorizontal(float value); void SetVertical(float value);
	void SetCursor(sf::Vector2f cursor);

	friend class Animator;
};