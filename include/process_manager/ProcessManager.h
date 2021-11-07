#ifndef DISTRIBUTED_SENSORS_PROCESS_MANAGER_H
#define DISTRIBUTED_SENSORS_PROCESS_MANAGER_H

#include <unordered_map>
#include <iostream>

#include <boost/process.hpp>

class ProcessManager
{
public:
    ProcessManager() = default;

    void SpawnProcess(const std::string &command, const uint64_t id);

    void TerminateProcess(const uint64_t &id);
    void TerminateAll();

    size_t CountProcesses();

private:
    std::unordered_map<uint64_t, boost::process::child> processes_;
};

#endif