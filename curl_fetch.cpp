#include "curl_fetch.h"

/* This function is registered as a callback with CURL.  As the data
   from the requested webpage is returned in chunks, write_data is
   called with each chunk.  */
size_t write_data(void *buffer, size_t size,
                         size_t nmemb, wd_in *userp) {
  struct wd_in *wdi = userp;

  while(wdi->len + (size * nmemb) >= wdi->size) {
    /* check for realloc failing in real code. */
    wdi->data = (char*) realloc(wdi->data, wdi->size*2);
    wdi->size*=2;
  }

  memcpy(wdi->data + wdi->len, buffer, size * nmemb);
  wdi->len+=size*nmemb;

  return size * nmemb;
}

int fetch_url(std::string input_url, std::string& curl_return) {
  CURL *curl;
  CURLcode res;
  struct wd_in wdi;
  memset(&wdi, 0, sizeof(wdi));

  /* Get a curl handle.  Each thread will need a unique handle. */
  curl = curl_easy_init();
  if(NULL != curl) {
    wdi.size = 1024;
    /* Check for malloc failure in real code. */
    wdi.data = (char*) malloc(wdi.size);
    /*Allow redirection*/
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    /*Timeout for connections, in seconds*/
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
    /* Set the URL for the operation. */
    curl_easy_setopt(curl, CURLOPT_URL, input_url.c_str());
    /* "write_data" function to call with returned data. */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    /* userp parameter passed to write_data. */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &wdi);
    /* Actually perform the query. */
    res = curl_easy_perform(curl);
    /* Check the return value and do whatever. */

    /* Clean up after ourselves. */
    curl_easy_cleanup(curl);
  }
  else {
    fprintf(stderr, "Error: could not get CURL handle.\n");
    exit(EXIT_FAILURE);
  }

  /* Now wdi.data has the data from the GET and wdi.len is the length
     of the data available, so do whatever. */

  /* Write the content to stdout. */
  curl_return.assign(wdi.data, wdi.len);
  // printf("\nSize : %zu",wdi.size);
  // printf("\tLength : %zu \n",wdi.len);
  free(wdi.data);
  /* cleanup wdi.data buffer. */
  return res;
}
