//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// UNSUPPORTED: libcpp-has-no-threads

// <atomic>

// template <class Integral>
//     Integral
//     atomic_fetch_or(volatile atomic<Integral>* obj, Integral op);
//
// template <class Integral>
//     Integral
//     atomic_fetch_or(atomic<Integral>* obj, Integral op);

#include <atomic>
#include <type_traits>
#include <cassert>

#include "atomic_helpers.h"

template <class T>
struct TestFn {
  void operator()() const {
    {
        typedef std::atomic<T> A;
        A t;
        std::atomic_init(&t, T(1));
        assert(std::atomic_fetch_or(&t, T(2)) == T(1));
        assert(t == T(3));
    }
    {
        typedef std::atomic<T> A;
        volatile A t;
        std::atomic_init(&t, T(3));
        assert(std::atomic_fetch_or(&t, T(2)) == T(3));
        assert(t == T(3));
    }
  }
};

int main()
{
    TestEachIntegralType<TestFn>()();
}
