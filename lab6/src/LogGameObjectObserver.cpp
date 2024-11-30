#include "../include/LogGameObjectObserver.hpp"
#include <fstream>

LogGameObjectObserver::LogGameObjectObserver(const std::string& path_to_logfile)
    : path_to_logfile_(path_to_logfile) {}

void LogGameObjectObserver::Update(const std::string& message) {
    std::ofstream log_file;
    log_file.open(path_to_logfile_);

    log_file << message << '\n';
}
