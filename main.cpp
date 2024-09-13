#include "Game.h"
#include<time.h>
#include<iostream>

void get_name(std::string &name);
void add_scores(std::string &name, int &scores);
void view_scores();

int main()
{
	srand(static_cast<unsigned>(time(0)));
	std::string name;
	int score;
	char input[2];
	

	std::cout << "Welcom!" << std::endl;
	std::cout << "Press 1 to play" << std::endl;
	std::cout << "Press 2 to view scores" << std::endl;
	std::cout << "Press 3 to exit" << std::endl;

	std::cin.getline(input, 2);

	if (input[0] == '1')
	{
		get_name(name);
		std::cout << "GOOD LUCK " << name << std::endl;
		Game game;
		score = game.run();
		add_scores(name, score);
	}
	else if (input[0] == '2')
	{
		view_scores();
	}

	std::cout << "Thank You!" << std::endl;

	return 0;
}

void get_name(std::string& name)
{
	std::cout << "Please enter your name" << std::endl;
	std::cin >> name;
}

void add_scores(std::string& name, int& score)
{
	std::string s_score;
	s_score = std::to_string(score);
	std::ofstream fio("scores.txt", std::ios::app);
	if (fio.is_open())
	{
		fio << name << " " << s_score << std::endl;
		fio.close();
	}
	else
	{
		std::cerr << "[ERROR] file could not be opened" << std::endl;
	}
}

void view_scores()
{
	std::string line;
	std::ifstream fio("scores.txt");
	if (fio.is_open())
	{
		std::cout << "SCORES" << std::endl;
		while (getline(fio, line))
		{
			std::cout << line << std::endl;
		}
	}
}