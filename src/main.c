#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <curl/curl.h>
#include "services/add_service.h"

#define MAX 255

int main(int argc, char *argv[])
{

    CURL *curl;
    CURLcode res;
    
    char buffer[500];
    char errorBuffer[500];
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl == NULL) {
        printf("hola");
        return 128;
    }
    bool run = true;
    while (run)
    {
        if(curl){

            char ip_server[MAX];
            printf("Enter server direccion: \n");
            scanf("%s", ip_server);
            

           

            
            char filename[MAX];
            printf("Enter the image name: \n");
            scanf("%s", filename);

            char pixel[MAX];
            printf("Enter the pixels number: \n");
            scanf("%s", pixel);
        

            char *path = "./image";
            char *response = add_image(curl, ip_server, path, filename, pixel);
            printf("%s\n",response);
            free(response);
            
            
            char end[3];
            scanf("%s", end);
            if(end[0] == 'e' && end [1] == 'n' && end[2] == 'd')
            {
                printf("Program Closed.\n");
                run = false;
            }
            printf("\n");
        }
        
    }
    curl_easy_cleanup(curl);
}