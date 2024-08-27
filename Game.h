#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include<map>
#include<iostream>
#include"Player.h"
#include"Laser.h"

class Game
{
private:
	sf::RenderWindow* window;

	std::map<std::string, sf::Texture*> textures; //for each string there will be a texture.

	//player
	Player* player;

	// lasers
	std::vector<Laser*> laser;

	void initWindow();
	void initPlayer();
	void initVars();
	void initTextures();

	bool mouseHeld;

public:
	Game();
	virtual ~Game();

	void run();
	//update and render the window
	void eventUpdate();
	void playerUpdate();
	void laserUpdate();
	void update();
	void render();

};

