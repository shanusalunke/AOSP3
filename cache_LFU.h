#ifndef cache_LFU_H
#define cache_LFU__H

#ifndef CACHE_MAX_SIZE
#define CACHE_MAX_SIZE 1048576
#endif

#include <string>
#include <map>
#include <queue>

using namespace std;

struct data
{
string doc;
int flag=0;
};

class cache_lfu
{
  int CACHE_SIZE;
  int size;
  map<string,data> cache;
  struct min_{
    int min_num;
    std::string url_lfu;
  }min;

public:
/*Constructor*/
  cache_lfu();
  cache_lfu(int max);

  void cache_set_size(int max);
  int cache_fetch(string url, string &value);
  int cache_insert(string url, string value);

private:
  void cache_updateMin();
  int cache_isFull(int data_size);
	int cache_find(string url);
	int cache_remove(string url);
	string cache_decideReplace();
  void cache_set_max(int max);
};

#endif
