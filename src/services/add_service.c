#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "add_service.h"
#include "encode_b64.h"
#define MAX 100

struct memory
{
  char *response;
  size_t size;
};

static size_t mem_function(void *data, size_t size, size_t nmemb, void *userp)
 {
   size_t realsize = size * nmemb;
   struct memory *mem = (struct memory *)userp;
 
   char *ptr = realloc(mem->response, mem->size + realsize + 1);
   if(ptr == NULL)
     return 0;  /* out of memory! */
 
   mem->response = ptr;
   memcpy(&(mem->response[mem->size]), data, realsize);
   mem->size += realsize;
   mem->response[mem->size] = 0;
 
   return realsize;
 }

 char* upPhoto(CURL *curl, char *url, curl_mime *form ){
    
    CURLcode res;
    struct curl_slist *headerlist = NULL;
    static const char head[] = "Expect:";

    headerlist = curl_slist_append(headerlist, head);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);

    struct memory chunk = {0};
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, mem_function);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    
    
    curl_mime_free(form);
    curl_slist_free_all(headerlist);
    return chunk.response;

 }




char *add_image(CURL *curl, char *url, char *path,char *filename, char *number){


    FILE* image;
    FILE* encoded;
    char* imagePath = (char *)malloc(1 + strlen(path) + strlen(filename));
    sprintf(imagePath,"%s/%s",path,filename);

    char* encodedPath = (char *)malloc(1 + strlen(path) + strlen(filename));
    sprintf(encodedPath,"%s/encoded.txt",path);

    
    encoded=fopen(encodedPath,"w");
    fclose(encoded);
    encoded=fopen(encodedPath,"w+");
    image=fopen(imagePath,"r");
    
    encodeImage(image, encoded);
    fclose(image);
	  fclose(encoded);
    
    

    
    curl_mime *form = NULL;
    curl_mimepart *field = NULL;
    form = curl_mime_init(curl);
    field = curl_mime_addpart(form);
    curl_mime_name(field, "file");
    curl_mime_filedata(field, encodedPath);
    field = curl_mime_addpart(form);
    curl_mime_name(field, "filename");
    curl_mime_data(field, filename, CURL_ZERO_TERMINATED);
    field = curl_mime_addpart(form);
    curl_mime_name(field, "npixel");
    curl_mime_data(field, number, CURL_ZERO_TERMINATED);
    char *response = upPhoto(curl, url, form );

    return response;



   
}