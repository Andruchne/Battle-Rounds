#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <regex>

class ScoreBoard
{
	private:
		// Holds all the scores in a single string...
		std::string scores;

		bool CompareScore(const std::string& a, const std::string& b);
		void SortScores();
		void WriteScores();

	public:
		ScoreBoard();
		~ScoreBoard();

		void AddScore(std::string score);
		void CreateEmptyScores();
		std::string GetScores();
};

