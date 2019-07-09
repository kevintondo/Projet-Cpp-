#include "Joueur.h"

unsigned Joueur::joueurs = 0;

enum controls {HAUT = 0, BAS =1, GAUCHE=2, DROITE =3, TIRER=4};

Joueur::Joueur(std::vector<Texture>& textures,
	int HAUT, int BAS, 
	int GAUCHE, int DROITE,
	int TIRER)
	:level(1), exp(0), expNext(100),
	hp(10), hpMax(10),
	damage(1), damageMax(2),
	score(0)
{
	

	this->sprite.setTexture(textures[0]);
	this->sprite.setScale(0.12f, 0.12f);

	this->textureBalles = &textures[1];

	this->shootTimerMax = 25;
	this->shootTimer = this->shootTimerMax;

	this->damageTimerMax = 10;
	this->damageTimer = this->damageTimerMax;

	this->controls[controls::HAUT] = HAUT;
	this->controls[controls::BAS] = BAS;
	this->controls[controls::GAUCHE] = GAUCHE;
	this->controls[controls::DROITE] = DROITE;
	this->controls[controls::TIRER] = TIRER;

	this->nbrJoueur = Joueur::joueurs;
	Joueur::joueurs++;

	std::cout << this->nbrJoueur << "\n";


	
}


Joueur::~Joueur()
{

}

void Joueur::Mouvement()
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::HAUT])))
		this->sprite.move(0.f, -5.f);
	
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::BAS])))
		this->sprite.move(0.f, 5.f);
	
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::DROITE])))
		this->sprite.move(5.f, 0.f);
	
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::GAUCHE])))
		this->sprite.move(-5.f, 0.f);
	
	
}

void Joueur::Combat()
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::TIRER])) && this->shootTimer >= this->shootTimerMax)
	{
		this->balles.push_back(Balles(textureBalles, this->joueurCentre));

		this->shootTimer = 0; //Reset Temps pour tirer
	}
}

void Joueur::Update(Vector2u windowBounds)
{
	//Update timers
	if (this->shootTimer < this->shootTimerMax)
	{
		this->shootTimer++;
	}

	if (this->damageTimer < this->damageTimerMax)
	{
		this->damageTimer++;
	}

	//Update position
	this->joueurCentre.x = this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2;
	this->joueurCentre.y = this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2;

	this->Mouvement();
	this->Combat();


}
void Joueur::Draw(RenderTarget& target)
{
	target.draw(this->sprite);

	for (size_t i = 0; i < this->balles.size(); i++)
	{
		this->balles[i].Draw(target);
	}
}
