#pragma once
#include "Abilitie.h"

class ShieldAbility : public Ability
{
public:

	ShieldAbility(GameFramework& GameFrameWorkRef, float x, float y);
	~ShieldAbility() {}

	void Activate() override;
};

