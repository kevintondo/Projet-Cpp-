#pragma once
#include "Balles.h"



class Joueur
{

private:
	float dtMultiplier;

	unsigned nbrJoueur;
	

	Vector2f joueurCentre;

	float shootTimer;
	float shootTimerMax;

	float damageTimer;
	float damageTimerMax;


	//Texture *texture;

	Sprite sprite;
	RectangleShape hitbox;

	//Texture* textureBalles;
	std::vector<Balles> balles;
	Texture* textureBalles;

	int controls[5];

	int level;
	int exp;
	int expNext;

	int hp;
	int hpMax;

	int damage;
	int damageMax;

	int score;

public:
	Joueur(std::vector<Texture> &textures, int HAUT = 73, int BAS = 74, int GAUCHE =71, int DROITE = 72, int TIRER = 57);
	virtual ~Joueur();

	//Accesseur
	inline std::vector<Balles>& getBalles() { return this->balles; }
	inline const Vector2f& getPosition()const { return this->sprite.getPosition(); }
	inline const String getHpAsString()const { return std::to_string(this->hp) + "/" + std::to_string(this->hpMax); }

	inline const int getDamage()const { return rand() % this->damageMax + this->damage; }
	inline FloatRect getGlobalBounds()const { return this->sprite.getGlobalBounds(); }
	inline const int& getHp()const { return this->hp; }
	inline const int& getHpMax()const { return this->hpMax; }
	inline void takeDamage(int damage) { this->hp -= damage; }
	inline bool enVie()const { return this->hp > 0; }
	inline const int& getnbrJoueur()const { return this->nbrJoueur; }

	//Fonctions
	void Combat(const float &dt);
	void Mouvement(const float &dt);
	void Update(Vector2u windowBounds, const float &dt);
	void Draw(RenderTarget& target);

	static unsigned joueurs;

};

