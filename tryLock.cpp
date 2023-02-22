#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

std::mutex gLock;

void job1()
{
    gLock.lock();
    std::cout << "job1 is running" << std::endl;
    gLock.unlock();
}

void job2()
{
    if (gLock.try_lock())
    {
        std::cout << "job2 is running" << std::endl;
        gLock.unlock();
    }
    else
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
        if (gLock.try_lock())
        {
            std::cout << "job2 is running on second try" << std::endl;
            gLock.unlock();
        }
    }
}

int main()
{

    std::thread thread1(job1);
    std::thread thread2(job2);

    thread1.join();
    thread2.join();

    return 0;
}