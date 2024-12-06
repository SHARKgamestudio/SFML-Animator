#pragma once

#include "Animation.h"
#include "BlendTree.h"

#include <vector>
#include <string>

class SpriteSheet;

class Animator {
private:
	SpriteSheet* spritesheet;

	std::vector<Animation*> animations;
	int currentAnimation = 0;

	std::vector<BlendTree*> blendtrees;
	int currentBlendTree = 0;

	Animation *current, *last;

	bool blendtree; float frameAsTime;
public:
	Animator(SpriteSheet* spritesheet, std::vector<Animation*> animations = {});
	~Animator();
	
	void Update(float deltaTime);

	Animation* Find(std::string name);

	void AddAnimation(Animation* animation);
	void AddBlendTree(BlendTree* blendtree);

	void Play(std::string name);
	void PlayBlendTree(std::string name);
};