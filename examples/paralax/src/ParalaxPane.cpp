#include "ParalaxPane.h"
#include "draw/Draw.h"
#include "core/Assert.h"

ParalaxPane::ParalaxPane()
{
	attach( &t );
	attach( &p );
	attach( &v );
	attach( &r );
	attach( &d );
}

bool ParalaxPane::init( Config inConfig )
{
	VALIDATE( ComponentEntity::init() );

	config = inConfig;

	t.setTexturePath( config.texturePath );
	p.set( config.startingPosition.x, config.startingPosition.y );
	v.set( config.velocity.x, config.velocity.y );

	return true;
}

bool ParalaxPane::render()
{
	if ( config.repeatX && config.repeatY )
	{
		const int32_t numVertical = ( draw::Draw::getScreenHeight() / d.height ) + 2;
		const int32_t numHorizontal = ( draw::Draw::getScreenWidth() / d.width ) + 2;
		
		for ( int32_t i = -1; i < numVertical; ++i )
		{
			for ( int32_t j = -1; j < numHorizontal; ++j )
			{
				VALIDATE( r.render( 
					component::Position( 
						p.x + ( j * static_cast< int32_t >( d.width ) ), 
						p.y + ( i * static_cast< int32_t >( d.height ) ) 
					) 
				) );
			}
		}
	}
	else if ( config.repeatX )
	{
		const int32_t numHorizontal = ( draw::Draw::getScreenWidth() / d.width ) + 2;
		for ( int32_t i = -1; i < numHorizontal; ++i )
		{
			VALIDATE( r.render( 
				component::Position( 
					p.x + ( i * static_cast< int32_t >( d.width ) ), 
					p.y 
				) 
			) );
		}
	}
	else if ( config.repeatY )
	{
		const int32_t numVertical = ( draw::Draw::getScreenHeight() / d.height ) + 2;
		for ( int32_t i = -1; i < numVertical; ++i )
		{
			VALIDATE( r.render( 
				component::Position( 
					p.x, 
					p.y + ( i * static_cast< int32_t >( d.height ) ) 
				) 
			) );
		}
	}
	else
	{
		VALIDATE( r.render( p ) );
	}

	return true;
}

bool ParalaxPane::update( float timeStepSeconds )
{
	VALIDATE( ComponentEntity::update( timeStepSeconds ) );
	
	if ( v.x > 0.0f )
	{
		if ( p.x > d.width )
		{
			p.x = 0.0f;
		}
	}
	else
	{
		if ( p.x < -static_cast< int32_t >( d.width ) )
		{
			p.x = 0.0f;
		}
	}

	if ( v.y > 0.0f )
	{
		if ( p.y > d.height )
		{
			p.y = 0.0f;
		}
	}
	else
	{
		if ( p.y < -static_cast< int32_t >( d.height ) )
		{
			p.y = 0.0f;
		}
	}

	return true;
}