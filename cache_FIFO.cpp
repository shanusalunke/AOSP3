#include <iostream>
#include "cache_FIFO.h"

cache_fifo::cache_fifo()
{
	CACHE_SIZE = CACHE_MAX_SIZE;
	size = 0;
}

cache_fifo::cache_fifo(int max)
{
	CACHE_SIZE = max;
	size = 0;
}

void cache_fifo::cache_set_max(int max)
{
	CACHE_SIZE = max;
}

int cache_fifo::cache_isFull(int data_size)
{
	if(size + data_size > CACHE_SIZE)
		return 1;
	return 0;
}

int cache_fifo::cache_find(string url)
{
	if(cache.count(url) == 0)
		return 0;
	return 1;
}

int cache_fifo::cache_fetch(string url, string &value)
{
	if(cache_find(url))
	{
		value = cache[url];
		return 1;
	}
	return 0;
}

int cache_fifo::cache_insert(string url, string value)
{
	int data_size = value.length();
	if(data_size > CACHE_SIZE)
		return 0;
	while(cache_isFull(data_size))
	{
		cache_remove(cache_decideReplace());
	}

	cache[url] = value;
	size = size + data_size;
	fifo_queue.push(url);
	return 1;
}

int cache_fifo::cache_remove(string url)
{
	string temp;
	if(cache_fetch(url, temp) == 0)
		return 0;
	size = size - temp.length();
	cache.erase(url);
	fifo_queue.pop();
	return 1;
}

string cache_fifo::cache_decideReplace()
{
	return fifo_queue.front();
}
