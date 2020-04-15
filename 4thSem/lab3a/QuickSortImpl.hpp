#pragma once

#include <algorithm>
#include <future>

namespace lab::detail {

    constexpr static auto PARALLELING_POINT = 7000;

    template <typename Iter, typename Comp>
    void default_quick(Iter beg, Iter end, Comp comp) {

        const auto distance = std::distance(beg, end);

        if (distance < 2) {
            return;
        }
        using std::swap;

        auto last = std::prev(end);
        swap(*std::next(beg, distance / 2), *last);

        auto bound = std::partition(beg, last, [&](const auto &el) {
            return comp(el, *last);
        });
        swap(*bound, *last);

        default_quick(beg, bound, comp);
        default_quick(std::next(bound), end, comp);
    }


    template    <typename Iter, typename Comp>
    void parallel_quick(Iter beg, Iter end, Comp comp) {

        const auto distance = std::distance(beg, end);

        if (distance < 2) {
            return;
        }
        if (distance <= PARALLELING_POINT) {
            default_quick(beg, end, comp);
            return;
        }

        using std::swap;

        auto last = std::prev(end);
        swap(*std::next(beg, distance / 2), *last);

        auto bound = std::partition(beg, last, [&](const auto &el) {
            return comp(el, *last);
        });
        swap(*bound, *last);

        if (std::distance(beg, bound) > PARALLELING_POINT) {
            auto func_call_result = std::async(std::launch::async, parallel_quick<Iter, Comp>, beg, bound, comp);
            parallel_quick(std::next(bound), end, comp);
            func_call_result.wait();
        } else {
            parallel_quick(beg, bound, comp);
            parallel_quick(std::next(bound), end, comp);
        }
    }
}

