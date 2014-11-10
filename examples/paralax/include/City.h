#ifndef CITY_H
#define CITY_H

#include "component/ComponentEntity.h"
#include "core/AssetPool.h"
#include "Building.h"
#include "async/Timer.h"
#include "component/WindowExitCollision.h"

class City : 
	public async::Timer::IExpiredListener,
	public component::WindowExitCollision::IWindowExitCollisionListener
{
public:
	bool init( uint32_t numConcurrentBuildings );
	bool shutdown();
	bool update( float timeStepSeconds );
	bool render();

public: // async::Timer::IExpiredListener
	virtual bool onTimerExpired( uint32_t id );

public: // component::WindowExitCollision::IWindowExitCollisionListener
	virtual bool onWindowExit( component::ComponentEntity* entity, bool left, bool right, bool top, bool bottom );

private:
	bool createBuilding();

	core::AssetPool< Building > buildingPool;
	std::vector< Building* > buildings;

	async::Timer buildingCreateTimer;
};

#endif