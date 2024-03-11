#pragma once
#include <vector>
class GameSprite;

class Text
{
public:

	~Text();
	bool InitText(float NewX, float NewY);
	void UpdateText(int Score);
	void DestroyText();

private:
	float StartX = 0;
	float StartY = 0;

	int Spacing = 5;
	std::vector<GameSprite*> Numbers;
};

