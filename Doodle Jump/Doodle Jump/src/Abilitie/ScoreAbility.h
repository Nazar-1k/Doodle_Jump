#pragma once
#include "Abilitie.h"

class ScoreAbility : public Ability
{
public:

	ScoreAbility(GameFramework& gameFrameWork, float x, float y);
	~ScoreAbility() {}

	void Activate() override;

private:

	int CountScoreAdd = 500;

};

