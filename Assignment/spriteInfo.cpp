#include "spriteInfo.hpp"

SpriteInfo::SpriteInfo(State state, std::string spriteFile, int columns, int rows) : 
	state(state), spriteFile(spriteFile), columns(columns), rows(rows)
{
	soundFile = "";
}

std::string SpriteInfo::GetSpriteFile() const
{
	return this->spriteFile;
}

int SpriteInfo::GetColumns() const
{
	return this->columns;
}

int SpriteInfo::GetRows() const
{
	return this->rows;
}

State SpriteInfo::GetState() const
{
	return this->state;
}

void SpriteInfo::SetSoundFile(std::string soundFile)
{
	this->soundFile = soundFile;
}

std::string SpriteInfo::GetSoundFile() const 
{
	return this->soundFile;
}