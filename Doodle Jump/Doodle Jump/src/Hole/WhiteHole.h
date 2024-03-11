#pragma once

#include "Hole.h"

class WhiteHole : public Hole
{
public:
	
	WhiteHole(float x, float y);
	void Update(float DeltaTime, Player* MyPlayer) override ;
	
};

