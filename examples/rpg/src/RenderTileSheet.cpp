#include "RenderTileSheet.h"
#include "draw/Draw.h"
#include "math/Rect.h"
#include "Path.h"
#include "component/Position.h"
#include "core/Algorithm.h"
#include "core/Rand.h"
#include "core/File.h"
#include "core/Platform.h"

#include <stdio.h>
#include <iostream>

bool RenderTileSheet::setTileSheet( const char* tileSheet )
{
	tileSheetTexture.initComponent( 0 );
	tileSheetTexture.setTexturePath( tileSheet );
	return true;
}

bool RenderTileSheet::setTileMap( const char* tileMap )
{
	core::File file;
	VALIDATE( file.openRead( tileMap ) );

	uint32_t size = file.size();
	char* buffer = reinterpret_cast< char* >( malloc( size + 1 ) );
	VALIDATE( buffer );
	buffer[size] = '\0';

	core::Slice< char* > bufferSlice( buffer, size );
	file.read( bufferSlice );

	char* context = 0;
	VALIDATE( SSCANF_S( STRTOK_S( buffer, "\n", &context ), "tileswide %u", &tilesWide ) > 0 );
	VALIDATE( SSCANF_S( STRTOK_S( 0, "\n", &context ), "tileshigh %u", &tilesHigh ) > 0 );
	VALIDATE( SSCANF_S( STRTOK_S( 0, "\n", &context ), "tilewidth %u", &tileWidth ) > 0 );
	VALIDATE( SSCANF_S( STRTOK_S( 0, "\n", &context ), "tileheight %u", &tileHeight ) > 0 );
	VALIDATE( STRTOK_S( 0, "\n", &context ) );

	VALIDATE( layers.alloc( 10 ) );		// Max 10 layers supported... can we do better?

	const char* layerHeader = STRTOK_S( 0, "\n", &context );
	while ( layerHeader )
	{
		uint32_t layerIndex = 0;
		VALIDATE( SSCANF_S( layerHeader, "layer %u\n", &layerIndex ) > 0 );

		Layer& layer = layers[ layerIndex ];
		VALIDATE( layer.tiles.alloc( tilesHigh ) );

		for ( uint32_t rowIndex = 0; rowIndex < tilesHigh; ++rowIndex )
		{
			VALIDATE( layer.tiles[ rowIndex ].alloc( tilesWide ) );
			
			char* rowTileNumbers = STRTOK_S( 0, "\n", &context );
			VALIDATE( rowTileNumbers );
			
			char* rowTileNumbersContext = 0;
			char* tileNumber = STRTOK_S( rowTileNumbers, ",", &rowTileNumbersContext );
			VALIDATE( tileNumber );
			for ( uint32_t columnIndex = 0; columnIndex < tilesWide; ++columnIndex )
			{
				VALIDATE( SSCANF_S( tileNumber, "%u", &layer.tiles[ rowIndex ][ columnIndex ] ) > 0 );
				tileNumber = STRTOK_S( 0, ",", &rowTileNumbersContext );
				VALIDATE( tileNumber );
			}
		}
		
		VALIDATE( STRTOK_S( 0, "\n", &context ) );
		layerHeader = STRTOK_S( 0, "\n", &context );
	}

	pathNodes = new Node[ tilesWide * tilesHigh ];
	memset( pathNodes, 0, tilesWide * tilesHigh );

	delete buffer;

	return true;
}

bool RenderTileSheet::setCollisionMap( const char* tileMap )
{
	core::File file;
	VALIDATE( file.openRead( tileMap ) );

	uint32_t size = file.size();
	char* buffer = reinterpret_cast< char* >( malloc( size + 1 ) );
	VALIDATE( buffer );
	buffer[size] = '\0';

	core::Slice< char* > bufferSlice( buffer, size );
	file.read( bufferSlice );
	
	char* context = 0;
	VALIDATE( SSCANF_S( STRTOK_S( buffer, "\n", &context ), "tileswide %u", &tilesWide ) > 0 );
	VALIDATE( SSCANF_S( STRTOK_S( 0, "\n", &context ), "tileshigh %u", &tilesHigh ) > 0 );
	VALIDATE( SSCANF_S( STRTOK_S( 0, "\n", &context ), "tilewidth %u", &tileWidth ) > 0 );
	VALIDATE( SSCANF_S( STRTOK_S( 0, "\n", &context ), "tileheight %u", &tileHeight ) > 0 );
	VALIDATE( STRTOK_S( 0, "\n", &context ) );

	const char* layerHeader = STRTOK_S( 0, "\n", &context );
	uint32_t layerIndex = 0;
	VALIDATE( SSCANF_S( layerHeader, "layer %u\n", &layerIndex ) > 0 );
	
	VALIDATE( collisionLayer.tiles.alloc( tilesHigh ) );

	for ( uint32_t rowIndex = 0; rowIndex < tilesHigh; ++rowIndex )
	{
		VALIDATE( collisionLayer.tiles[ rowIndex ].alloc( tilesWide ) );
			
		char* rowTileNumbers = STRTOK_S( 0, "\n", &context );
		VALIDATE( rowTileNumbers );
			
		char* rowTileNumbersContext = 0;
		char* tileNumber = STRTOK_S( rowTileNumbers, ",", &rowTileNumbersContext );
		VALIDATE( tileNumber );
		for ( uint32_t columnIndex = 0; columnIndex < tilesWide; ++columnIndex )
		{
			VALIDATE( SSCANF_S( tileNumber, "%u", &collisionLayer.tiles[ rowIndex ][ columnIndex ] ) > 0 );
			tileNumber = STRTOK_S( 0, ",", &rowTileNumbersContext );
			VALIDATE( tileNumber );
		}
	}

	delete buffer;

	return true;
}

bool RenderTileSheet::render()
{
	for ( uint32_t layerIndex = 0; layerIndex < layers.size(); ++layerIndex )
	{
		VALIDATE( renderLayer( layers[ layerIndex ] ) );
	}

	return true;
}

bool RenderTileSheet::clampCoordsToGrid( int32_t& x, int32_t& y )
{
	x -= ( x % tileWidth );
	y -= ( y % tileHeight );

	return true;
}

bool RenderTileSheet::shutdown()
{
	delete pathNodes;
	return true;
}

bool RenderTileSheet::createPathTo( 
	const component::Position& start, 
	const component::Position& end,
	Path& path )
{
	memset( pathNodes, 0, tilesWide * tilesHigh * sizeof( Node ) );
	openList.clear();
	
	Node& beginNode = getNodeFromPosition( start );
	Node& endNode = getNodeFromPosition( end );

	CHECK( findPath( beginNode, endNode ) );

	Node* pathNode = &endNode;
	while ( pathNode )
	{
		int32_t x = pathNode->gridX * tileWidth;
		int32_t y = pathNode->gridY * tileHeight;
		VALIDATE( clampCoordsToGrid( x, y ) );
		VALIDATE( path.add( x, y ) );

		pathNode = pathNode->parent;
	};
	
	// Pop the first as it's the same as the starting position
	VALIDATE( path.pop() );

	return true;
}

bool RenderTileSheet::positionIsWalkable( const component::Position& pos )
{
	CHECK( pos.x >= 0.0f );
	CHECK( pos.y >= 0.0f );
	CHECK( pos.x < ( tileWidth * tilesWide ) );
	CHECK( pos.y < ( tileHeight * tilesHigh ) );

	Node& tile = getNodeFromPosition( pos );
	return tileIsWalkable( tile.gridX, tile.gridY );
}

uint32_t RenderTileSheet::getWidth()
{
	return tilesWide * tileWidth;
}

uint32_t RenderTileSheet::getHeight()
{
	return tilesHigh * tileHeight;
}

uint32_t getHeight();

bool RenderTileSheet::findPath( Node& startNode, const Node& endNode )
{
	Node* currentNode = &startNode;
	do
	{
		VALIDATE( addNodeToList( *currentNode, kClosed ) );

		if ( endNode.state == kClosed )
		{
			return true;
		}

		Node* node = getNextSurroundingNode( 0, currentNode->gridX, currentNode->gridY );
		while ( node )
		{
			if ( node->state == kNeither )
			{
				addNodeToList( *node, kOpen );
				node->parent = currentNode;
				node->h = calculateHValue( node, endNode );
				node->g = calculateGValue( node, currentNode );
			}
			else if ( node->state == kOpen )
			{
				uint32_t newGValue = calculateGValue( node, currentNode );
				if ( newGValue < node->g )
				{
					node->parent = currentNode;
					node->g = newGValue;
				}
			}

			node = getNextSurroundingNode( node, currentNode->gridX, currentNode->gridY );
		};

		currentNode = getLowestFScoreNode();
	} while ( !openList.empty() );

	return false;
}

RenderTileSheet::Node* RenderTileSheet::getLowestFScoreNode()
{
	core::List< Node* >::Iterator iter = openList.begin();

	Node* lowestFScoreNode = *iter;
	uint32_t fScore = lowestFScoreNode->g + lowestFScoreNode->h;
	
	while ( ( *iter )->state == kClosed )
	{
		iter = openList.erase( iter );

		if ( openList.empty() )
		{
			return 0;
		}
	}

	for ( ; iter != openList.end(); )
	{
		Node* node = *iter;

		if ( node->state == kClosed )
		{
			iter = openList.erase( iter );
		}
		else
		{
			if ( node->g + node->h < fScore )
			{
				fScore = node->g + node->h;
				lowestFScoreNode = node;
			}
			++iter;
		}
	}

	return lowestFScoreNode;
}

uint32_t RenderTileSheet::calculateHValue( RenderTileSheet::Node* node, const RenderTileSheet::Node& endNode )
{
	return ( core::algorithm::abs< int32_t >( static_cast< int32_t >( node->gridX ) - endNode.gridX ) +
		core::algorithm::abs< int32_t >( static_cast< int32_t >( node->gridY ) - endNode.gridY ) ) * 10;
}

uint32_t RenderTileSheet::calculateGValue( RenderTileSheet::Node* node, const RenderTileSheet::Node* endNode )
{
	uint32_t gValue = ( ( node->gridX == endNode->gridX ) || ( node->gridY == endNode->gridY ) ) ? 10 : 14;
	return endNode->g + gValue;
}

RenderTileSheet::Node* RenderTileSheet::getNextSurroundingNode( Node* inNode, uint32_t x, uint32_t y )
{
	uint32_t xBegin = core::algorithm::max( 0, static_cast< int32_t >( x - 1 ) );
	uint32_t xEnd = core::algorithm::min( tilesWide - 1, x + 1 );
	uint32_t yBegin = core::algorithm::max( 0, static_cast< int32_t >( y - 1 ) );
	uint32_t yEnd = core::algorithm::min( tilesHigh - 1, y + 1 );

	bool returnNext = inNode ? false : true;
	for ( uint32_t i = yBegin; i <= yEnd; ++i )
	{
		for ( uint32_t j = xBegin; j <= xEnd; ++j )
		{
			if ( !( j == x && i == y ) )
			{
				Node& node = getNodeFromGridPosition( j, i );
				if ( tileIsWalkable( j, i ) )
				{
					if ( returnNext )
					{
						return &node;
					}

					if ( &node == inNode )
					{
						returnNext = true;
					}
				}
			}
		}
	}

	return 0;
}

bool RenderTileSheet::tileIsWalkable( uint32_t x, uint32_t y )
{
	uint32_t index = indexFromGridPosition( x, y );
	ASSERT( index < ( tilesWide * tilesHigh ) );

	return collisionLayer.tiles[ y ][ x ] != 0;
}

RenderTileSheet::Node& RenderTileSheet::getNodeFromPosition( const component::Position& pos )
{
	ASSERT( pos.x >= 0.0f );
	ASSERT( pos.y >= 0.0f );

	uint32_t x = static_cast< uint32_t >( pos.x );
	uint32_t y = static_cast< uint32_t >( pos.y );

	return getNodeFromCoordinate( x, y );
}

RenderTileSheet::Node& RenderTileSheet::getNodeFromCoordinate( uint32_t x, uint32_t y )
{
	return getNodeFromGridPosition( x / tileWidth, y / tileHeight );
}

RenderTileSheet::Node& RenderTileSheet::getNodeFromGridPosition( uint32_t x, uint32_t y )
{
	uint32_t index = indexFromGridPosition( x, y );
	ASSERT( index < ( tilesWide * tilesHigh ));
	Node& ret = pathNodes[ index ];

	ret.gridX = x;
	ret.gridY = y;

	return ret;
}

uint32_t RenderTileSheet::indexFromGridPosition( uint32_t x, uint32_t y )
{
	return ( y * tilesHigh ) + x;
}

bool RenderTileSheet::addNodeToList( RenderTileSheet::Node& node, RenderTileSheet::OpenClosedState list )
{
	node.state = list;
	switch ( list )
	{
	case kOpen:
		openList.push_back( &node );
		return true;
	case kClosed:
		return true;
	default:
		return false;
	}
}

bool RenderTileSheet::renderLayer( const Layer& layer )
{
	const Tiles& tiles = layer.tiles;

	for ( uint32_t y = 0; y < tiles.size(); ++y )
	{
		const core::Array< int32_t >& row = tiles[ y ];

		for ( uint32_t x = 0; x < row.size(); ++x )
		{
			CHECK( renderTile( row[ x ], x, y ) );
		}
	}

	return true;
}

bool RenderTileSheet::renderTile( int32_t tileNumber, uint32_t x, uint32_t y )
{
	if ( tileNumber < 0 )
	{
		return true;
	}

	VALIDATE( ( tileSheetTexture.getWidth() % tileWidth ) == 0 );
	VALIDATE( ( tileSheetTexture.getHeight() % tileHeight ) == 0 );

	uint32_t numTilesWide = tileSheetTexture.getWidth() / tileWidth;
	uint32_t numTilesHigh = tileSheetTexture.getHeight() / tileHeight;

	uint32_t tileXIndex = tileNumber % numTilesWide;
	uint32_t tileYIndex = tileNumber / numTilesWide;

	float tilePositionOnScreen[ 2 ] = { 
		static_cast< float >( x * tileWidth ), 
		static_cast< float >( y * tileHeight ) 
	};

	math::Rect< uint32_t > tilePositionInSheet(
		tileXIndex * tileWidth,
		tileYIndex * tileHeight,
		tileWidth,
		tileWidth );

	draw::Draw::get().blitRegion( 
		&tileSheetTexture, 
		tilePositionInSheet, 
		tilePositionOnScreen[0], tilePositionOnScreen[1] );

	return true;
}