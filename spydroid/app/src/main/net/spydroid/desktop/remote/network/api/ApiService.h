#ifndef API_SERVICE_H
#define API_SERVICE_H

#include <cstddef>
#include <string>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
void ApiService();

#endif // API_SERVICE_H