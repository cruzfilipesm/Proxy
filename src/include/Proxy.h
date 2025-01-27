//
// Created by filipe-cruz on 27/01/25.
//

#ifndef PROXY_H
#define PROXY_H

#include <iostream>
#include <memory>
#include <thread>
#include <utility>
#include <zmq.hpp>

class IProxy {
public:
    virtual ~IProxy() = default;
    virtual void run() = 0;
};

class ReqRepProxy : public IProxy {
public:
    explicit ReqRepProxy(zmq::context_t& context, std::string frontEnd, std::string backEnd) :
    context(context), frontEndAddr(std::move(frontEnd)), backEndAddr(std::move(backEnd)){}

    void run() override {
        zmq::socket_t frontend(context, ZMQ_ROUTER);
        frontend.bind(frontEndAddr);

        zmq::socket_t backend(context, ZMQ_DEALER);
        backend.bind(backEndAddr);

        zmq::proxy(frontend, backend);
    }

private:
    zmq::context_t& context;
    std::string frontEndAddr;
    std::string backEndAddr;
};

class PushPullProxy : public IProxy {
public:
    explicit PushPullProxy(zmq::context_t& context, std::string frontEnd, std::string backEnd) :
    context(context), frontEndAddr(std::move(frontEnd)), backEndAddr(std::move(backEnd)) {}

    void run() override {
        zmq::socket_t frontend(context, ZMQ_PULL);
        frontend.bind(frontEndAddr);

        zmq::socket_t backend(context, ZMQ_PUSH);
        backend.bind(backEndAddr);

        zmq::proxy(frontend, backend);
    }

private:
    zmq::context_t& context;
    std::string frontEndAddr;
    std::string backEndAddr;
};

#endif //PROXY_H
