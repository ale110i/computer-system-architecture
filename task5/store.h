#pragma once

#include <mutex>
#include <vector>
#include <unordered_map>
#include <queue>
#include <thread>
#include <condition_variable>


int TIME_FOR_ONE_PURCHASE = 500; // in milliseconds

class Store {
public:
    explicit Store(size_t section_count = 3);

    void Open();

    void Close();

    bool Enter();

    bool JoinQueue(size_t section);

    void Work(size_t section);

    void PurchaseProducts(size_t section, int number_of_purchases);

    void Leave();

    ~Store();

    size_t section_count = 3;

private:
    std::mutex common_mutex; // for individual_cv array, queues and is_cashier_free (these data are closely related)
    std::vector<std::queue<std::thread::id>> queues;
    std::unordered_map<std::thread::id, std::condition_variable> individual_cv;
    std::vector<std::condition_variable> cashier_cv;
    std::vector<bool> is_cashier_free;
    std::mutex report_mutex;
    std::atomic_bool is_open = false; // for new customers
    std::atomic_bool is_end_of_day = false; // for cashiers
    std::vector<std::thread> cashiers;
};
