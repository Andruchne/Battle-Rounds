#pragma once

#include "spriteObject.hpp"
#include <functional>

class AnimationSprite : public SpriteObject {

	private:
		int rows = 0;
		int columns = 0;
		int spriteWidth = 0;
		int spriteHeight = 0;
		float animationInterval = 0.5f;
		sf::IntRect currentSpritePos;
		sf::Clock clock;
		std::function<void()> animate;
		void SetAnimate(std::function<void()> animate);
		bool resetAnim = false;

	protected:
		bool finishedAnimation = false;

	public:
		AnimationSprite(std::string identifier, std::string spriteFile, int columns, int rows);
		AnimationSprite(const AnimationSprite& other);
		~AnimationSprite();

	public:
		virtual void update() override;
		void render(sf::RenderWindow& window) override;
		void SetFramesPerSecond(float fps);
		void SetSprite(std::string spriteFile, int columns, int rows);
		void AnimateLoop();
		void AnimateOnce();

		bool FinishedAnimating() const;
};

