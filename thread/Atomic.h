#ifndef PNP_ATOMIC_H
#define PNP_ATOMIC_H

#include <boost/noncopyable.hpp>
#include <stdint.h>

namespace muduo
{
namespace detail
{
    template <typename T>
    class AtomicIntegerT : boost::noncopyable
    {
    public:
        AtomicIntegerT()
                : value_(0)
        {
        }

        T get() const
        {
        }

    private:
        volatile T value_;
    };
}
}

#endif //PNP_ATOMIC_H
