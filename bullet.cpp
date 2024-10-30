#include "bullet.h"

void bullet::bulletAnimation(float deltaTime) {
	animationTime += deltaTime;
	if (animationTime >= frameDuration) {
		animationTime = 0.f;
		currentFrame = (currentFrame + 1) % numFrames;
		sf::IntRect newFrame(currentFrame * frameWidth, 0, frameWidth, frameHeight);
		sprite.setTextureRect(newFrame);
	}
}