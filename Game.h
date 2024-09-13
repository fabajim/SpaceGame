#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>
#include<fstream>

#include<map>
#include<iostream>
#include"Player.h"
#include"Laser.h"
#include"Enemy.h"
#include"Stars.h"

class Game
{
private:
	sf::RenderWindow* window;

	std::map<std::string, sf::Texture*> textures; //for each string there will be a texture.
	sf::Font font;
	sf::Text gameText;

	//player
	Player* player;

	// lasers
	std::vector<Laser*> laser;

	//Enemy
	std::vector<Enemy*> enemy;

	//Stars
	std::vector<Stars*> stars;

	void initWindow();
	void initText();
	void initPlayer();
	void initVars();
	void initTextures();
	void initEnemy();
	void initStar();

	void subtractPoints();
	void updatePoints();
	void updateEnemySpeed(float speed);
	void updateEnemySpawnTime(float time);

	bool mouseHeld; // keep laser from fireing in one continous line
	float enemySpawnTimeMax;
	float enemySpawnTime;
	float enemySpeed;
	float starSpawnMax;
	float starSpawnTimer;
	int maxStars;
	int points;

public:
	Game();
	virtual ~Game();

	int run();
	//update and render the window
	void eventUpdate();
	void playerUpdate();
	void laserUpdate();
	void enemyUpdate();
	void starUpdate();
	void textUpdate();
	void update();

	void renderText(sf::RenderTarget& target);
	void render();


};

