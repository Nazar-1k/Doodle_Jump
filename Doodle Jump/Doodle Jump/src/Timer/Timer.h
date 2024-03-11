#pragma once

//The application time based timer
class Timer
{
public:
	//Initializes variables
	Timer();

	//The various clock actions
	void Start();
	void Stop();
	void Pause();
	void UnPause();

	//Gets the timer's time
	unsigned int GetTime() const;

	//Checks the status of the timer
	bool isStarted() const;
	bool isPaused() const;

private:
	//The clock time when the timer started
	unsigned int StartTicks;

	//The ticks stored when the timer was paused
	unsigned int PausedTicks;

	//The timer status
	bool Paused;
	bool Started;
};

