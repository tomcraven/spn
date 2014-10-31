#ifndef CORE_ASSETPOOL_H
#define CORE_ASSETPOOL_H

#include <vector>
#include "core/Assert.h"

template< class T >
class AssetPool
{
public:
	bool shutdown()
	{
		// Cannot use vector.clear as it leaves allocations that cause an assertion during Iw2DTerminate
		FreeAssetsContainer().swap( freeAssets );

		delete[] data;
		return true;
	}

	bool init( uint32_t numAssets )
	{
		data = new T[ numAssets ];
		VALIDATE( data );
		for ( uint32_t i = 0; i < numAssets; ++i )
		{
			freeAssets.push_back( &( data[i] ) );
		}

		return true;
	}

	T* alloc()
	{
		VALIDATE_AND_RETURN( !freeAssets.empty(), 0 );

		FreeAssetsContainer::iterator freeAssetsIter = freeAssets.begin();
		VALIDATE_AND_RETURN( freeAssetsIter != freeAssets.end(), 0 );

		T* ret = *freeAssetsIter;
		freeAssets.erase( freeAssetsIter );
		return ret;
	}

	void free( T* asset )
	{
		freeAssets.push_back( asset );
	}

private:
	T* data;

	typedef std::vector< T* > FreeAssetsContainer;
	FreeAssetsContainer freeAssets;
};

#endif