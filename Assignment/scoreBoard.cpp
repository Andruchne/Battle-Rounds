#include "scoreBoard.hpp"

ScoreBoard::ScoreBoard()
{
	SortScores();
}

ScoreBoard::~ScoreBoard() 
{
}

void ScoreBoard::SortScores() 
{
	std::ifstream readFile("highscores.cmgt");

	if (readFile.is_open())
	{
		// Read through all the lines and save them in the vector...
		std::vector<std::string> lines;

		std::string line;

		std::regex scoreRegex("([^:]+): (\\d+)");

		while (std::getline(readFile, line)) {
			std::smatch match;
			if (std::regex_search(line, match, scoreRegex)) {
				// If both capturing groups of scoreRegex match...
				if (match.size() > 2) {
					lines.push_back(match[0].str());
				}
			}
		}

		// Check size of vector to show atleast five scores...
		while (lines.size() < 5) {
			lines.push_back("Player: 0\n");
		}

		// Sort the scores...
		std::sort(lines.begin(), lines.end(), [](const std::string& a, const std::string& b) {

			size_t aScorePos = a.find(':');
			size_t bScorePos = b.find(':');

			int aScore = std::stoi(a.substr(aScorePos + 2));
			int bScore = std::stoi(b.substr(bScorePos + 2));

			return aScore > bScore;
		});

		// Remove leftover scores...
		if (lines.size() > 5) {
			for (int i = lines.size() - 1; i > 4; i--)
			{
				lines.erase(lines.begin() + i);
			}
		}

		// Add the scores to the score string...
		scores = "";
		for (int i = 0; i < lines.size(); i++)
		{
			if (i != lines.size() - 1) scores += lines[i] + "\n";
			else scores += lines[i];
		}

		WriteScores();

		readFile.close();
	}
	else 
	{
		CreateEmptyScores();
	}
}

void ScoreBoard::WriteScores()
{
	std::ofstream writeFile("highscores.cmgt", std::ofstream::out);

	if (writeFile.is_open()) {
		writeFile << scores << std::endl;
		writeFile.close();
	}
	else printf("Scoreboard Error: Unable to write onto file...");
}

void ScoreBoard::CreateEmptyScores()
{
	std::ofstream writeFile("highscores.cmgt", std::ofstream::out);

	if (writeFile.is_open()) {
		std::string emptyScores = "";

		for (int i = 0; i < 5; i++)
		{
			if(i != 4) emptyScores += "Player: 0\n";
			else emptyScores += "Player: 0";
		}

		scores = emptyScores;
		writeFile << scores << std::endl;
		writeFile.close();
	}
	else printf("Scoreboard Error: Unable to write onto file...");
}

bool ScoreBoard::CompareScore(const std::string& a, const std::string& b) 
{
	size_t aScorePos = a.find(':');
	size_t bScorePos = b.find(':');

	int aScore = std::stoi(a.substr(aScorePos + 2));
	int bScore = std::stoi(b.substr(aScorePos + 2));

	return aScore > bScore;
}

void ScoreBoard::AddScore(std::string score) 
{
	std::ofstream writeFile("highscores.cmgt", std::ios::app);

	if (writeFile.is_open()) {
		writeFile << score << std::endl;
		writeFile.close();
	}
	else printf("Scoreboard Error: Unable to write onto file...");

	SortScores();
}

std::string ScoreBoard::GetScores() 
{
	return scores;
}