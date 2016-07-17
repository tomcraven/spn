#ifndef CORE_ASSETPOOL_H
#define CORE_ASSETPOOL_H

#include "core/List.h"
#include "core/Assert.h"

namespace core
{
	template< class T >
	class AssetPool
	{
	public:
		AssetPool() : data( 0 ), size( 0 )
		{
		}

		bool shutdown()
		{
			delete[] data;
			return true;
		}

		bool init( uint32_t numAssets )
		{
			size = numAssets;
			data = new Asset[ numAssets ];
			VALIDATE( data );
			for ( uint32_t i = 0; i < numAssets; ++i )
			{
				freeAssets.push_back( &( data[i] ) );
			}

			offset = reinterpret_cast< uint8_t* >( &data[0].value ) - 
				reinterpret_cast< uint8_t* >( &data[0] );

			return true;
		}

		T* alloc()
		{
			VALIDATE_AND_RETURN( data, 0 );
			VALIDATE_AND_RETURN( !freeAssets.empty(), 0 );

			typename FreeAssetsContainer::Iterator freeAssetsIter = freeAssets.begin();
			VALIDATE_AND_RETURN( freeAssetsIter != freeAssets.end(), 0 );

			Asset* ret = *freeAssetsIter;
			freeAssets.erase( freeAssetsIter );
			return &ret->value;
		}

		bool free( T* ptr )
		{
			Asset* asset = typeToAsset( ptr );
			VALIDATE( asset >= data );
			VALIDATE( asset < data + ( size * sizeof( T )));
			freeAssets.push_back( asset );
			return true;
		}

		uint32_t getNumFreeAssets()
		{
			return freeAssets.size();
		}

	private:
		struct Asset : public core::ListNode
		{
			T value;
		};

		enum
		{
			kAssetSize = sizeof( Asset )
		};
		
		Asset* typeToAsset( T* ptr )
		{
			uint8_t* bytePtr = reinterpret_cast< uint8_t* >( ptr );
			bytePtr -= offset;
			return reinterpret_cast< Asset* >( bytePtr );
		}

		uint32_t offset;
		uint32_t size;

		Asset* data;

		typedef core::List< Asset* > FreeAssetsContainer;
		FreeAssetsContainer freeAssets;
	};
}

#endif