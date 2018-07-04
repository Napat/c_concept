
### main.c

``` bash
$ ./output/respapiclient
user_q1 0x603090
user_q2 0x6030b0
user_q3 0x6030d0
user_q3 0x6030f0
curl_get_xN(51) begin----------------------------------------
user pointer: 0x603090
        realsize\size\nmemb 66\1\66
        contents length: 66
        contents: {
 "msg": "Hello World. Today is good day",
 "version": "1.0.0"
}

user pointer: 0x603090
        realsize\size\nmemb 66\1\66
        contents length: 66
        contents: {
 "msg": "Hello World. Today is good day",
 "version": "1.0.0"
}

user pointer: 0x603090
        realsize\size\nmemb 66\1\66
        contents length: 66
        contents: {
 "msg": "Hello World. Today is good day",
 "version": "1.0.0"
}

curl_get_xN(56) end----------------------------------------
curl_post_json_xN(87) begin----------------------------------------
user pointer: 0x6030b0
        realsize\size\nmemb 46\1\46
        contents length: 46
        contents: {
 "msg": "Hello POST.",
 "version": "1.0.1"
}
user pointer: 0x6030b0
        realsize\size\nmemb 46\1\46
        contents length: 46
        contents: {
 "msg": "Hello POST.",
 "version": "1.0.1"
}
user pointer: 0x6030b0
        realsize\size\nmemb 46\1\46
        contents length: 46
        contents: {
 "msg": "Hello POST.",
 "version": "1.0.1"
}
curl_post_json_xN(92) end----------------------------------------
curl_post_xml_xN(128) begin----------------------------------------
user pointer: 0x6030d0
        realsize\size\nmemb 53\1\53
        contents length: 53
        contents: {
 "msg": "Hello POST xml.",
 "version": "1.0.2"
}
user pointer: 0x6030d0
        realsize\size\nmemb 53\1\53
        contents length: 53
        contents: {
 "msg": "Hello POST xml.",
 "version": "1.0.2"
}
user pointer: 0x6030d0
        realsize\size\nmemb 53\1\53
        contents length: 53
        contents: {
 "msg": "Hello POST xml.",
 "version": "1.0.2"
}
curl_post_xml_xN(133) end----------------------------------------
curl_post_appxwwwformurlencoded_xN(172) begin----------------------------------------
user pointer: 0x6030f0
        realsize\size\nmemb 82\1\82
        contents length: 82
        contents: {
 "msg": "tasks_post-x-www-form-urlencoded/v1/compareface",
 "version": "1.0.3"
}
user pointer: 0x6030f0
        realsize\size\nmemb 82\1\82
        contents length: 82
        contents: {
 "msg": "tasks_post-x-www-form-urlencoded/v1/compareface",
 "version": "1.0.3"
}
user pointer: 0x6030f0
        realsize\size\nmemb 82\1\82
        contents length: 82
        contents: {
 "msg": "tasks_post-x-www-form-urlencoded/v1/compareface",
 "version": "1.0.3"
}
curl_post_appxwwwformurlencoded_xN(177) end----------------------------------------
$
```


## References

- [libcurl c api document](https://curl.haxx.se/libcurl/c/)
- [libcurl github](https://github.com/curl/curl/blob/master/docs/INSTALL.md)
- [libcurl example: getinmemory](https://curl.haxx.se/libcurl/c/getinmemory.html)
- [libcurl tutorial](https://curl.haxx.se/libcurl/c/libcurl-tutorial.html)
- [restful tutorial](http://www.drdobbs.com/web-development/restful-web-services-a-tutorial/240169069)

## Userful
- [mocky rest api server support both http/https](https://www.mocky.io/)
- [mockable rest api](https://www.mockable.io/)



