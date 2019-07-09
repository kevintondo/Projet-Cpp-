#pragma once
#include "Balles.h"



class Joueur
{

private:
	unsigned nbrJoueur;

	Vector2f joueurCentre;

	int shootTimer;
	int shootTimerMax;

	int damageTimer;
	int damageTimerMax;


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
	

	//Fonctions
	void Combat();
	void Mouvement();
	void Update(Vector2u windowBounds);
	void Draw(RenderTarget& target);

	static unsigned joueurs;

};

