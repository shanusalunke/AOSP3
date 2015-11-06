namespace cpp hellons

struct response
{
1:string document
2:bool isCacheHit
}

service HelloWorld
{

response request(1:string url)

/* Stop the server */
oneway void shutdown()
}
