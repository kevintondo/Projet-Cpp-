#include "Balles.h"



Balles::Balles(Texture *texture, Vector2f position,
	Vector2f maxVitesse)
{
	this->dtMultiplier = 60.f;
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->maxVitesse = maxVitesse;
	this->sprite.setScale(0.1f, 0.1f);
	this->sprite.setPosition(Vector2f(position.x - this->sprite.getGlobalBounds().width/2,
		position.y - this->sprite.getGlobalBounds().height /2));
	

}


Balles::~Balles()
{
}

void Balles::Movement(const float &dt)
{
	this->sprite.move(this->maxVitesse.x * dt * this->dtMultiplier,
		this->maxVitesse.y * dt * this->dtMultiplier);
}

void Balles::Update(const float &dt)
{
	this->Movement(dt);
}
void Balles::Draw(RenderTarget& target)
{
	target.draw(this->sprite);
}
