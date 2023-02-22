# Concurency on C++

Example code pieces to explore concurency on C++.

Build:
`g++ -std=c++20 jthreads.cpp -o prog`

Run:
`./prog`

## For SFML example

`sudo apt install libsfml-*`

Then,

`g++ -std=c++20 sfmlGrid.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system`

## Thread Sanitizer
To detect data races, use sanitizer

`g++ -fsanitize=thread -std=c++20 dataRace.cpp -o prog`

Credits [Mike Shah](https://www.youtube.com/playlist?list=PLvv0ScY6vfd_ocTP2ZLicgqKnvq50OCXM).