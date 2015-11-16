#ifndef RENDER_TILE_SHEET_H
#define RENDER_TILE_SHEET_H

#include "component/Texture.h"
#include "core/Array.h"
#include "Level.h"
#include "core/List.h"

class Path;

class RenderTileSheet : public Level
{
public:
	bool setTileSheet( const char* tilesheet );
	bool setTileMap( const char* tilemap );
	bool setCollisionMap( const char* map );

	bool render();

	bool clampCoordsToGrid( int32_t& x, int32_t& y );

	bool shutdown();

public: // Level
	virtual bool createPathTo( 
		const component::Position& start, 
		const component::Position& end,
		Path& path );

	virtual bool positionIsWalkable(
		const component::Position& pos );
	
	virtual uint32_t getWidth();
	virtual uint32_t getHeight();

private:
	component::Texture tileSheetTexture;

	typedef core::Array< core::Array< int32_t > > Tiles;
	struct Layer
	{
		Tiles tiles;
		component::Texture texture;
	};
	core::Array< Layer > layers;
	Layer collisionLayer;

	bool renderLayer( const Layer& layer );
	bool renderTile( int32_t tileNumber, uint32_t x, uint32_t y );

	uint32_t tileWidth, tileHeight;
	uint32_t tilesWide, tilesHigh;

	enum OpenClosedState
	{
		kNeither,
		kOpen,
		kClosed
	};

	struct Node : public core::ListNode
	{
		OpenClosedState state;
		Node* parent;
		uint32_t g, h;
		uint32_t gridX, gridY;
	};
	Node* pathNodes;

	bool findPath( Node& startNode, const Node& endNode );
	uint32_t indexFromGridPosition( uint32_t x, uint32_t y );
	Node& getNodeFromPosition( const component::Position& pos );
	Node& getNodeFromCoordinate( uint32_t x, uint32_t y );
	Node& getNodeFromGridPosition( uint32_t x, uint32_t y );
	bool addNodeToList( Node& node, OpenClosedState list );
	Node* getNextSurroundingNode( Node* inNode, uint32_t x, uint32_t y );
	uint32_t calculateHValue( Node* node, const Node& endNode );
	uint32_t calculateGValue( Node* node, const Node* endNode );
	Node* getLowestFScoreNode();
	bool tileIsWalkable( uint32_t x, uint32_t y );

	core::List< Node* > openList;
};

#endif