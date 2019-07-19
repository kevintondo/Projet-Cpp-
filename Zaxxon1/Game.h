#pragma once
#include "Joueur.h"
#include "Enemie.h"



class Game
{

private:
	RenderWindow* window;
	float dtMultiplier;

	//Text
	Font font;
	std::vector<Text> followJoueurTexts;
	std::vector<Text> staticJoueurTexts;
	Text enemieText;
	Text partieTermineText;



	std::vector<Joueur> joueurs;
	int joueursEnVie;

	//Enenmies
	std::vector<Enemie> enemies;
	std::vector<Enemie> enemiesSauvegarder;
	float enemieDuree;
	float enemieDureeMax;


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
	void Update(const float& dt);
	void UpdateUI();
	void Draw();

	void initUI();
	void DrawUI();

};

