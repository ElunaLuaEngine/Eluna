#ifndef ELUNA_HTTP_MANAGER_H
#define ELUNA_HTTP_MANAGER_H

#include <regex>

#include "libs/httplib.h"
#include "libs/rigtorp/SPSCQueue.h"

struct HttpWorkItem
{
public:
    HttpWorkItem(int funcRef, const std::string& httpVerb, const std::string& url, const std::string& body, const std::string &contentType, const httplib::Headers& headers);

    int funcRef;
    std::string httpVerb;
    std::string url;
    std::string body;
    std::string contentType;
    httplib::Headers headers;
};

struct HttpResponse
{
public:
    HttpResponse(int funcRef, int statusCode, const std::string& body, const httplib::Headers& headers);

    int funcRef;
    int statusCode;
    std::string body;
    httplib::Headers headers;
};


class HttpManager
{
public:
    HttpManager();

    void PushRequest(HttpWorkItem* item);
    void StartHttpWorker();
    void HandleHttpResponses();

private:
    void HttpWorkerThread();
    bool ParseUrl(const std::string& url, std::string& host, std::string& path);
    httplib::Result DoRequest(httplib::Client& client, HttpWorkItem* req, const std::string& path);

    rigtorp::SPSCQueue<HttpWorkItem*> httpWorkQueue;
    rigtorp::SPSCQueue<HttpResponse*> httpResponseQueue;
    std::thread httpWorkerThread;
    bool startedHttpWorkerThread;
    std::atomic_bool httpCancelationToken;
    std::condition_variable httpCondVar;
    std::mutex httpCondVarMutex;
    std::regex parseUrlRegex;
};

#endif // #ifndef ELUNA_HTTP_MANAGER_H
