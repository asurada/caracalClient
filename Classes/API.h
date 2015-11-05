//
//  API.h
//  
//
//  Created by Yan Wei on 2015/10/29.
//
//

#ifndef ____API__
#define ____API__

#include <stdio.h>
#include "network/HttpClient.h"
//#include "rapidjson/document.h"
//#include "rapidjson/stringbuffer.h"
//#include "rapidjson/writer.h"
//#include "rapidjson/stringbuffer.h"
#include "rapidjson/reader.h"

#include <iostream>

using namespace cocos2d::network;
using namespace rapidjson;
using namespace std;


class API
{
    private:

        void receiveRequest(char* response);

    public:

        void request(std::string url,HttpRequest::Type type);
        void parseData(HttpResponse* response);
        char* convertToChar(HttpResponse* response);
        ~API();
};



#endif /* defined(____API__) */
