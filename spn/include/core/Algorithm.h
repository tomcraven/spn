#ifndef CORE_ALGORITHM_H
#define CORE_ALGORITHM_H

namespace core
{
	namespace algorithm
	{
		template< class T >
		static T max( const T& a, const T& b )
		{
			return ( a > b ) ? a : b;
		}

		template< class T >
		static T min( const T& a, const T& b )
		{
			return ( a < b ) ? a : b;
		}

		template< class T >
		static T clamp( const T& val, const T& low, const T& high )
		{
			return min( high, max( low, val ) );
		}

		template< class T >
		static T abs( const T& value )
		{
			if ( value < 0 )
			{
				return value * -1;
			}
			return value;
		}

		static bool floatEquals( float a, float b, float error = 0.001f )
		{
			return ( abs( a - b ) < error );
		}

		template< class T >
		static void swap( T& a, T& b )
		{
			T temp = a;
			a = b;
			b = temp;
		}

		static int32_t round( float in )
		{
			return static_cast< int32_t >( in + 0.5 );
		}

		static int32_t roundDown( float in )
		{
			return static_cast< int32_t >( in );
		}
	};
}

#endif