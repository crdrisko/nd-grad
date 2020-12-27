// Copyright (c) 2019 by Anthony Williams. All rights reserved.
// Licensed under the Boost Software License. See the LICENSE file in the project root for more information.
//
// Name: Listing2_07.cpp
// Author: crdrisko
// Date: 12/26/2020-08:09:30
// Description: A joining_thread class

#include <thread>
#include <utility>

class joining_thread
{
    std::thread t;

public:
    joining_thread() noexcept = default;

    template<typename Callable, typename... Args>
    explicit joining_thread(Callable&& func, Args&&... args) : t(std::forward<Callable>(func), std::forward<Args>(args)...)
    {
    }

    explicit joining_thread(std::thread t_) noexcept : t(std::move(t_)) {}
    joining_thread(joining_thread&& other) noexcept : t(std::move(other.t)) {}

    joining_thread& operator=(joining_thread&& other) noexcept
    {
        if (joinable())
            join();

        t = std::move(other.t);
        return *this;
    }

    joining_thread& operator=(joining_thread other) noexcept
    {
        if (joinable())
            join();

        t = std::move(other.t);
        return *this;
    }

    ~joining_thread() noexcept
    {
        if (joinable())
            t.join();
    }

    void swap(joining_thread& other) noexcept { t.swap(other.t); }
    std::thread::id get_id() const noexcept { return t.get_id(); }
    bool joinable() const noexcept { return t.joinable(); }
    void join() { t.join(); }
    void detach() { t.detach(); }
    std::thread& as_thread() noexcept { return t; }
    const std::thread& as_thread() const noexcept { return t; }
};

int main() {}
