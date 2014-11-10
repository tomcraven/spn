#ifndef PARALAXPANE_H
#define PARALAXPANE_H

#include "component/ComponentEntity.h"
#include "component/Position.h"
#include "component/RenderTexture.h"
#include "component/Texture.h"
#include "component/Velocity.h"
#include "component/WindowExitCollision.h"
#include "component/Dimensions.h"

class ParalaxPane : public component::ComponentEntity
{
public:
	struct Config
	{
		const char* texturePath;
		bool repeatX, repeatY;
		
		component::Position startingPosition;
		component::Velocity velocity;
	};

public:
	ParalaxPane();
	bool init( Config config );

public: // component::ComponentEntity
	virtual bool render();
	virtual bool update( float timeStepSeconds );

private:
	component::Texture t;
	component::Position p;
	component::Velocity v;
	component::RenderTexture r;
	component::Dimensions d;

	Config config;
};

#endif