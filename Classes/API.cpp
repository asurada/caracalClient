//
//  API.cpp
//  
//
//  Created by Yan Wei on 2015/10/29.
//
//

#include "API.h"

struct MyHandler {
    bool Null() { cout << "Null()" << endl; return true; }
    bool Bool(bool b) { cout << "Bool(" << boolalpha << b << ")" << endl; return true; }
    bool Int(int i) { cout << "Int(" << i << ")" << endl; return true; }
    bool Uint(unsigned u) { cout << "Uint(" << u << ")" << endl; return true; }
    bool Int64(int64_t i) { cout << "Int64(" << i << ")" << endl; return true; }
    bool Uint64(uint64_t u) { cout << "Uint64(" << u << ")" << endl; return true; }
    bool Double(double d) { cout << "Double(" << d << ")" << endl; return true; }
    bool String(const char* str, SizeType length, bool copy) {
        cout << "String(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
    }
    bool StartObject() { cout << "StartObject()" << endl; return true; }
    bool Key(const char* str, SizeType length, bool copy) {
        cout << "Key(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
    }
    bool EndObject(SizeType memberCount) { cout << "EndObject(" << memberCount << ")" << endl; return true; }
    bool StartArray() { cout << "StartArray()" << endl; return true; }
    bool EndArray(SizeType elementCount) { cout << "EndArray(" << elementCount << ")" << endl; return true; }
};


void API::request(std::string url,HttpRequest::Type type){
    HttpRequest* request = new HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(type);
    request->setResponseCallback([this](HttpClient* client, HttpResponse* response){
        char* strRpns = convertToChar(response);
        
        this->receiveRequest(strRpns);
    });
    request->setTag("request test1");
    HttpClient::getInstance()->send(request);
    request->release();
}


void API::receiveRequest(char* response){
    MyHandler handler;
    Reader reader;
    StringStream ss(response);
    reader.Parse(ss, handler);
    
}


void API::parseData(HttpResponse* response){
//    Document document;
//    document.Parse(convertToChar(response));
}


char* API::convertToChar(HttpResponse* response){
    std::vector<char> * buffer = response->getResponseData();
    char * concatenated = (char *) malloc(buffer->size() + 1);
    std::string s2(buffer->begin(), buffer->end());
    strcpy(concatenated, s2.c_str());
    return concatenated;
}

