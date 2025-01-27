#include "include/ProxyManager.h"
#include "include/CustomAssert.h"

inline const char * getEnvironmentVariable(const char* env) {
    const auto environmentVariable = std::getenv(env);
    const std::string errorMessage = std::string{env} + " not set";
    M_Assert(environmentVariable != nullptr, errorMessage.c_str());
    return environmentVariable;
}

int main() {

    const auto reqRepFrontEnd = getEnvironmentVariable("REQ_REP_FRONTEND");
    const auto reqRepBackEnd = getEnvironmentVariable("REQ_REP_BACKEND");

    const auto pushPullFrontEnd = getEnvironmentVariable("PUSH_PULL_FRONTEND");
    const auto pushPullBackEnd = getEnvironmentVariable("PUSH_PULL_BACKEND");

    ProxyManager manager;

    manager.addProxy(std::make_unique<ReqRepProxy>(manager.getContext(), reqRepFrontEnd, reqRepBackEnd));
    manager.addProxy(std::make_unique<PushPullProxy>(manager.getContext(), pushPullFrontEnd, pushPullBackEnd));

    manager.runAll();

    return 0;
}