#include <iostream>
#include <thread>
#include <vector>

static int shared_value = 0;

void increment()
{
    shared_value++;
}

int main()
{
    auto lambda = [](int x)
    {
        std::cout << "This thread is " << std::this_thread::get_id() << std::endl;
        std::cout << " Argument is: " << x << std::endl;
    };

    std::vector<std::thread> threads;

    for (int i = 0; i < 100; i++)
    {
        threads.push_back(std::thread(increment));
    }

    for (int i = 0; i < 100; i++)
    {
        threads[i].join();
    }

    std::cout << "shared value is: " << shared_value << std::endl;
    // shared value may not be exactly 100
    // to fix ==> mutex
    return 0;
}