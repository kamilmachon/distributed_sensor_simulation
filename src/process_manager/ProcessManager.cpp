#include <process_manager/ProcessManager.h>

void ProcessManager::SpawnProcess(const std::string &command, const uint64_t id)
{
    boost::process::child process(command);

    if (processes_.find(id) != std::end(processes_))
    {
        TerminateProcess(id);
    }
    processes_[id] = std::move(process);
}

void ProcessManager::TerminateProcess(const uint64_t &id)
{
    try
    {
        if (!processes_[id].running())
        {
            std::cout << "terminating process with id " << id << '\n';
            processes_.at(id).terminate();
        }
    }
    catch (const std::out_of_range &oor)
    {
        std::cerr << "Process id does not exists: " << oor.what() << '\n';
    }
}

void ProcessManager::TerminateAll()
{
    for (auto &process : processes_)
    {
        process.second.terminate(); //TODO: check results
    }
}

size_t ProcessManager::CountProcesses()
{
    return processes_.size();
}
