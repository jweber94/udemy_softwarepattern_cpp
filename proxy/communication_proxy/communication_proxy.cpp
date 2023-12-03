#include <iostream>

// Proxy interface - communication proxys are created from differenciations of this interface. The underlying implementation of the remote object is done at the server
struct Pingable {
	virtual std::wstring ping(const std::wstring& message) = 0;
};

// basic implementation
struct Pong : Pingable {
	std::wstring ping(const std::wstring& message) override {
		return message + L"pong";
	}
};

// remote proxy - accesses the underlying object via network - the basic implementation is not done within this process
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

struct RemotePong : Pingable
{
    wstring ping(const wstring& message) override
    {
        wstring result;
        http_client client(U("http://localhost:64959/"));
        uri_builder builder(U("/api/values/"));
        builder.append(message);
        auto task = client.request(methods::GET, builder.to_string())
            .then([=](http_response r)
                {
                    return r.extract_string();
                });
        task.wait();
        return task.get();
    }
};

void tryit(Pingable& pp) {
	std::wcout << pp.ping(L"ping") << std::endl;
}

int main() {
    // in process version with the Pong Proxy
	Pong pp;
	for (std::size_t i = 0; i < 3; i++) {
		tryit(pp);
	}

    // remote execution with the communication proxy
    RemotePong pp;
    for (std::size_t i = 0; i < 3; i++) {
        tryit(pp);
    }
} 