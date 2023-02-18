#include <iostream>
#include <thread>
#include <vector>

int main()
{
    auto lambda = [](int x)
    {
        std::cout << "This thread is " << std::this_thread::get_id() << std::endl;
        std::cout << " Argument is: " << x << std::endl;
    };

    std::vector<std::jthread> jthreads; // auto joining threads, needs g++20

    for (int i = 0; i < 10; i++)
    {
        jthreads.push_back(std::jthread(lambda, i));
    }

    std::cout << "Hi from main thread!" << std::endl;

    return 0;
}