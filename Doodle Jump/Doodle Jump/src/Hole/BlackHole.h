#pragma once

#include "Hole.h"

class BlackHole : public Hole
{

public:

	BlackHole(float x, float y);
	
	void Update(float DeltaTime, Player* MyPlayer) override;

private:
	
	float PlayerWidth = 0.f;
	float PlayerHeight = 0.f;

	float PlayerResizeSpeed = 1.5;

};

