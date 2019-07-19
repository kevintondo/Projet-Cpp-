#include "Game.h"

enum texture { vaisseau = 0, balle, enemie };

Game::Game(RenderWindow* window)
{
	this->window = window;
	//this->window->setFramerateLimit(60);
	this->dtMultiplier = 60.f;

	//initialisation font
	this->font.loadFromFile("Font/Dosis-Light.otf");

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
	this->joueursEnVie = this->joueurs.size();

	//initialisation enemies
	Enemie e1(&this->texture[enemie], this->window->getSize(),
		Vector2f(0.f, 0.f),
		Vector2f(-1.f, 0.f), Vector2f(0.1f, 0.1f),
		0, rand() % 3 + 1, 1, 1);

	

	this->enemieDureeMax = 0;

	this->enemiesSauvegarder.push_back(Enemie(e1));

	this->enemieDureeMax = 20;
	this->enemieDuree = this->enemieDureeMax;

	this->initUI();

}


Game::~Game()
{


}

void Game::initUI()
{
	
	Text tempText;
	for (size_t i = 0; i < this->joueurs.size(); i++)
	{
		//Follow joueur Text
		//Text tempText;
		tempText.setFont(font);
		tempText.setCharacterSize(14);
		//tempText.setColor(Color::White);
		tempText.setString(std::to_string(i));

		this->followJoueurTexts.push_back(Text(tempText));

		//static joueur Text
		
		tempText.setFont(font);
		tempText.setCharacterSize(14);
		//tempText.setColor(Color::White);
		tempText.setString("");

		this->staticJoueurTexts.push_back(Text(tempText));
	}

	this->enemieText.setFont(this->font);
	this->enemieText.setCharacterSize(14);
	this->enemieText.setFillColor(Color::White);

	this->partieTermineText.setFont(this->font);
	//this->partieTermineText.setFillColor(Color::Red);
	this->partieTermineText.setCharacterSize(60);
	this->partieTermineText.setString("GAME OVER!");
	this->partieTermineText.setPosition(this->window->getSize().x/2 - 100.f, this->window->getSize().y / 2);
}


void Game::UpdateUI()
{

	for (size_t i = 0; i < this->followJoueurTexts.size(); i++)
	{
		this->followJoueurTexts[i].setPosition(this->joueurs[i].getPosition().x, this->joueurs[i].getPosition().y-15.f);
		this->followJoueurTexts[i].setString(this->joueurs[i].getHpAsString());
	}

	for (size_t i = 0; i < this->staticJoueurTexts.size(); i++)
	{
		// this->followJoueurTexts[i].setPosition(this->joueurs[i].get)
		// this->followJoueurTexts[i].setString(std::to_string(this->))
	}

}
void Game::Update(const float &dt)
{
	if (this->joueursEnVie > 0)
	{

		//Update Duree
		if (this->enemieDuree < this->enemieDureeMax)
		{
			this->enemieDuree += 1.f * dt * this->dtMultiplier;
		}

		// enemies generer
		 if (this->enemieDuree >= this->enemieDureeMax)
		{
			this->enemies.push_back(Enemie(
				&this->texture[enemie], this->window->getSize(),
				Vector2f(0.f, 0.f),
				Vector2f(-1.f, 0.f), Vector2f(0.1f, 0.1f),
				0, rand() % 3 + 1, 1, 1));

			this->enemieDuree = 0;
		} 


		for (size_t i = 0; i < this->joueurs.size(); i++)
		{

			if (this->joueurs[i].enVie())
			{

				//Joueur Updt
				this->joueurs[i].Update(this->window->getSize(), dt);



				for (size_t k = 0; k < this->joueurs[i].getBalles().size(); k++)
				{
					this->joueurs[i].getBalles()[k].Update(dt);

					//Enemie collision
					for (size_t j = 0; j < this->enemies.size(); j++)
					{

						if (this->joueurs[i].getBalles()[k].getGlobalBounds().intersects(this->enemies[j].getGlobalBounds()))
						{
							this->joueurs[i].getBalles().erase(this->joueurs[i].getBalles().begin() + k);

							if (this->enemies[j].getHP() > 0)
							{
								this->enemies[j].takeDamage(this->joueurs[i].getDamage());
							}
							if (this->enemies[j].getHP() <= 0) {
								this->enemies.erase(this->enemies.begin() + j);
							}


							return;
						}

					}

					//Fenetre de jeu Limite
					if (this->joueurs[i].getBalles()[k].getPosition().x > this->window->getSize().x)
					{
						this->joueurs[i].getBalles().erase(this->joueurs[i].getBalles().begin() + k);
						return;
					}
				}

			}
		}

		for (size_t i = 0; i < this->enemies.size(); i++)
		{
			this->enemies[i].Update(dt);

			for (size_t k = 0; k < this->joueurs.size(); k++)
			{
				if (this->joueurs[k].enVie())
				{
					if (this->joueurs[k].getGlobalBounds().intersects(this->enemies[i].getGlobalBounds()))
					{
						this->joueurs[k].takeDamage(this->enemies[i].getDamage());

						if (!this->joueurs[k].enVie())
						{
							this->joueursEnVie--;
							
						}

						this->enemies.erase(this->enemies.begin() + i);
						return;

					}
				}

				
			}

				if (this->enemies[i].getPosition().x < 0 - this->enemies[i].getGlobalBounds().width)
				{
					this->enemies.erase(this->enemies.begin() + i);
					return;
				}
		}
		this->UpdateUI();
	}

	
	
}

void Game::DrawUI()
{
	for (size_t i = 0; i < this->followJoueurTexts.size(); i++)
	{
	
		this->window->draw(this->followJoueurTexts[i]);
	}

	for (size_t i = 0; i < this->staticJoueurTexts.size(); i++)
	{
		this->window->draw(this->staticJoueurTexts[i]);
	}

	if (this->joueursEnVie <= 0)
	{
		this->window->draw(this->partieTermineText);
	}
}

void Game::Draw()
{
	this->window->clear();
	
	for (size_t i = 0; i < this->joueurs.size(); i++)
	{
		if (this->joueurs[i].enVie())
		{
			this->joueurs[i].Draw(*this->window);
		}
		
	}

	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		this->enemieText.setPosition(this->enemies[i].getPosition());
		this->enemieText.setString(
			std::to_string(this->enemies[i].getHP()) + 
				"/" + 
			std::to_string(this->enemies[i].getHPMax()));

		this->enemies[i].Draw(*this->window);
		this->window->draw(this->enemieText);
		
	}

	this->DrawUI();
	this->window->display();
} 