#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <memory>
#include <chrono>

#include <SFML/Graphics.hpp>

static std::vector<int> grid; // global grid
std::vector<std::unique_ptr<sf::Shape>> shapes;
bool isRunning = true;

void update_grid(int x, int y)
{
    while (isRunning)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        grid[y * 2 + x] = rand() % 4;
    }
}

int main()
{
    grid.reserve(4); // initialize 4 places
    std::fill(begin(grid), end(grid), 0);
    for (int x = 0; x < 2; x++)
    {
        for (int y = 0; y < 2; y++)
        {
            // create circle with radius 200px
            shapes.push_back(std::make_unique<sf::CircleShape>(200.0f));
        }
    }

    // initialize threads
    std::vector<std::thread> threads;
    for (int x = 0; x < 2; x++)
    {
        for (int y = 0; y < 2; y++)
        {
            threads.push_back(std::thread(update_grid, x, y));
        }
    }

    sf::RenderWindow window(sf::VideoMode(800, 800), "Threads with SFML");

    // main loop
    while (window.isOpen() && isRunning)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                isRunning = false;
            }
        }

        window.clear();
        for (int x = 0; x < 2; x++)
        {
            for (int y = 0; y < 2; y++)
            {
                // set the position
                shapes[y * 2 + x]->setPosition(x * 400, y * 400);

                // update the color with new values
                if (0 == grid[y * 2 + x])
                {
                    shapes[y * 2 + x]->setFillColor(sf::Color::Red);
                }
                else if (1 == grid[y * 2 + x])
                {
                    shapes[y * 2 + x]->setFillColor(sf::Color::Green);
                }
                else if (2 == grid[y * 2 + x])
                {
                    shapes[y * 2 + x]->setFillColor(sf::Color::Blue);
                }
                else if (3 == grid[y * 2 + x])
                {
                    shapes[y * 2 + x]->setFillColor(sf::Color::White);
                }
            }
        }

        // draw the shapes
        for (auto &shape : shapes)
        {
            window.draw(*shape);
        }
        window.display();
    }

    // join threads before program ends
    for (auto &thread : threads)
    {
        thread.join();
    }

    std::cout << "Terminating..." << std::endl;

    return 0;
}