#include "Game.h"
#include<time.h>
#include<iostream>

void play_game(int &score);
void get_name(std::string &name);
void add_scores(std::string &name, int &scores);
void view_scores();
void clear_scores();
void empty_scores();

int main()
{
	srand(static_cast<unsigned>(time(0)));
	std::string name;
	std::string input;
	int score;
	std::cout << "Welcom!" << std::endl;
	while (input[0] != '4')
	{
		std::cout << "Press 1 to play" << std::endl;
		std::cout << "Press 2 to view scores" << std::endl;
		std::cout << "Press 3 to clear scores" << std::endl;
		std::cout << "Press 4 to exit" << std::endl;
		std::cout << "Please make a selection: ";
		std::cin >> input;
		std::cout << std::endl;
		if (input[0] == '1')
		{
			get_name(name);
			play_game(score);
			add_scores(name, score);
		}
		else if (input[0] == '2')
		{
			view_scores();
		}
		else if (input[0] == '3')
		{
			clear_scores();
		}
		else if (input[0] == '4')
		{
			break;
		}
		else
		{
			std::cout << "[Error] " << input << " Was An Invalid Entry\n" << std::endl;
		}
	}

	std::cout << "Goodbye!" << std::endl;

	return 0;
}

void play_game(int &score)
{
	std::cout << "GOOD LUCK " << std::endl;
	Game game;
	score = game.run();
	std::cout << std::endl;
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
		fio.close();
	}
	std::cout << std::endl;
}

void clear_scores()
{
	std::string varify;
	std::cout << "Are you sure you want to clear the scores? Action cannot be undon! (y/n): ";
	std::cin >> varify;
	if (varify[0] == 'Y' || varify[0] == 'y')
	{
		empty_scores();
		std::cout << "Scores Cleared\n" << std::endl;
	}

}

void empty_scores()
{
	std::ofstream f; 
	f.open("scores.txt", std::ofstream::out | std::ofstream::trunc);
	f << "";
	f.close();
}