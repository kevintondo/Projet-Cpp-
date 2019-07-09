#include "Game.h"

enum texture { vaisseau = 0, balle, enemie };

Game::Game(RenderWindow* window)
{
	this->window = window;
	this->window->setFramerateLimit(60);

	//initialisation texture
	//this->textureBalles
	//this->joueurTexture.loadFromFile("Textures/vaisseau.png");
	//this->textureBalles.loadFromFile("Textures/balle.png");

	//this->textureBalles.loadFromFile("Textures/enemie.png");
	
	this->texture.push_back(Texture());
	this->texture[vaisseau].loadFromFile("Textures/vaisseau.png");
	this->texture.push_back(Texture());
	this->texture[balle].loadFromFile("Textures/balle.png");
	this->texture.push_back(Texture());
	this->texture[enemie].loadFromFile("Textures/enemie.png");
	



	//initialisation joueur
	this->joueurs.push_back(Joueur(this->texture));

	this->enemies.push_back(Enemie(
		&this->texture[enemie], this->window->getSize(),
		Vector2f(0.f, 0.f),
		Vector2f(-1.f,0.f), Vector2f(0.1f,0.1f),
		0, rand() % 3 +1, 3, 1));



}


Game::~Game()
{


}

void Game::CombatUpdate()
{
	//Limite fenetre
	
	

}

void Game::Update()
{
	for (size_t i = 0; i < this->joueurs.size(); i++)
	{
		bool enemieEffacer = false;
		bool balleEffacer = false;

		//Joueur Updt
		this->joueurs[i].Update(this->window->getSize());

		
		for (size_t k = 0; k < this->joueurs[i].getBalles().size() && !balleEffacer; k++)
		{ 
			this->joueurs[i].getBalles()[k].Update();

			//Enemie collision
			for (size_t j = 0; j < this->enemies.size() && !enemieEffacer; j++)
			{
				this->enemies[i].Update();

				if (this->joueurs[i].getBalles()[k].getGlobalBounds().intersects(this->enemies[j].getGlobalBounds()))
				{
					this->joueurs[i].getBalles().erase(this->joueurs[i].getBalles().begin() + k);
					this->enemies.erase(this->enemies.begin() + j);
					enemieEffacer = true;
					balleEffacer = true;
				}
				else if (this->enemies[i].getPosition().x < 0 - this->enemies[i].getGlobalBounds().width)
				{
					this->enemies.erase(this->enemies.begin() + i);
					enemieEffacer = true;
				}
			}

			//Fenetre de jeu Limite
			if (!balleEffacer && this->joueurs[i].getBalles()[k].getPosition().x > this->window->getSize().x)
			{
				this->joueurs[i].getBalles().erase(this->joueurs[i].getBalles().begin() + k);
				balleEffacer = true;
			}
		}
		
	}
	
}

void Game::Draw()
{
	this->window->clear();
	
	for (size_t i = 0; i < this->joueurs.size(); i++)
	{
		joueurs[i].Draw(*this->window);
	}

	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		enemies[i].Draw(*this->window);
	}

	this->window->display();
} 