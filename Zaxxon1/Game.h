#pragma once
#include "Joueur.h"
#include "Enemie.h"



class Game
{

private:
	RenderWindow* window;

	std::vector<Joueur> joueurs;
	std::vector<Enemie> enemies;


	Texture joueurTexture;
	Texture textureBalles;
	


	//Texture
	std::vector<Texture> texture;


public:
	Game(RenderWindow* window);
	~Game();

	//Accessors
	inline RenderWindow& getWindow() { return *this->window; }
	
	//Setters

	//FUNCTIONS
	void Update();
	void Draw();
	void CombatUpdate();

};

