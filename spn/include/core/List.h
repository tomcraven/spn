#ifndef LIST_H
#define LIST_H

#include "core/Types.h"

namespace core
{
	struct ListNode
	{
		ListNode() : previous( 0 ), next( 0 )
		{
		}

		ListNode* previous;
		ListNode* next;
	};

	template< class T >
	class List
	{
	public:
		class Iterator
		{
		public:
			Iterator() : node( 0 )
			{
			}

			Iterator( ListNode* inNode ) : node( inNode )
			{
			}
			
			T operator*() const
			{
				return static_cast< T >( node );
			}
			
			void operator++() const
			{
				node = node->next;
			}

			void operator--()
			{
				node = node->previous;
			}

			bool operator!=( const Iterator& other ) const
			{
				return node != other.node;
			}

			mutable ListNode* node;
		};

	public:
		List() : head( 0 ), tail( 0 ), numNodes( 0 )
		{
		}

		void push_back( ListNode* item )
		{
			if ( !head )
			{
				head = item;
				tail = item;

				item->next = 0;
				item->previous = 0;
			}
			else
			{
				tail->next = item;
				item->previous = tail;
				item->next = 0;
				tail = item;
			}

			++numNodes;
		}

		Iterator erase( Iterator item )
		{
			bool itemIsHead = ( item.node == head );
			bool itemIsTail = ( item.node == tail );

			Iterator ret = item.node->next;

			if ( itemIsHead || itemIsTail )
			{
				if ( itemIsHead )
				{
					head = item.node->next;

					if ( head )
					{
						head->previous = 0;
					}
				}

				if ( itemIsTail )
				{
					tail = item.node->previous;

					if ( tail )
					{
						tail->next = 0;
					}
				}
			}
			else
			{
				item.node->previous->next = item.node->next;
				item.node->next->previous = item.node->previous;
			}
			
			--numNodes;

			return ret;
		}

		Iterator begin() const
		{
			return Iterator( head );
		}

		Iterator end() const
		{
			return Iterator( 0 );
		}

		uint32_t size()
		{
			return numNodes;
		}

		bool empty()
		{
			return ( size() == 0 );
		}

		Iterator find( T item )
		{
			/// @todo
			return end();
		}

		void clear()
		{
			head = 0;
			tail = 0;
			numNodes = 0;
		}
		
	public:
		ListNode* head;
		ListNode* tail;

		uint32_t numNodes;
	};
}

#endif