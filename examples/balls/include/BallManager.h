#ifndef BALLMANAGER_H
#define BALLMANAGER_H

#include "Ball.h"
#include <vector>

class MainRoom;

class BallManager : public game::Button::Consumer
{
public:
	BallManager( MainRoom* mainRoom );

	bool init( uint32_t numBalls );
	bool shutdown();
	bool update( float timeStepSeconds );
	bool render();
	const char* getNumClickedBallsString();

private: // game::Button::Consumer
	virtual bool onButtonConsumerClick( uint32_t id );

private:
	bool updateClickedBallCountBuffer();

	Ball* freeBalls;
	typedef std::vector< Ball* > BallContainer;
	BallContainer balls;
	BallContainer::iterator ballToErase;
	
	uint32_t clickedBallCount;
	enum
	{
		kClickedBallCountBufferSize = 5
	};
	char clickedBallCountBuffer[ kClickedBallCountBufferSize ];

	MainRoom* mainRoom;
};

#endif