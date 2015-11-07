#include <iostream>
#include "cache_LFU.h"

cache_lfu::cache_lfu()
{
	CACHE_SIZE = CACHE_MAX_SIZE;
	size = 0;
  min.min_num = 100;
  min.url_lfu = "";
}

cache_lfu::cache_lfu(int max)
{
	CACHE_SIZE = max;
	size = 0;
  min.min_num = 100;
  min.url_lfu="";
}

void cache_lfu::cache_set_max(int max)
{
	CACHE_SIZE = max;
}

void cache_lfu::cache_updateMin(){
  map<string, data>::iterator it;
  min.min_num = 100;
  for ( it = cache.begin(); it != cache.end(); it++ )
  {
    if (it->second.flag < min.min_num){
      min.min_num = it->second.flag;
      min.url_lfu = it->first;
    }
  }
}

int cache_lfu::cache_isFull(int data_size)
{
	if(size + data_size > CACHE_SIZE)
		return 1;
	return 0;
}

int cache_lfu::cache_find(string url)
{
	if(cache.count(url) == 0)
		return 0;
	return 1;
}

int cache_lfu::cache_fetch(string url, string &value)
{
  struct data val;
	if(cache_find(url))
	{
		val = cache[url];
    value = val.doc;
    val.flag++;
    if(val.flag < min.min_num)
     {
      min.min_num = val.flag;
      min.url_lfu = url;
     }
    cache[url] = val;
		return 1;
	}
	return 0;
}

int cache_lfu::cache_insert(string url, string value)
{
	int data_size = value.length();
	if(data_size > CACHE_SIZE)
		return 0;
	while(cache_isFull(data_size))
	{
    cout << "In while loop ...\n";
  //  cout << "cachesize" << CACHE_SIZE << endl;
  //  cout << "data seize" << data_size << endl;
		cache_remove(cache_decideReplace());
    //Update min with next lease from map
    cache_updateMin();
	}
  struct data val;
  val.doc = value;
  val.flag = 1;
  if(val.flag < min.min_num)
   {
    min.min_num = val.flag;
    min.url_lfu = url;

   }
	cache[url] = val;
	size = size + data_size;
	return 1;
}

int cache_lfu::cache_remove(string url)
{
	string temp;
	if(cache_fetch(url, temp) == 0)
		return 0;
	size = size - temp.length();
	cache.erase(url);
	return 1;
}

string cache_lfu::cache_decideReplace()
{
	return min.url_lfu;
}
