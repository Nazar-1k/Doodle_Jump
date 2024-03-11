#include "GameFarmework.h"

#include <iostream>
#include <random>

#include "../Background/GameBackground.h"
#include "../Sprites/Player/Player.h"

#include "../Sprites/Platform/BasePlatform.h"
#include "../Sprites/Platform/HalfCrushPlatform.h"
#include "../Sprites/Platform/CrushPlatform.h"
#include "../Sprites/Platform/MovePlatform.h"
#include "../Sprites/Platform/JumpPlatform.h"

#include "../Sprites/Platform/PlatformFactory/BasePlatformFactory.h"
#include "../Sprites/Platform/PlatformFactory/CrushPlatformFactory.h"
#include "../Sprites/Platform/PlatformFactory/HalfCrushPlatformFactory.h"
#include "../Sprites/Platform/PlatformFactory/JumpPlatformFactory.h"
#include "../Sprites/Platform/PlatformFactory/MovePlatformFactory.h"

#include "../Sprites/Enemy/Enemy.h"

#include "../Timer/Timer.h"

#include "../Abilitie/JetpackAbility.h"
#include "../Abilitie/ScoreAbility.h"
#include "../Abilitie/ShieldAbility.h"

#include "../Hole/BlackHole.h"
#include "../Hole/WhiteHole.h"


GameFramework::GameFramework()
	:Background{ nullptr }, DoodlePlayer{ nullptr }, RestartTimer{ nullptr }, LastPlatform { nullptr }, Hole { nullptr }
{
}
GameFramework::GameFramework(int width, int height, bool fullscreen)
	: ScreenWidth(width), ScreenHeight(height), isFullScreen(fullscreen),
	Background{ nullptr },
	DoodlePlayer{ nullptr }, RestartTimer{ nullptr }, LastPlatform{ nullptr }, Hole{ nullptr }
{
}

GameFramework::~GameFramework()
{
	Destroy();
}
void GameFramework::Destroy()
{
	if (DoodlePlayer)
	{
		delete DoodlePlayer;

	}
	if (Background)
	{
		delete Background;

	}
	if (RestartTimer)
	{
		delete RestartTimer;

	}

	// Destroy All Object
	DestroyObjectBeforRestart();
}

void GameFramework::PreInit(int& width, int& height, bool& fullscreen)
{
	// Set Screen Size
	width = ScreenWidth;
	height = ScreenHeight;
	fullscreen = isFullScreen;
}
bool GameFramework::Init()
{
	srand(static_cast<unsigned int>(time(0)));

	bool bInitResult = true;

	Background = new GameBackground();

	bInitResult = bInitResult && Background && Background->InitBackground(ScreenWidth, ScreenHeight);

	DoodlePlayer = new Player(*this);
	bInitResult = bInitResult && DoodlePlayer;

	RestartTimer = new Timer();
	bInitResult = bInitResult && RestartTimer;

	InitPlatforms(StartCountPlatforms);

	return bInitResult;
}

bool GameFramework::Tick()
{
	// Get the current time in milliseconds
	unsigned int CurrentTime = getTickCount();

	// Calculate the delta time
	float DelataTimeCoef = 10.f;
	float DeltaTime = static_cast<float>(CurrentTime - LastUpdateTime) / DelataTimeCoef;

	// Update the game with the delta time
	UpdateGame(DeltaTime);
	
	// Save the current time as the last update time
	LastUpdateTime = CurrentTime;

	return false;
}
void GameFramework::UpdateGame(float DeltaTime)
{
	Background->DrawBackground();

	if (NeedToRestart)
	{
		if (!RestartTimer->isStarted())
		{
			RestartTimer->Start();
		}
		if (RestartTimer->GetTime() >= TimeToRestart)
		{
			RestartGame();
			RestartTimer->Stop();
		}
	}
	
	GenareteObjects();

	UpdatePlatforms(DeltaTime);
	UpdateObjectsInList(DeltaTime, Abilitys);
	UpdateObjectsInList(DeltaTime, Enemys);

	if (Hole)
	{
		Hole->Update(DeltaTime, DoodlePlayer);

		if (DestroyCondition(Hole->GetY()))
		{
			delete Hole;
			Hole = nullptr;
			CurrentCountHole --;
		}
	}
	
	DoodlePlayer->DrawSprite(DeltaTime, NeedToRestart);
	

	UpdateScore(DeltaTime);
	Background->DrawTopAndDownBackround(Score, CountPlatformLeft);
}

const char* GameFramework::GetTitle()
{
	return "Doodle Jump";
}

void GameFramework::Close()
{
	Destroy();
}

void GameFramework::onMouseMove(int x, int y, int xrelative, int yrelative)
{
	MouseX = x;
	MouseY = y;
}
void GameFramework::onMouseButtonClick(FRMouseButton button, bool isReleased)
{
	if (!isReleased)
	{
		switch (button)
		{
		case FRMouseButton::LEFT:
			bIsLeftMouseButtonPressed = true;
			break;

		case FRMouseButton::RIGHT:

			break;

		case FRMouseButton::MIDDLE:

			break;

		case FRMouseButton::COUNT:

			break;

		}
	}
	else
	{
		switch (button)
		{
		case FRMouseButton::LEFT:
			bIsLeftMouseButtonPressed = false;
			break;

		case FRMouseButton::RIGHT:

			break;

		case FRMouseButton::MIDDLE:

			break;

		case FRMouseButton::COUNT:

			break;

		}
	}
}
bool GameFramework::IsMouseButtonPressed(FRMouseButton k) const 
{
	switch (k)
	{
	case FRMouseButton::LEFT:
		return bIsLeftMouseButtonPressed;
		break;

	case FRMouseButton::RIGHT:
		return false;
		break;

	case FRMouseButton::MIDDLE:
		return false;
		break;

	case FRMouseButton::COUNT:
		return false;
		break;

	}

	return false;
}
void GameFramework::GetMousePosition(int& xMouse, int& yMouse) const
{
	xMouse = MouseX;
	yMouse = MouseY;
}

void GameFramework::onKeyPressed(FRKey k)
{
	switch (k)
	{
	case FRKey::UP:
		break;

	case FRKey::DOWN:
		break;

	case FRKey::LEFT:
		bIsLeftPressed = true;
		break;

	case FRKey::RIGHT:
		bIsRightPressed = true;
		break;

	case FRKey::COUNT:
		break;
	}
}
void GameFramework::onKeyReleased(FRKey k)
{
	switch (k)
	{
	case FRKey::UP:
		break;

	case FRKey::DOWN:
		break;

	case FRKey::LEFT:
		bIsLeftPressed = false;
		break;

	case FRKey::RIGHT:
		bIsRightPressed = false;
		break;

	case FRKey::COUNT:
		break;
	}
}
bool GameFramework::IsKeyPressed(FRKey k) const
{
	switch (k)
	{
	case FRKey::UP:
		break;

	case FRKey::DOWN:
		break;

	case FRKey::LEFT:
		return bIsLeftPressed;
		break;

	case FRKey::RIGHT:
		return bIsRightPressed;
		break;

	case FRKey::COUNT:
		break;

	default:
		return false;
	}
	return false;
}

void GameFramework::AddScore(int AddedScore)
{
	Score += AddedScore;
}

Player* GameFramework::GetDoodlePlayer()
{
	return DoodlePlayer;
}

void GameFramework::RestartGame()
{
	DestroyObjectBeforRestart();
	InitObjectAfterRestart();

	NeedToRestart = false;
}
void GameFramework::DestroyObjectBeforRestart()
{
	DestroyAllObjectsInList(Abilitys);
	DestroyAllObjectsInList(Enemys);
	DestroyAllObjectsInList(Platforms);
	delete Hole;

	CurrentCountPlatforms = 0;
	CurrentCountHole = 0;

	if (LastPlatform)
	{
		LastPlatform = nullptr;
	}
}
void GameFramework::InitObjectAfterRestart()
{
	InitPlatforms(StartCountPlatforms);

	DoodlePlayer->SetStartOptions();

	CountPlatformLeft = 0;
	Score = 0;
	PreviousScoreWhenSpawnAbility = 0;
	DoodlePlayer->SetDie(false);
}

void GameFramework::GenareteObjects()
{
	
	if (LastPlatform && ((CurrentCountPlatforms <= MinCountPlatforms || LastPlatform->GetY() >= MaxHeightBetweenPlatforms) 
	&& LastPlatform->GetY() > MinHeightBetweenPlatforms))
	{
		Platform* NewPlatform = GenaretePlatforms();

		float NewX;
		float NewY = 0.f;
		GenareteRandomPositionX(NewX, NewPlatform->GetWidth());

		NewPlatform->SetPosition(NewX, NewY);
		Platforms.push_back(NewPlatform);

		// If Move platform dont create Abilyty or Enemy
		if (typeid(*NewPlatform) != typeid(MovePlatform))
		{
			// Generate Enemy every (50) Platform
			if (CountPlatformLeft % PlatformToSpawnEnemy == 0)
			{
				CreateEnemy(NewX, NewY);

				if (MinCountPlatforms > std::floor(ScreenHeight / DoodlePlayer->CalculateMaxJumpHeight()))
				{
					MinCountPlatforms--;
				}
			}
			else if (Score - PreviousScoreWhenSpawnAbility >= ScoreToSpawnAbility)
			{
				CreateAbility(NewX, NewY);
				PreviousScoreWhenSpawnAbility = Score;
			}
		}
	}

	if (CountPlatformLeft % 100 == 0 && CurrentCountHole < MaxCountHole)
	{
		
		if (LastPlatform)
		{
			CreateHole();
			if (Hole)
			{
				float NewX = GenareteRandomNumberWithLimitedRange(LastPlatform->GetX(), LastPlatform->GetWidth(), static_cast<int>(Hole->GetWidth()));
				float NewY = 0.f;

				Hole->SetPosition(NewX, NewY);
			}
		}
	}
}
void GameFramework::GenareteRandomPositionX(float& NewX, int ObjectWidth)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> disX(ObjectWidth / 2, ScreenWidth - ObjectWidth / 2);

	NewX = static_cast<float>(disX(gen));
}

int GameFramework::GenareteRandomNumberWithProbability(int Probability[], int CountPlatforms)
{	
	int RandomNumber = rand() % 100 + 1;
	int Sum = 0;

	for (int i = 0; i < CountPlatforms; ++i)
	{
		Sum += Probability[i];
		if (RandomNumber <= Sum)
		{
			return RandomNumber = i;
		}
	}

	return 0;
}

Platform* GameFramework::CreatePlatformFromFactory(PlatformFactory& factory)
{
	Platform* NewPlatform = factory.CreatePlatform();
	NewPlatform->InitPlatform();

	CurrentCountPlatforms++;

	return NewPlatform;
}

float GameFramework::GenareteRandomNumberWithLimitedRange(float PlatformX, int WidthPlatform, int WidthHole) const
{	
	float minValue = 0;
	float maxValue = 0;

	if (PlatformX <= WidthPlatform / 2 + WidthHole / 2)
	{
		minValue = static_cast<float>(PlatformX + WidthPlatform / 2 + WidthHole / 2);
		maxValue = static_cast<float>(ScreenWidth - WidthHole / 2);
	}
	else if (PlatformX >= ScreenWidth - WidthPlatform / 2 - WidthHole / 2)
	{
		minValue = static_cast<float>(WidthHole / 2);
		maxValue = static_cast<float>(PlatformX - WidthPlatform / 2 - WidthHole / 2);
	}
	else
	{
		int Rand = rand() % 2;
		switch (Rand)
		{
		case 0:
			minValue = static_cast<float>(PlatformX + WidthPlatform / 2 + WidthHole / 2);
			maxValue = static_cast<float>(ScreenWidth - WidthHole / 2);
			break;
		case 1:
			minValue = static_cast<float>(WidthHole / 2);
			maxValue = static_cast<float>(PlatformX - WidthPlatform / 2 - WidthHole / 2);
			break;
		}
	}
	if (minValue >= maxValue)
	{
		float Temp = maxValue;
		maxValue = minValue;
		minValue = maxValue;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> disX(static_cast<int>(minValue), static_cast<int>(maxValue));

	float NewX = static_cast<float>(disX(gen));
	return NewX;
}

void GameFramework::InitPlatforms(int numPlatforms)
{
	float PlatformOffset = floor(static_cast<float>(ScreenHeight / numPlatforms));
	float YPlatformOffset = ScreenHeight - PlatformOffset;

	// Set min Height BetweenPlatform
	MinHeightBetweenPlatforms = PlatformOffset;

	// Set max Height BetweenPlatform
	if (DoodlePlayer)
	{
		MaxHeightBetweenPlatforms = DoodlePlayer->CalculateMaxJumpHeight();
	}
	
	MinCountPlatforms = StartCountPlatforms;

	for (int i = 0; i < numPlatforms; ++i)
	{
		Platform* NewPlatform = GenaretePlatforms();

		float NewX;
		float NewY = YPlatformOffset;

		GenareteRandomPositionX(NewX, NewPlatform->GetWidth());

		NewPlatform->SetPosition(NewX, NewY);
		Platforms.push_back(NewPlatform);

		YPlatformOffset -= PlatformOffset;
	}
}
void GameFramework::UpdatePlatforms(float DeltaTime)
{
	for (auto it = Platforms.begin(); it != Platforms.end();) 
	{
		if (*it)
		{
			(*it)->UpdatePlatform(DeltaTime, DoodlePlayer);

			if (DestroyCondition((*it)->GetY()) || (*it)->IsDestroy())
			{
				delete* it;
				it = Platforms.erase(it);

				CurrentCountPlatforms--;
				CountPlatformLeft++;
			}
			else
			{
				++it;
			}
		}		
	}
}
Platform* GameFramework::GenaretePlatforms()
{
	int  Probability[] = { 50, 10, 20, 15, 5 };

	switch (GenareteRandomNumberWithProbability(Probability))
	{
		case 0:
		{
			BasePlatformFactory Factory;
		
			LastPlatform = CreatePlatformFromFactory(Factory);
			return LastPlatform;

			break;
		}
		case 1:
		{
			CrushPlatformFactory Factory;

			return CreatePlatformFromFactory(Factory);

			break;
		}
		case 2:
		{
			HalfCrushPlatformFactory Factory;
			LastPlatform = CreatePlatformFromFactory(Factory);
			return LastPlatform;

			break;
		}
		case 3:
		{
			MovePlatformFactory Factory;
			LastPlatform = CreatePlatformFromFactory(Factory);

			return LastPlatform;

			break;
		}
		case 4:
		{
			
			JumpPlatformFactory Factory;

			LastPlatform = CreatePlatformFromFactory(Factory);
			return LastPlatform;
				
			break;
						
		}
		default:
		{
			BasePlatformFactory Factory;

			LastPlatform = CreatePlatformFromFactory(Factory);
			return LastPlatform;

			break;
		}
	}

	return nullptr;	
}

void GameFramework::UpdateScore(float DeltaTime)
{
	if (DoodlePlayer->IsWithinMaxJumpHeight())
	{
		float Ñoefficient = 1.5f;
		Score += static_cast<int>(std::round(std::abs(DoodlePlayer->GetDy() * DeltaTime) / Ñoefficient));
	}
}

void GameFramework::CreateEnemy(float x, float y)
{
	Enemys.push_back(new Enemy(x, y));
}
void GameFramework::CreateAbility(float x, float y)
{
	int CountAbilAbilitys = 3;
	int randomIndex = std::rand() % CountAbilAbilitys;

	switch (randomIndex)
	{
		case 0:
		{
			Ability* NewAbilyty = new JetpackAbility(*this, x, y);
			Abilitys.push_back(NewAbilyty);
			break;
		}

		case 1:
		{
			Ability* NewAbilyty = new ScoreAbility(*this, x, y);
			Abilitys.push_back(NewAbilyty);
			break;
		}

		case 2:
		{
			Ability* NewAbilyty = new ShieldAbility(*this, x, y);
			Abilitys.push_back(NewAbilyty);
			break;
		}

	}
}
void GameFramework::CreateHole(float x, float y)
{
	int CountHole = 2;
	int randomIndex = std::rand() % CountHole;

	switch (randomIndex)
	{
		case 0:
		{
			Hole = new BlackHole(x, y);
			break;
		}

		case 1:
		{
			Hole = new WhiteHole(x, y);
			break;
		}
	}

	CurrentCountHole++;
}

template<typename T>
void GameFramework::UpdateObjectsInList(float DeltaTime, std::list<T*>& List)
{
	if (!List.empty())
	{
		for (auto it = List.begin(); it != List.end();)
		{
			if (*it)
			{
				(*it)->Update(DeltaTime, DoodlePlayer);

				if (DestroyCondition((*it)->GetY()) || (*it)->IsDestroy())
				{
					delete* it;
					it = List.erase(it);				

				}
				else
				{
					++it;
				}
			}
		}
	}
}

bool GameFramework::DestroyCondition(float ObjectY, bool Isdestroy)
{
	return (ObjectY >= static_cast<float>(ScreenHeight - DoodlePlayer->GetHeight() / 4) && DoodlePlayer->GetDy() <= 0) || Isdestroy;
}

template<typename T>
void GameFramework::DestroyAllObjectsInList(std::list<T*>& List)
{
	for (auto& element : List)
	{
		if (element)
		{
			delete element;
		}
	}

	List.clear();
}