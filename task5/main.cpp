#include <iostream>
#include <thread>
#include <vector>
#include "store.h"


void GoToTheStore(size_t n, std::vector<size_t> sections, std::vector<int> product_count, Store *s,
                  int &ready) {
    if (!s->Enter()) {
        ready = true;
        return;
    }
    for (size_t i = 0; i < n; ++i) {
        if (!s->JoinQueue(sections[i])) {
            ready = true;
            return;
        }
        s->PurchaseProducts(sections[i], product_count[i]);
    }
    s->Leave();
    ready = true;
}

int main() {
    Store store;
    size_t thread_count =
            std::max(size_t(std::thread::hardware_concurrency()), 2 + store.section_count) - 1 - store.section_count;
    std::vector<std::thread> threads(thread_count);
    std::vector<int> ready(thread_count, true);
    std::string s;
    while (true) {
        std::cin >> s;
        if (s == "open") {
            store.Open();
        } else if (s == "add") {
            size_t n;
            std::vector<size_t> sections;
            std::vector<int> count;
            try {

                std::cin >> n;
                sections.resize(n);
                std::vector<size_t> sections(n);
                for (auto &x: sections) {
                    std::cin >> x;
                }
                count.resize(n);
                for (auto &x: count) {
                    std::cin >> x;
                }
            } catch (...) {
                std::cout << "Invalid input. Skipped\n";
            }
            for (size_t i = 0;; i = (i + 1) % thread_count) {
                if (ready[i]) {
                    ready[i] = 0;
                    if (threads[i].joinable()) {
                        threads[i].join();
                    }
                    std::thread t(GoToTheStore, n, sections, count, &store,
                                  std::ref(ready[i]));
                    std::swap(threads[i], t);
                    break;
                }
            }
        } else if (s == "close") {
            store.Close();
            break;
        }
    }
    for (auto &t: threads) {
        if (t.joinable()) {
            t.join();
        }

    }
    return 0;
}
