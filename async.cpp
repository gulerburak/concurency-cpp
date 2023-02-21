#include <iostream>
#include <future>

int count(int x)
{
    for (int i = 0; i < x; i++)
    {
        std::cout << "async counted: " << i << std::endl;
    }
    return 0;
}

int main()
{
    int c = 30;
    std::future<int> asyncFunc = std::async(&count, c);

    // do some work here
    for (int i = 0; i < c; i++)
    {
        std::cout << "main counted: " << i << std::endl;
    }

    int result = asyncFunc.get(); // waits till async function is completed

    return 0;
}