#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

char user_q1[20] = {};
char user_q2[20] = {};
char user_q3[20] = {};
char user_q4[20] = {};

size_t curl_cbfn(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;

    printf("user pointer: %p\n", userp);
    printf("\trealsize\\size\\nmemb %lu\\%lu\\%lu\n", realsize, size, nmemb);
    printf("\tcontents length: %lu\n", strlen((char *)contents));
    printf("\tcontents: %s\n", (char *)contents);

    return realsize;
}

int curl_error(CURLcode err) {
    // More about CURLcode: https://curl.haxx.se/libcurl/c/libcurl-errors.html
    if (err != CURLE_OK) {
        printf("%s(%d) CURLE_xxx: error %d\n", __FUNCTION__, __LINE__, err);
        return err;
    }
    //printf("%s(%d) CURLE_OK: All fine. Proceed as usual\n", __FUNCTION__, __LINE__);
    return 0;
}

int curl_get_xN() {
    int loop, xN = 3;
    CURL *curl_easy;
    CURLcode res;
    char url[] = "https://demo6460359.mockable.io/tasks_get/v1/users?name=napat&lastname=roo";
    curl_easy = curl_easy_init();
    if (curl_easy == NULL) {
        printf("%s(%d) curl_easy_init error: something went wrong %p\n", __FUNCTION__, __LINE__, curl_easy);
        return -1;
    }
    // set callback fn
    curl_easy_setopt(curl_easy, CURLOPT_WRITEFUNCTION, curl_cbfn);
    // set user pointer pass to callback fn
    curl_easy_setopt(curl_easy, CURLOPT_WRITEDATA, (void *)user_q1);
    // set url
    curl_easy_setopt(curl_easy, CURLOPT_URL, url);
    // set http_get
    curl_easy_setopt(curl_easy, CURLOPT_HTTPGET, 1L);

    printf("%s(%d) begin: %s----------------------------------------\n", __FUNCTION__, __LINE__, url);
    for(loop = 0; loop < xN; loop++) {
        // get away #n
        res = curl_easy_perform(curl_easy);
    }
    printf("%s(%d) end----------------------------------------\n", __FUNCTION__, __LINE__);

    // clean: MUST CALL cleanup when use curl_easy_init()
    curl_easy_cleanup(curl_easy);

    return curl_error(res);
}

int curl_post_json_xN() {
    int loop, xN = 3;
    CURL *curl_easy;
    CURLcode res;
    char url[] = "https://demo6460359.mockable.io/tasks_postjson/v1/users";
    char post_data[] = "username=newuser&password=newpasswd&msg=test&msisdn=9999999999&tagname=Demo&shortcode=8888&telcoId=5&dnRequired=false";
    curl_easy = curl_easy_init();
    if (curl_easy == NULL) {
        printf("%s(%d) curl_easy_init error: something went wrong %p\n", __FUNCTION__, __LINE__, curl_easy);
        return -1;
    }

    // set callback fn
    curl_easy_setopt(curl_easy, CURLOPT_WRITEFUNCTION, curl_cbfn);
    // set user pointer pass to callback fn
    curl_easy_setopt(curl_easy, CURLOPT_WRITEDATA, (void *)user_q2);
    // set url
    curl_easy_setopt(curl_easy, CURLOPT_URL, url);
    // post data to the server without having libcurl do a default strlen() to measure the data size
    curl_easy_setopt(curl_easy, CURLOPT_POSTFIELDSIZE, (long)strlen(post_data));
    // set data to post
    curl_easy_setopt(curl_easy, CURLOPT_POSTFIELDS, post_data);

    printf("%s(%d) begin: %s----------------------------------------\n", __FUNCTION__, __LINE__, url);
    for (loop = 0; loop < xN; loop++) {
        // post away
        res = curl_easy_perform(curl_easy);
    }
    printf("%s(%d) end----------------------------------------\n", __FUNCTION__, __LINE__);

    // clean: MUST CALL cleanup when use curl_easy_init()
    curl_easy_cleanup(curl_easy);

    return curl_error(res);
}

int curl_post_xml_xN() {
    int loop, xN = 3;
    CURL *curl_easy;
    CURLcode res;
    char url[] = "https://demo6460359.mockable.io/tasks_postxml/v1/users";
    char post_data[] = "<?xml version=\"1.0\" encoding=\"utf-8\"?><Person><ID>1</ID><Name>Ana Conda</Name><Email>a.conda@gmail.com</Email><Country>India</Country></Person>";
    struct curl_slist *headers = NULL;    

    curl_easy = curl_easy_init();
    if (curl_easy == NULL) {
        printf("%s(%d) curl_easy_init error: something went wrong %p\n", __FUNCTION__, __LINE__, curl_easy);
        return -1;
    }

    // set header
    headers = curl_slist_append(headers, "Content-Type: text/xml");    
    curl_easy_setopt(curl_easy, CURLOPT_HTTPHEADER, headers);
    // set callback fn
    curl_easy_setopt(curl_easy, CURLOPT_WRITEFUNCTION, curl_cbfn);
    // set user pointer pass to callback fn
    curl_easy_setopt(curl_easy, CURLOPT_WRITEDATA, (void *)user_q3);
    // set url
    curl_easy_setopt(curl_easy, CURLOPT_URL, url);
    // post data to the server without having libcurl do a default strlen() to measure the data size
    curl_easy_setopt(curl_easy, CURLOPT_POSTFIELDSIZE, (long)strlen(post_data));
    // set data to post
    curl_easy_setopt(curl_easy, CURLOPT_POSTFIELDS, post_data);

    printf("%s(%d) begin: %s----------------------------------------\n", __FUNCTION__, __LINE__, url);
    for (loop = 0; loop < xN; loop++) {
        // post away
        res = curl_easy_perform(curl_easy);
    }
    printf("%s(%d) end----------------------------------------\n", __FUNCTION__, __LINE__);

    // clean header
    curl_slist_free_all(headers);
    // clean: MUST CALL cleanup when use curl_easy_init()
    curl_easy_cleanup(curl_easy);

    return curl_error(res);
}

int curl_post_appxwwwformurlencoded_xN() {
    int loop, xN = 3;
    CURL *curl_easy;
    CURLcode res;
    char url[] = "https://demo6460359.mockable.io/tasks_post-x-www-form-urlencoded/v1/compareface";
    char post_data[] = "{\"img1base64\":\"xxxxxx\",\"img2base64\":\"yyyyyy\"}";
    struct curl_slist *headers = NULL;

    curl_easy = curl_easy_init();
    if (curl_easy == NULL) {
        printf("%s(%d) curl_easy_init error: something went wrong %p\n", __FUNCTION__, __LINE__, curl_easy);
        return -1;
    }

    // set header
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    curl_easy_setopt(curl_easy, CURLOPT_HTTPHEADER, headers);
    // set callback fn
    curl_easy_setopt(curl_easy, CURLOPT_WRITEFUNCTION, curl_cbfn);
    // set user pointer pass to callback fn
    curl_easy_setopt(curl_easy, CURLOPT_WRITEDATA, (void *)user_q4);
    // set url
    curl_easy_setopt(curl_easy, CURLOPT_URL, url);
    // post data to the server without having libcurl do a default strlen() to measure the data size
    curl_easy_setopt(curl_easy, CURLOPT_POSTFIELDSIZE, (long)strlen(post_data));
    // set data to post
    curl_easy_setopt(curl_easy, CURLOPT_POSTFIELDS, post_data);

    printf("%s(%d) begin: %s----------------------------------------\n", __FUNCTION__, __LINE__, url);
    for (loop = 0; loop < xN; loop++) {
        // post away
        res = curl_easy_perform(curl_easy);
    }
    printf("%s(%d) end----------------------------------------\n", __FUNCTION__, __LINE__);

    // clean header
    curl_slist_free_all(headers);
    // clean: MUST CALL cleanup when use curl_easy_init()
    curl_easy_cleanup(curl_easy);

    return curl_error(res);
}

int main(int argc, char *argv[]) {
    curl_global_init(CURL_GLOBAL_ALL);

    printf("user_q1 %p\n", user_q1);
    printf("user_q2 %p\n", user_q2);
    printf("user_q3 %p\n", user_q3);
    printf("user_q3 %p\n", user_q4);

    curl_get_xN();
    curl_post_json_xN();
    curl_post_xml_xN();
    curl_post_appxwwwformurlencoded_xN();
    return 0;
}
