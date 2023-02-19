#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

std::mutex gLock;
std::condition_variable gConditionVariable;

int main()
{
    int result = 0;
    bool notified = false; // to notify the work has been done by working thread

    // reporter thread
    std::thread reporter([&]
                         {
        std::unique_lock<std::mutex> lock(gLock);

            std::cout << "Waiting to work to be done."<< std::endl;

        if(!notified){
            gConditionVariable.wait(lock);
        }
        std::cout << "Reporter, result is: " << result << std::endl; });

    // worker thread
    std::thread worker([&]
                       {
            std::unique_lock<std::mutex> lock(gLock);

            // got the lock, do the work
            result = 42 + 1 + 7;
            // work is completed

            notified = true;
            std::cout << "Work complete, waiting 5 seconds."<< std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
            std::cout << "Wait time is up." << std::endl;

            // wake the waiting thread
            gConditionVariable.notify_one(); });

    // join threads before program ends
    reporter.join();
    worker.join();

    std::cout << "Program completed!" << std::endl;
    return 0;
}