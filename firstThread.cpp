#include <iostream>
#include <thread>

void test(int x)
{
    std::cout << "Test function run" << std::endl;
    std::cout << "Argument is: " << x << std::endl;
}

int main()
{
    std::thread myThread(&test, 100);
    myThread.join(); // block the main thread until myThread finishes
    // if it does not wait, core dumped

    std::cout << "Hi from main thread!" << std::endl;
    return 0;
}