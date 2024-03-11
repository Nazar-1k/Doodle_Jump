#pragma once
#include "Abilitie.h"

class JetpackAbility : public Ability
{
public:

	JetpackAbility(GameFramework& GameFrameWorkRef, float x, float y);

	void Activate() override;
};

