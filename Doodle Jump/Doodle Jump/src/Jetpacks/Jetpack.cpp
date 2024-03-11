#include "Jetpack.h"

#include "../Framework/GameFarmework.h"

#include "../Sprites/GameSprite.h"

#include "../Timer/Timer.h"


// Path
static const char pathJetpackFrame1[] = "data/Jetpacks/Bunny/jetpack-bunny_Frame4.png";
static const char pathJetpackFrame2[] = "data/Jetpacks/Bunny/jetpack-bunny_Frame5.png";
static const char pathJetpackFrame3[] = "data/Jetpacks/Bunny/jetpack-bunny_Frame6.png";

Jetpack::Jetpack(GameFramework& GameFrameworkRef)
: MyGameFramework{ GameFrameworkRef }
{

	if (JetpackFrame1 = new GameSprite())
	{
		JetpackFrame1->CreateSprite(pathJetpackFrame1);
	}
	if (JetpackFrame2 = new GameSprite())
	{
		JetpackFrame2->CreateSprite(pathJetpackFrame2);
	}
	if (JetpackFrame3 = new GameSprite())
	{
		JetpackFrame3->CreateSprite(pathJetpackFrame3);
	}

	ActiveJetpack();

}

Jetpack::~Jetpack()
{
	DestroySpriteJetpack();

	if (JetpackTimer)
	{
		delete JetpackTimer;
	}
}

void Jetpack::UpdateJetpack(float newX, float newY, float DeltaTime, bool& bActive)
{
	newX -= LeftJetpackOffset;
	newY += LeftJetpackOffset;

	JetpackFrame1->SetPosition(newX, newY);
	JetpackFrame2->SetPosition(newX, newY);
	JetpackFrame3->SetPosition(newX, newY);


	if(countFrame >= 5 && countFrame >= 0)
	{
		JetpackFrame1->DrawSprite(MyGameFramework.GetScreenWitdth());
	}
	else if (countFrame >= 5 && countFrame <= 10)
	{
		JetpackFrame2->DrawSprite(MyGameFramework.GetScreenWitdth());
	}
	else
	{
		JetpackFrame3->DrawSprite(MyGameFramework.GetScreenWitdth());
	}
		
	countFrame++;
	if (countFrame > 15)
	{
		countFrame = 0;
	}

	if (JetpackTimer->isStarted() && JetpackTimer->GetTime() >= CountJetpackTime)
	{
		JetpackTimer->Pause();

		bActive = isActive = false;
	}

}

void Jetpack::DestroySpriteJetpack()
{
	JetpackFrame1->DestroySprite();
	JetpackFrame2->DestroySprite();
	JetpackFrame3->DestroySprite();
}

void Jetpack::ActiveJetpack()
{
	if (!JetpackTimer)
	{
		JetpackTimer = new Timer();
	}
	
	JetpackTimer->Start();

	isActive = true;
}
