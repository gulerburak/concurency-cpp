#include <iostream>
#include <future>
#include <thread>
#include <chrono>

bool backgroundDownload() // background video downloader
{
    int videoDuration = 5000;

    while (videoDuration > 0) // download will finish in 2 seconds
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        videoDuration -= 2500;
    }

    return true;
}

int main()
{
    std::future<bool> backgroundThread = std::async(std::launch::async, backgroundDownload);
    std::future_status downloadStatus;

    int videoDuration = 5000; // 5 seconds

    bool finishFlag = true;

    while (videoDuration) // main video player
    {
        std::cout << "video is playing: " << 5000 - videoDuration << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // play tick for player

        downloadStatus = backgroundThread.wait_for(std::chrono::milliseconds(1)); // check if download is complete

        if (downloadStatus == std::future_status::ready && finishFlag)
        {
            std::cout << "video is downloaded at time " << 5000 - videoDuration << std::endl;
            finishFlag = false;
        }

        videoDuration -= 100;
    }

    std::cout << "video is played" << std::endl;

    return 0;
}