//
// Created by filipe-cruz on 27/01/25.
//

#ifndef PROXYMANAGER_H
#define PROXYMANAGER_H

#include "Proxy.h"

class ProxyManager {
public:
    ProxyManager() : context(1) {}

    void addProxy(std::unique_ptr<IProxy> proxy) {
        proxies.push_back(std::move(proxy));
    }

    void runAll() {
        for (auto& proxy : proxies) {
            threads.emplace_back(&IProxy::run, proxy.get());
        }
    }

    zmq::context_t& getContext() {
        return context;
    }

private:
    zmq::context_t context;
    std::vector<std::unique_ptr<IProxy>> proxies;
    std::vector<std::jthread> threads;
};

#endif //PROXYMANAGER_H
