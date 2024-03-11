#pragma once

#include "Framework.h"
#include <vector>
#include <list>


class GameBackground;
class Player;
class Platform;
class Enemy;
class Ability;
class Hole;
class Timer;

class PlatformFactory;

class GameFramework : public Framework
{
public:

	GameFramework();
	GameFramework(int width, int height, bool fullscreen = false);
	~GameFramework();
	void Destroy(); // Destroy All Object

	virtual void PreInit(int& width, int& height, bool& fullscreen) override;
	virtual bool Init() override;

	virtual bool Tick() override;
	virtual void UpdateGame(float DeltaTime);

	virtual const char* GetTitle() override;
	virtual void Close() override;

public:

	// Mouse function
	virtual void onMouseMove(int x, int y, int xrelative, int yrelative);
	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);
	bool IsMouseButtonPressed(FRMouseButton k) const;
	void GetMousePosition(int& xMouse, int& yMouse) const;

	// Keyboard function
	virtual void onKeyPressed(FRKey k);
	virtual void onKeyReleased(FRKey k);
	bool IsKeyPressed(FRKey k) const;

public:

	int GetScreenWitdth() const { return ScreenWidth; }
	int GetScreenHeight() const { return ScreenHeight; }

public:
	
	void AddScore(int AddedScore);
	Player* GetDoodlePlayer();

private:

	// Screen Settings
	int ScreenWidth = 600;
	int ScreenHeight = 1000;
	bool isFullScreen = false;

	// Saves the last update time
	unsigned int LastUpdateTime = 0;

	// Key Button Pressed
	bool bIsLeftPressed = false;
	bool bIsRightPressed = false;

	// Mouse Button Pressed
	bool bIsLeftMouseButtonPressed = false;

	int MouseX = 0;
	int MouseY = 0;

private:

	// Restart
	bool NeedToRestart = false;
	Timer* RestartTimer;
	unsigned int TimeToRestart = 700; // 0.7 second

	void RestartGame();
	void DestroyObjectBeforRestart();
	void InitObjectAfterRestart();

private:

	// Player
	Player* DoodlePlayer;

private:

	void GenareteObjects();
	void GenareteRandomPositionX(float& NewX, int ObjectWidth = 0);
	int GenareteRandomNumberWithProbability(int Probability[], int CountPlatforms = 5);

	Platform* CreatePlatformFromFactory(PlatformFactory& factory);

	float GenareteRandomNumberWithLimitedRange(float PlatformX, int WidthPlatform, int WidthHole) const;

private:

	// Platform
	std::list<Platform*> Platforms;
	void InitPlatforms(int numPlatforms);
	void UpdatePlatforms(float DeltaTime);
	Platform* GenaretePlatforms(); 

	// Heights Berween Platforms
	float MinHeightBetweenPlatforms = 0;
	float MaxHeightBetweenPlatforms = 0;

	int StartCountPlatforms = 15;

	// Current count Platforms
	int CurrentCountPlatforms = 0;
	int MinCountPlatforms = 10;

	// The last generated platform from which you can jump
	Platform* LastPlatform;

	// The number of platforms the player has passed
	int CountPlatformLeft = 0;

private:

	// Score
	int Score = 0;

	// Previous number of points when spawning abilities
	int PreviousScoreWhenSpawnAbility = 0;
	int ScoreToSpawnAbility = 1000;
	
	void UpdateScore(float DeltaTime);

private:

	// Enemy
	std::list<Enemy*> Enemys;
	void CreateEnemy(float x, float y);

	// Count platform to spawn Enemy
	int PlatformToSpawnEnemy = 50;

private:

	// Abilitys
	std::list<Ability*> Abilitys;
	void CreateAbility(float x, float y);

private:

	// Hole
	Hole* Hole;
	void CreateHole(float x = 0, float y = 0);

	int CurrentCountHole = 0;

	int MaxCountHole = 1;

private:
	// Update all object in List
	template<typename T>
	void UpdateObjectsInList(float DeltaTime, std::list<T*>& List);

private:
	// If object left the screen
	bool DestroyCondition(float ObjectY, bool Isdestroy = false);

	template<typename T>
	void DestroyListObject(std::list<T*>& List, typename std::list<T*>::iterator it);

	// Destroy all object in List
	template<typename T>
	void DestroyAllObjectsInList(std::list<T*>& List);

private:

	// Background 
	GameBackground* Background;
};
