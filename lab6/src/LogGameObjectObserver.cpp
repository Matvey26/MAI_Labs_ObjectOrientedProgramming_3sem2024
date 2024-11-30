#pragma once

#include "../include/LogGameObjectObserver.hpp"

LogGameObjectObserver::LogGameObjectObserver(const std::string& path_to_logfile)
    : path_to_logfile_(path_to_logfile) {}

void LogGameObjectObserver::Update(const std::string& message) {
    // Not implemented
}
