

#include "NKThreading/NkThread.h"

#include "NKThreading/NkMutex.h"

#include "NKCore/NkAtomic.h"

#include <array>

#include <chrono>

#include <iostream>

#include <vector>

using nkentseu::threading::NkThread;

using nkentseu::threading::NkMutex;

using nkentseu::threading::NkScopedLockMutex;

using nkentseu::NkAtomicInt;

constexpr int NB_THREADS = 8;

constexpr int REPETITIONS = 1000000;

constexpr int EXPECTED = NB_THREADS * REPETITIONS;

int compteur = 0;

NkMutex mutex;

NkAtomicInt atomique = 0;

void incrementerSansProtection()

{

    for (int i = 0; i < REPETITIONS; ++i)

        compteur++;

}

void incrementerMutex()

{

    for (int i = 0; i < REPETITIONS; ++i)

    {

        NkScopedLockMutex lock(mutex);

        compteur++;

    }

}

void incrementerAtomique()

{

    for (int i = 0; i < REPETITIONS; ++i)

        atomique.FetchAdd(1);

}

template <typename Fonction>

long long executer(Fonction fonction)

{

    auto debut = std::chrono::steady_clock::now();

    std::vector<NkThread> threads;

    for (int i = 0; i < NB_THREADS; ++i)

        threads.emplace_back(fonction);

    for (auto& thread : threads)

        thread.Join();

    auto fin = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(

        fin - debut).count();

}

long long executerLocal()

{

    std::array<int, NB_THREADS> totaux{};

    auto debut = std::chrono::steady_clock::now();

    std::vector<NkThread> threads;

    for (int i = 0; i < NB_THREADS; ++i)

    {

        threads.emplace_back([i, &totaux]()

        {

            int local = 0;

            for (int j = 0; j < REPETITIONS; ++j)

                local++;

            totaux[i] = local;

        });

    }

    for (auto& thread : threads)

        thread.Join();

    int total = 0;

    for (int valeur : totaux)

        total += valeur;

    auto fin = std::chrono::steady_clock::now();

    std::cout << "Local total: " << total << '\n';

    return std::chrono::duration_cast<std::chrono::milliseconds>(

        fin - debut).count();

}

int main()

{

    long long temps[4][3]{};

    int totaux[4]{};

    for (int essai = 0; essai < 3; ++essai)

    {

        compteur = 0;

        temps[0][essai] = executer(incrementerSansProtection);

        totaux[0] = compteur;

        compteur = 0;

        temps[1][essai] = executer(incrementerMutex);

        totaux[1] = compteur;

        atomique = 0;

        temps[2][essai] = executer(incrementerAtomique);

        totaux[2] = atomique.Load();

        temps[3][essai] = executerLocal();

        totaux[3] = EXPECTED;

    }

    const char* noms[] = {

        "Unprotected", "Mutex", "Atomic", "Local"

    };

    for (int v = 0; v < 4; ++v)

    {

        long long a = temps[v][0];

        long long b = temps[v][1];

        long long c = temps[v][2];

        if (a > b) { auto t = a; a = b; b = t; }

        if (b > c) { auto t = b; b = c; c = t; }

        if (a > b) { auto t = a; a = b; b = t; }

        std::cout << noms[v]

                  << ": total=" << totaux[v]

                  << ", median=" << b << " ms\n";

    }

    return 0;

}