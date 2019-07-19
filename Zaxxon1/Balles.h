#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <cstdlib>
#include <vector>



using namespace sf;

class Balles
{
private:
	float dtMultiplier;

	Texture *texture;
	Sprite sprite;

	Vector2f maxVitesse;

public:
	Balles(Texture *texture, Vector2f position, Vector2f maxVitesse = Vector2f(15.f, 0.f));
	virtual ~Balles();

	//Accesseurs
	inline FloatRect getGlobalBounds()const {return this->sprite.getGlobalBounds(); }
	inline Vector2f getPosition()const { return this->sprite.getPosition(); }
	//Fonstions
	void Movement(const float &dt);

	void Update(const float &dt);
	void Draw(RenderTarget& target);
};

