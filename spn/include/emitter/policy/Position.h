#ifndef EMITTER_POLICY_POSITION_H
#define EMITTER_POLICY_POSITION_H

#include "component/Position.h"

namespace emitter
{
	namespace policy
	{
		class Position
		{
		public:
			virtual component::Position getPosition() = 0;
		};

		namespace position
		{
			class Point : public Position
			{
			public:
				Point( float inX, float inY ) : x( inX ), y( inY )
				{
				}

			public:
				virtual component::Position getPosition()
				{
					return component::Position( x, y );
				}

			private:
				float x, y;
			};
		
			class RectEdge : public Position
			{
			public:
				RectEdge()
				{
				}

				void set( component::Position& position, component::Dimensions& dimensions )
				{
					p = &position;
					d = &dimensions;
				}

			public: // Position
				virtual component::Position getPosition()
				{
					float x = p->x - ( d->width / 2 );
					float y = p->y - ( d->height / 2 );
					uint32_t width = d->width;
					uint32_t height = d->height;

					bool verticalEdge = core::random::boolean();
					if ( verticalEdge )
					{
						float randomX = core::random::range( x, x + width );
						bool top = core::random::boolean();
						if ( top )
						{
							return component::Position( randomX, y );
						}
						else
						{
							return component::Position( randomX, y + height );
						}
					}
					else
					{
						float randomY = core::random::range( y, y + height );
						bool left = core::random::boolean();
						if ( left )
						{
							return component::Position( x, randomY );
						}
						else
						{
							return component::Position( x + width, randomY );
						}
					}
				}

			private:
				component::Position* p;
				component::Dimensions* d;
			};
		
			class Rect : public Position
			{
			public:
				Rect()
				{
				}

				void set( component::Position& position, component::Dimensions& dimensions )
				{
					p = &position;
					d = &dimensions;
				}

			public: // Position
				virtual component::Position getPosition()
				{
					return component::Position( core::random::range( p->x, p->x + d->width ),
						core::random::range( p->y, p->y + d->height ) );
				}

			private:
				component::Position* p;
				component::Dimensions* d;
			};
		}
	}
}

#endif