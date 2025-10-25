#pragma once

#include <string>

enum State { Idle, Attack, Hit, Death };

struct SpriteInfo
{
	private:
		std::string spriteFile;
		int columns;
		int rows;
		State state;
		std::string soundFile;

	public:
		SpriteInfo(State state, std::string spriteFile, int columns, int rows);
		std::string GetSpriteFile() const;
		int GetRows() const;
		int GetColumns() const;
		State GetState() const;
		void SetSoundFile(std::string spriteFile);
		std::string GetSoundFile() const;
};

