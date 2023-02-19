#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex gLock;

static int shared_value = 0;

void increment()
{
    gLock.lock();
    // critical region starts, only one thread can access this block
    shared_value++;

    gLock.unlock(); // critical region ends
}

int main()
{
    auto lambda = [](int x)
    {
        std::cout << "This thread is " << std::this_thread::get_id() << std::endl;
        std::cout << " Argument is: " << x << std::endl;
    };

    std::vector<std::thread> threads;

    for (int i = 0; i < 1000; i++)
    {
        threads.push_back(std::thread(increment));
    }

    for (int i = 0; i < 1000; i++)
    {
        threads[i].join();
    }

    std::cout << "shared value is: " << shared_value << std::endl;
    // shared value exactly will be 1000
    return 0;
}