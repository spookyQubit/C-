// Implement an LRU
// This will be implemented with:
// 1) Doubly linked list
// 2) A hash function


#include <iostream>
#include <unordered_map>
#include <list>
//#include <pair>

using namespace std;


class LRU
{
	private:
		typedef list<int>::iterator list_iterator;
		size_t                                  d_max_cache_size; // The allowed size of the cache
		size_t                                  d_current_cache_size;
        unordered_map<int, list_iterator> d_page_id_map; // A map to store the 
                                                               // page id and reference 
                                                               // to thier position 
        list<int>                               d_page_position_list; // List of page id where 
                                                                      // the most recently used at 
                                                                      // the head and least at the tail


	public:
		LRU(size_t n): d_max_cache_size(n), d_current_cache_size(0){}
		~LRU(){}

		void insert(int page_id);
		void print_cache() const;
		
};



void LRU::insert(int page_id)
{
    // If the page_id already exisits:
	if(d_page_id_map.find(page_id) != d_page_id_map.end())
	{
		// If the page_id already exisits:
        // 1) Get the list iterator from map
        // 2) Delete the page_id from the list
        // 3) Insert it at the beginning of the list
        // 4) Update the map to have begin
        list<int>::iterator iter_to_delete = d_page_id_map.at(page_id); 
	    d_page_position_list.erase(iter_to_delete);
	    d_page_position_list.push_front(page_id);
	    d_page_id_map.at(page_id) = d_page_position_list.begin(); 

	    return;
	}


    // If the page_id does not exisits:
    // 1) If the cache is already full
    // 2) If the cache is not yet full
	if(d_current_cache_size >= d_max_cache_size) // Cache is already full
	{
		// 1) Remove the last element from the list
		// 2) Remove the cache from the map
		// 3) Insert the element in the front of the list
        // 4) Insert the element in the map
        int page_id_to_remove = d_page_position_list.back();
        d_page_position_list.pop_back();  
        d_page_id_map.erase(page_id_to_remove);
        d_page_position_list.push_front(page_id);
        pair<int, list<int>::iterator> p = make_pair(page_id, d_page_position_list.begin());
	    d_page_id_map.insert(p);
        return;
	}
	else // Cache is not yet full
	{
		// 1) Inser the element in the front of the list
        // 2) nsert the element in the map
        // 3) Increment the current cache size
		d_page_position_list.push_front(page_id);
		pair<int, list<int>::iterator> p = make_pair(page_id, d_page_position_list.begin());
		d_page_id_map.insert(p);
		++d_current_cache_size;
		return;
	}
}


void LRU::print_cache() const
{
	for(list<int>::const_iterator iter = d_page_position_list.begin(); 
		iter != d_page_position_list.end();
		++iter)
	{
		cout << *iter << endl;
	}
}


int main()
{
	LRU lru(3);
    
 
    //int page_seq[] = {1, 2, 3, 4};
    //int page_seq[] = {1, 1, 1, 1};
    //int page_seq[] = {1, 2, 1, 2};
    int page_seq[] = {1, 1, 1, 1, 5, 6, 5, 6};

    for(int i=0; i<sizeof(page_seq)/sizeof(int); ++i)
    {
    	lru.insert(page_seq[i]);
    }

    lru.print_cache();

}