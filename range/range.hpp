
#ifndef __RANGE_H
#define __RANGE_H

namespace shibing {
namespace detail {

template <typename T>
class range {
   public:
    range(const T &start, const T &end, const T &step)
        : start_{start}, end_{end}, step_{step} {}

    class iterator {
       public:
        typedef T value_type;
        typedef T &referece;
        typedef iterator self;

        iterator(const T &value, const T &step) : value_{value}, step_{step} {}

        self &operator++() {
            value_ += step_;
            return *this;
        }

        referece operator*() { return value_; }

        bool operator==(const self &rhs) {
            return step_ > 0 ? value_ >= rhs.value_ : value_ <= rhs.value_;
        }
        bool operator!=(const self &rhs) {
            return step_ > 0 ? value_ < rhs.value_ : value_ > rhs.value_;
        }

       private:
        T value_;
        T step_;
    };

    iterator begin() { return iterator{start_, step_}; }
    iterator end() { return iterator{end_, step_}; }

   private:
    T start_;
    T end_;
    T step_;
};
}

template <typename T>
detail::range<T> range(const T &end) {
    return detail::range<T>{0, end, 1};
}

template <typename T>
detail::range<T> range(const T &start, const T &end) {
    return detail::range<T>{start, end, 1};
}

template <typename T>
detail::range<T> range(const T &start, const T &end, const T &step) {
    return detail::range<T>{start, end, step};
}
}

#endif
