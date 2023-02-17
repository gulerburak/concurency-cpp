#include <iostream>
#include <thread>

int main()
{
    auto lambda = [](int x)
    {
        std::cout << "Test function run" << std::endl;
        std::cout << "Argument is: " << x << std::endl;
    };

    std::thread myThread(lambda, 100);
    myThread.join(); // block the main thread until myThread finishes
    // if it does not wait, core dumped

    std::cout << "Hi from main thread!" << std::endl;
    return 0;
}