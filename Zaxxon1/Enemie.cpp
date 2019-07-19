#include "Enemie.h"


enum eType {MOVELEFT = 0, fOLLOW, FOLLOWFAST, FOLLOWSHOOT, FOLLOWFASTSHOOT};

Enemie::Enemie(Texture *texture, Vector2u windowBounds,
	Vector2f position, Vector2f direction,
	Vector2f scale, int type,
	int hpMax, int damageMax, int damageMin)
{

	this->dtMultiplier = 40.f;
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(scale);
	this->windowBounds = windowBounds;
	this->direction = direction;

	this->sprite.setPosition(windowBounds.x , (rand()%windowBounds.y) - this->sprite.getGlobalBounds().height);

	this->type = type;
	this->hpMax = hpMax;
	this->hp = this->hpMax;

	this->damageMax = damageMax;
	this->damageMin = damageMin;

}


Enemie::~Enemie()
{
}

void Enemie::takeDamage(int damage)
{
	this->hp -= damage;

	if (this->hp <= 0)
	{
		this->hp = 0;
	}
}

void Enemie::Update(const float &dt)
{
	switch (this->type)
	{
	case 0:
		this->sprite.move(this->direction.x * 10.f * dt * this->dtMultiplier,
			this->direction.y * 10.f);
		break;

	default:
		break;

	}
}

void Enemie::Draw(RenderTarget &target)
{
	target.draw(this->sprite);
}
