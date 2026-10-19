

#include "NKThreading/NkThread.h"

#include "NKThreading/NkMutex.h"

#include <iostream>

using namespace nkentseu::threading;

// Freezing version, preserved as a comment:

/*

NkMutex m1;

NkMutex m2;

void threadA()

{

    NkScopedLockMutex lock1(m1);

    NkChrono::SleepMilliseconds(100);

    NkScopedLockMutex lock2(m2);

}

void threadB()

{

    NkScopedLockMutex lock1(m2);

    NkChrono::SleepMilliseconds(100);

    NkScopedLockMutex lock2(m1);

}

*/

// Corrected version: always acquire m1 before m2.

NkMutex m1;

NkMutex m2;

void threadA()

{

    NkScopedLockMutex lock1(m1);

    NkChrono::SleepMilliseconds(100);

    NkScopedLockMutex lock2(m2);

    std::cout << "Thread A completed\n";

}

void threadB()

{

    NkScopedLockMutex lock1(m1);

    NkChrono::SleepMilliseconds(100);

    NkScopedLockMutex lock2(m2);

    std::cout << "Thread B completed\n";

}

int main()

{

    NkThread a(threadA);

    NkThread b(threadB);

    a.Join();

    b.Join();

    std::cout << "Both threads completed\n";

    return 0;

}