namespace cpp hellons

/*
0 - cache hit
1 - cache miss because couldn't return curl
2 - cache miss because couldn't find in cache
3 - cache miss because document couldn't fit in the cache
*/

struct response
{
1:string document
2:int cache_hit_flag
}

service HelloWorld
{

response request(1:string url)

/* Stop the server */
oneway void shutdown()
}
