#include <iostream>

#include <thread>

#include <vector>

#include <chrono>

#include <atomic>

using namespace std;

atomic<unsigned long long> total{0};

void shortTask() {

    unsigned long long sum = 0;

    for (int i = 0; i < 1000; ++i) {

        sum += i;

    }

    total.fetch_add(sum, memory_order_relaxed);

}

void longTask() {

    unsigned long long sum = 0;

    for (int repeat = 0; repeat < 100; ++repeat) {

        for (int i = 0; i < 1000; ++i) {

            sum += i;

        }

    }

    total.fetch_add(sum, memory_order_relaxed);

}

template <typename Task>

double measureThreads(Task task) {

    auto start = chrono::steady_clock::now();

    vector<thread> threads;

    for (int i = 0; i < 200; ++i) {

        threads.emplace_back(task);

    }

    for (auto& t : threads) {

        t.join();

    }

    auto end = chrono::steady_clock::now();

    return chrono::duration<double, milli>(end - start).count();

}

int main() {

    cout << "Manual threads, short task (ms):\n";

    for (int i = 0; i < 3; ++i) {

        cout << measureThreads(shortTask) << '\n';

    }

    cout << "Manual threads, long task (ms):\n";

    cout << measureThreads(longTask) << '\n';

    cout << "Result: " << total.load() << '\n';

    return 0;

}