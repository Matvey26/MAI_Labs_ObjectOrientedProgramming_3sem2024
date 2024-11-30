#pragma once

#include "IGameObjectObserver.hpp"
#include <string>


class LogGameObjectObserver : public IGameObjectObserver {
private:
    std::string path_to_logfile_;

public:
    LogGameObjectObserver(const std::string& path_to_logfile);

    void Update(const std::string& message) override;
};


class PrintGameObjectObserver : public IGameObjectObserver {
public:
    PrintGameObjectObserver();

    void Update(const std::string& message) override;
};