#ifndef ADD_SERVICE_H/* Include guard */
#define ADD_SERVICE_H
/**
 * Service to add image
 */

/**
 * @brief posts document and word. Get Code from https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
 * 
 * @param curl instance of the curl
 * @param url service URL to do the Post
 * @param filename file to send
 * @return int CURLcode of the process 
 */
char *add_image(CURL *curl, char *url, char *path, char *filename, char *number);
#endif