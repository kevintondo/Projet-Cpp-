#pragma once
#include "Balles.h"

class Enemie
{

private:
	Texture* texture;
	Sprite sprite;

	int type;
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;


public:
	Enemie(Texture *texture, Vector2u windowBounds,
		Vector2f position, Vector2f direction,
		Vector2f scale, int type,
		int hpMax, int damageMax, int damageMin);
	virtual ~Enemie();

	//Accessors
	inline const int getDamage() const { return rand() % this->damageMax + this->damageMin; }
	inline const int getHP() const { return this->hp; }
	inline const int getHPMax() const { return this->hpMax; }
	inline const int estMort() const { return this->hp <= 0; }
	inline FloatRect getGlobalBounds()const { return this->sprite.getGlobalBounds(); }
	inline Vector2f getPosition()const { return this->sprite.getPosition(); }

	//Fonctions

	void takeDamage(int damage);
	void Update();
	void Draw(RenderTarget &target);

};

