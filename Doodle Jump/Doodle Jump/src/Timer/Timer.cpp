#include "Timer.h"
#include <iostream>

#include "Framework.h"

Timer::Timer()
{
	//Initialize the variables
	StartTicks = 0;
	PausedTicks = 0;

	Paused = false;
	Started = false;
}

void Timer::Start()
{
	//Start the timer
	Started = true;

	//Unpause the timer
	Paused = false;

	//Get the current clock time
	StartTicks = getTickCount();
	PausedTicks = 0;
}

void Timer::Stop()
{
	//Stop the timer
	Started = false;

	//Unpause the timer
	Paused = false;

	//Clear tick variables
	StartTicks = 0;
	PausedTicks = 0;
}

void Timer::Pause()
{
	//If the timer is running and isn't already paused
	if (Started && !Paused)
	{
		//Pause the timer
		Paused = true;

		//Calculate the paused ticks
		PausedTicks = getTickCount() - StartTicks;
		StartTicks = 0;
	}
}

void Timer::UnPause()
{
	//If the timer is running and paused
	if (Started && Paused)
	{
		//Unpause the timer
		Paused = false;

		//Reset the starting ticks
		StartTicks = getTickCount() - PausedTicks;

		//Reset the paused ticks
		PausedTicks = 0;
	}
}

unsigned int Timer::GetTime() const
{
	//The actual timer time
	unsigned int Time = 0;

	//If the timer is running
	if (Started)
	{
		//If the timer is paused
		if (Paused)
		{
			//Return the number of ticks when the timer was paused
			Time = PausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			Time = getTickCount() - StartTicks;
		}
	}

	return Time;
}

bool Timer::isStarted() const
{
	//Timer is running and paused or unpaused
	return Started;
}

bool Timer::isPaused() const
{
	//Timer is running and paused or unpaused
	return Started;
}
