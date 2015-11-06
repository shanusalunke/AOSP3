#ifndef random_cache_H
#define random_cache_H

#ifndef CACHE_MAX_SIZE
#define CACHE_MAX_SIZE 1048576
#endif

#include <string>
#include <map>
#include <vector>

using namespace std;

class cache_random
{
  int CACHE_SIZE;
  int size;
  map<string,string> cache;
  vector<string> random_queue = vector<string>(50);

public:
/*Constructor*/
  cache_random();
  cache_random(int max);

  void cache_set_size(int max);
  int cache_fetch(string url, string &value);
  int cache_insert(string url, string value);

private:
  int cache_isFull(int data_size);
	int cache_find(string url);
	int cache_remove(int url_index);
	int cache_decideReplace();
  void cache_set_max(int max);
};

#endif
