#ifndef COMPONENT_RENDERSHEET_H
#define COMPONENT_RENDERSHEET_H

#include "component/IComponent.h"
#include "component/RenderTexture.h"
#include "component/IRender.h"

namespace component
{
	class Position;
	class Texture;
	class Dimensions;

	class RenderSheet : public IComponent, public IRender
	{
	public:
		RenderSheet();
		void setTexture( Texture* t, Dimensions* d, uint32_t frameWidth, uint32_t frameHeight, float speed );

	public: // IRender
		bool render( const Position& p );

	public: // IComponent
		virtual bool update( ComponentEntity* entity, float timeStep );
		virtual uint32_t getType();

	public:
		virtual bool shouldIncrementFrame( ComponentEntity* entity );

	private:
		bool updateCurrentFrame( float timeStep, ComponentEntity* entity );
		void incrementFrame();

	private:
		RenderTexture r;
		Texture* texture;
		uint32_t frameWidth, frameHeight;
		uint32_t numFramesX, numFramesY;
		float speed, timeUntilFrameChange;
		uint32_t currentFrame[2];
	};
}

#endif