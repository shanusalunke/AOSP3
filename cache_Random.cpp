#include <iostream>
#include "cache_Random.h"

cache_random::cache_random()
{
	CACHE_SIZE = CACHE_MAX_SIZE;
	size = 0;
}

cache_random::cache_random(int max)
{
	CACHE_SIZE = max;
	size = 0;
}

void cache_random::cache_set_max(int max)
{
	CACHE_SIZE = max;
}

int cache_random::cache_isFull(int data_size)
{
	if(size + data_size > CACHE_SIZE)
		return 1;
	return 0;
}

int cache_random::cache_find(string url)
{
	if(cache.count(url) == 0)
		return 0;
	return 1;
}

int cache_random::cache_fetch(string url, string &value)
{
	if(cache_find(url))
	{
		value = cache[url];
		return 1;
	}
	return 0;
}

int cache_random::cache_insert(string url, string value)
{
	int data_size = value.length();
	if( (data_size > CACHE_SIZE) || (data_size == 0 && CACHE_SIZE==0))
		return 0;
	while(cache_isFull(data_size))
	{
		cache_remove(cache_decideReplace());
	}

	cache[url] = value;
	size = size + data_size;
	random_queue.push_back(url);
	return 1;
}

int cache_random::cache_remove(int url_index)
{
	string temp;
	if (url_index < random_queue.size()){
		string url = random_queue[url_index];
		if(cache_fetch(url, temp) == 0)
			return 0;
		size = size - temp.length();
		cache.erase(url);
		random_queue.erase(random_queue.begin() + url_index);
		return 1;
	}
	return 0;
}

int cache_random::cache_decideReplace()
{
	int index = int (rand() % random_queue.size()-1);
	return index;
}
