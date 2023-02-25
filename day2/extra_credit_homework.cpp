#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <thread>

// naive approach
int main() {
    // for me windows immediately throttles this 
    // for (;;) {malloc(n)}
    // so I put a sleep there
    // it still only manages to get about 10% memory before windows just doesn't want to give me any more memory :(

    // I found a possible reason in this answer:
    // https://stackoverflow.com/questions/2513505/how-to-get-available-memory-c-g#comment62301379_26639774
    // "programs compiled with MSVC only allow about 2Gb of memory"
    for (;;) {malloc(1000);std::this_thread::sleep_for(std::chrono::nanoseconds(100));}

    return 0;
}