#ifndef NPC_H
#define NPC_H

#include "component/ComponentEntity.h"
#include "component/Texture.h"
#include "component/RenderTexture.h"
#include "component/Position.h"
#include "component/Dimensions.h"

class NPC : public component::ComponentEntity
{
public:
	NPC();

public: // game::Entity
	virtual bool init();
	virtual bool render();

private:
	component::Texture texture;
	component::RenderTexture r;
	component::Position position;
	component::Dimensions d;
};

#endif