namespace cpp hellons

struct response
{
1:string document
}

service HelloWorld
{

response request(1:string url)

/* Stop the server */
oneway void shutdown()
}
