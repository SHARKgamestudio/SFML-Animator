#include "SFML/Graphics.hpp"
#include "SpriteSheet.h"
#include "Animation.h"
#include "BlendTree.h"
#include "Animator.h"
#include <iostream>

using namespace sf;

int main() {
	RenderWindow window(VideoMode(800, 600), "Default");
	Event event;

	SpriteSheet spritesheet("spritesheet.png", 24, 8);
	spritesheet.setPosition(400, 300);
	spritesheet.setScale(4.0f, 4.0f);

	#pragma region Animator

	Animator animator(&spritesheet, {
		new Animation("idle_forward", 0, 0, 2),
		new Animation("idle_backward", 96, 96, 2),
		new Animation("idle_right", 48, 48, 2),
		new Animation("idle_left", 144, 144, 2),

		new Animation("idle_forward_left", 168, 168, 2),
		new Animation("idle_forward_right", 24, 24, 2),
		new Animation("idle_backward_left", 120, 120, 2),
		new Animation("idle_backward_right", 72, 72, 2),

		new Animation("walk_forward", 1, 4, 2),
		new Animation("walk_backward", 97, 100, 2),
		new Animation("walk_right", 49, 52, 2),
		new Animation("walk_left", 145, 148, 2),

		new Animation("walk_forward_left", 169, 172, 2),
		new Animation("walk_forward_right", 25, 28, 2),
		new Animation("walk_backward_left", 121, 124, 2),
		new Animation("walk_backward_right", 73, 76, 2),

		new Animation("attack", 4, 8, 2),
	});

	BlendTree idle("idle", {
		new Slot("idle_forward", 0, 1),
		new Slot("idle_backward", 0, -1),
		new Slot("idle_right", 1, 0),
		new Slot("idle_left", -1, 0),

		new Slot("idle_forward_left", -1, 1),
		new Slot("idle_forward_right", 1, 1),
		new Slot("idle_backward_left", -1, -1),
		new Slot("idle_backward_right", 1, -1),
	});
	animator.AddBlendTree(&idle);

	BlendTree walk("walk", {
		new Slot("walk_forward", 0, 1),
		new Slot("walk_backward", 0, -1),
		new Slot("walk_right", 1, 0),
		new Slot("walk_left", -1, 0),

		new Slot("walk_forward_left", -1, 1),
		new Slot("walk_forward_right", 1, 1),
		new Slot("walk_backward_left", -1, -1),
		new Slot("walk_backward_right", 1, -1),
		});
	animator.AddBlendTree(&walk);

	#pragma endregion
	
	Vector2f lastDirection(0, 1);

	animator.PlayBlendTree("idle");

	bool test = true;

	float horizontal = 0, vertical = 0;

	sf::Clock clock;
	while (window.isOpen()) {

		std::cout << lastDirection.x << "," << lastDirection.y << std::endl;

		float deltaTime = clock.restart().asSeconds();
		
		if (horizontal != 0 || vertical != 0) {
			if (test) { animator.PlayBlendTree("walk"); test = false; }
			lastDirection = Vector2f(horizontal, -vertical);
		}
		else { if (!test) { animator.PlayBlendTree("idle"); test = true; } }

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();


		// TRANSFORMS //
		horizontal = sf::Keyboard::isKeyPressed(sf::Keyboard::D) ? 1.0f : (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ? -1.0f : 0.0f);
		vertical = sf::Keyboard::isKeyPressed(sf::Keyboard::Z) ? 1.0f : (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ? -1.0f : 0.0f);

		Vector2f direction(horizontal, -vertical);

		Vector2f movements = direction * 90.0f;

		spritesheet.move(movements * deltaTime);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			animator.Play("attack");
		}

		// ANIMATIONS //
		idle.SetCursor(lastDirection);
		walk.SetCursor(lastDirection);
		animator.Update(deltaTime);

		// RENDERING //

		window.draw(spritesheet);

		window.display();
	}

	return 0;
}