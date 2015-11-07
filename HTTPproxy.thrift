namespace cpp HTTPproxy

/*
0 - cache hit
1 - cache miss because couldn't return curl
2 - cache miss because couldn't find in cache
3 - cache miss because document couldn't fit in the cache
*/

struct response
{
1:string document
2:i32 cache_hit_flag
}

service proxy
{

response request(1:string url)

/* Stop the server */
oneway void shutdown()
}
