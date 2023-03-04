#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <ctime>

using namespace std;

struct Subscription {
    uint64_t requestId;
    uint32_t subscriptionId;
    uint32_t interval;
    // add other subscription-related fields as required
};

class E2Agent {
public:
    void handleSubscriptionRequest(const map<string, string>& requestParams) {
        // extract the required parameters from the request
        uint64_t requestId = stoull(requestParams.at("requestId"));
        uint32_t subscriptionId = stoi(requestParams.at("subscriptionId"));
        uint32_t interval = stoi(requestParams.at("interval"));

        // create a new subscription object
        Subscription sub = { requestId, subscriptionId, interval };

        // add the subscription to the list of active subscriptions
        subscriptions.push_back(sub);

        // send a subscription response
        map<string, string> responseParams = {
            { "requestId", to_string(requestId) },
            { "subscriptionId", to_string(subscriptionId) },
            { "interval", to_string(interval) },
            { "timestamp", to_string(getCurrentTime()) }
        };

        sendSubscriptionResponse(responseParams);
    }

private:
    vector<Subscription> subscriptions;

    uint64_t getCurrentTime() {
        auto now = chrono::system_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
    }

    void sendSubscriptionResponse(const map<string, string>& responseParams) {
        // send the response to the RIC instance that sent the subscription request
        // use your own implementation of the E2 interface here
        // for example, using a socket connection to the RIC instance
        // and sending a message containing the response parameters
    }
};

int main() {
    // assume that the E2 agent receives a subscription request from the RIC instance
    // parse the request parameters into a map
    map<string, string> requestParams = {
        { "requestId", "12345" },
        { "subscriptionId", "67890" },
        { "interval", "5000" }
        // add other request parameters as required
    };

    E2Agent e2Agent;
    e2Agent.handleSubscriptionRequest(requestParams);

    return 0;
}