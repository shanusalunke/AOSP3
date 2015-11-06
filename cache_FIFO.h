#ifndef fifo_cache_H
#define fifo_cache_H

#ifndef CACHE_MAX_SIZE
#define CACHE_MAX_SIZE 1048576
#endif

#include <string>
#include <map>
#include <queue>

using namespace std;

class cache_fifo
{
  int CACHE_SIZE;
  int size;
  map<string,string> cache;
  queue<string> fifo_queue;

public:
/*Constructor*/
  cache_fifo();
  cache_fifo(int max);

  void cache_set_size(int max);
  int cache_fetch(string url, string &value);
  int cache_insert(string url, string value);

private:
  int cache_isFull(int data_size);
	int cache_find(string url);
	int cache_remove(string url);
	string cache_replace();
};

#endif
