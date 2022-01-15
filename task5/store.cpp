#include <iostream>
#include "store.h"

Store::Store(size_t section_count) : section_count(section_count),
                                     queues(section_count),
                                     cashier_cv(section_count),
                                     is_cashier_free(section_count, true) {
    for (size_t i = 0; i < section_count; ++i) {
        cashiers.emplace_back(&Store::Work, this, i);
    }
}

bool Store::Enter() {
    std::lock_guard<std::mutex> report_lock(report_mutex);
    std::lock_guard lock(common_mutex);
    if (!is_open) {
        std::cout << "Thread " << std::this_thread::get_id() << " can't enter the store because it is closed"
                  << std::endl;
        return false;
    }
    auto cur_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "Thread " << std::this_thread::get_id() << " entered the store at " << ctime(&cur_time) << std::endl;
    individual_cv[std::this_thread::get_id()];
    return true;
}

void Store::Leave() {
    {
        std::lock_guard lock(common_mutex);
        individual_cv.erase(std::this_thread::get_id());
        if (individual_cv.empty()) {
            is_end_of_day = true;
            for (auto &x : cashier_cv) {
                x.notify_one();
            }
        }
    }

    auto cur_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::lock_guard<std::mutex> lock(report_mutex);
    std::cout << "Thread " << std::this_thread::get_id() << " leaved the store at "
              << ctime(&cur_time) << std::endl;
}

bool Store::JoinQueue(size_t section) {
    if (section >= section_count) {
        std::lock_guard report_lock(report_mutex);
        std::cout << "Thread " << std::this_thread::get_id()
                  << " couldn't join the queue because the store doesn't have a section " << section << std::endl;
        return false;
    }
    {
        std::lock_guard lock(common_mutex);
        queues[section].push(std::this_thread::get_id());
        if (queues[section].size() == 1 && is_cashier_free[section]) {
            cashier_cv[section].notify_one();
        }
    }
    auto cur_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::lock_guard report_lock(report_mutex);
    std::cout << "Thread " << std::this_thread::get_id() << " joined the queue for section " << section << " at "
              << ctime(&cur_time) << std::endl;
    return true;
}

void Store::PurchaseProducts(size_t section, int number_of_purchases) {
    {
        std::unique_lock lock(common_mutex);
        auto &cv = individual_cv[std::this_thread::get_id()];
        while (queues[section].front() != std::this_thread::get_id() || !is_cashier_free[section]) {
            cv.wait(lock);
        }
        is_cashier_free[section] = false;
        queues[section].pop();
        cv.wait_for(lock, number_of_purchases * std::chrono::milliseconds(TIME_FOR_ONE_PURCHASE));
        is_cashier_free[section] = true;
        cashier_cv[section].notify_one();
    }
    auto cur_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::lock_guard report_lock(report_mutex);
    std::cout << "Thread " << std::this_thread::get_id() << " purchased in section " << section << " at "
              << ctime(&cur_time) << std::endl;
}

void Store::Open() {
    std::lock_guard report_lock(report_mutex);
    std::lock_guard lock(common_mutex);
    if (is_open) {
        std::cout << "The store is already open!" << std::endl;
    }
    auto cur_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    is_open = true;
    std::cout << "The store opened at " << ctime(&cur_time) << std::endl;
}

void Store::Close() {
    {
        std::lock_guard lock(common_mutex);
        if (!is_open) {
            std::lock_guard report_lock(report_mutex);
            std::cout << "The store is already closed!" << std::endl;
        }
        auto cur_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        is_open = false;
        std::cout << "The store closed at " << ctime(&cur_time) << std::endl;
        if (individual_cv.empty()) {
            is_end_of_day = true;
            for (auto &x: cashier_cv) {
                x.notify_one();
            }
        }
    }
}

void Store::Work(size_t section) {
    while (!is_end_of_day) {
        std::unique_lock lock(common_mutex);
        auto &cv = cashier_cv[section];
        while ((queues[section].empty() || !is_cashier_free[section]) && !is_end_of_day) {
            cv.wait(lock);
        }
        if (is_end_of_day) {
            return;
        }

        if (!queues[section].empty() && is_cashier_free[section]) {
            individual_cv[queues[section].front()].notify_one();
        }
    }
}

Store::~Store() {
    for (auto &t: cashiers) {
        t.join();
    }
    auto cur_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "The store finished its work at "
              << ctime(&cur_time) << std::endl;
}
