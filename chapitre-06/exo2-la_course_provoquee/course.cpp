#include "NKThreading/NKThread.h"

#include <iostream>

#include <vector>

int compteur = 0;

void incrementer()

{

    for (int i = 0; i < 1000000; ++i)

    {

        compteur += 1;

    }

}

int main()

{

    // Test with eight threads

    compteur = 0;

    std::vector<NkThread> threads;

    for (int i = 0; i < 8; ++i)

    {

        threads.emplace_back(incrementer);

    }

    for (auto& thread : threads)

    {

        thread.Join();

    }

    std::cout << "Eight threads: " << compteur << '\n';

    std::cout << "Expected: 8000000\n";

    // Test with one thread

    compteur = 0;

    incrementer();

    std::cout << "One thread: " << compteur << '\n';

    std::cout << "Expected: 1000000\n";

    return 0;

}
