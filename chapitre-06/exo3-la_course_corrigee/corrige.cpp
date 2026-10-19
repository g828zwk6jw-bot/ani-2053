#include "NKThreading/NKThread.h"

#include "NKThreading/NKMutex.h"

#include "NKCore/NkAtomic.h"

#include "NKCore/NkChrono.h"

#include <iostream>

#include <vector>

int compteur = 0;

NkMutex mutex;

NkAtomicInt atomique;

void incrementerSansProtection()

{

    for (int i = 0; i < 1000000; ++i)

        compteur += 1;

}

void incrementerMutex()

{

    for (int i = 0; i < 1000000; ++i)

    {

        NkScopedLock<NkMutex> lock(mutex);

        compteur += 1;

    }

}

void incrementerAtomique()

{

    for (int i = 0; i < 1000000; ++i)

        atomique.FetchAdd(1);

}

void incrementerLocal(int* total)

{

    int somme = 0;

    for (int i = 0; i < 1000000; ++i)

        somme += 1;

    *total = somme;

}

int main()

{

    // Use the NKentseu kit's NkChrono to measure each version.

    // API details may need adjustment to match the installed kit.

    for (int version = 0; version < 4; ++version)

    {

        double temps[3] = {};

        int total = 0;

        for (int essai = 0; essai < 3; ++essai)

        {

            compteur = 0;

            atomique = 0;

            std::vector<NkThread> threads;

            // TODO: start and stop NkChrono using the exact API

            // from the installed kit around the selected version.

            for (int i = 0; i < 8; ++i)

            {

                if (version == 0)

                    threads.emplace_back(incrementerSansProtection);

                else if (version == 1)

                    threads.emplace_back(incrementerMutex);

                else if (version == 2)

                    threads.emplace_back(incrementerAtomique);

                else

                    threads.emplace_back(incrementerLocal, nullptr);

            }

            for (auto& thread : threads)

                thread.Join();

            total = (version == 2) ? 8000000 : compteur;

            temps[essai] = 0.0;

        }

        std::cout << "Version " << version

                  << ": total=" << total

                  << ", median time=" << temps[1] << " ms\n";

    }

    return 0;

}