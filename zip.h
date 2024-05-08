#pragma once

#include <utility>

template <class Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end) : begin_(begin), end_(end) {
    }

    Iterator begin() const {  // NOLINT
        return begin_;
    }

    Iterator end() const {  // NOLINT
        return end_;
    }

private:
    Iterator begin_, end_;
};

template <class T_1, class T_2>
class ForZip {
public:
    class IteratorZip {
    public:
        IteratorZip(const T_1& it_1, const T_2& it_2) : it_1_(it_1), it_2_(it_2) {
        }

        bool operator==(const IteratorZip& it) const {
            if (it_1_ == it.it_1_ || it_2_ == it.it_2_) {
                return true;
            }
            return false;
        }

        bool operator!=(const IteratorZip& it) const {
            if (it_1_ == it.it_1_ || it_2_ == it.it_2_) {
                return false;
            }
            return true;
        }

        auto operator*() const {
            return std::make_pair(*it_1_, *it_2_);
        }

        IteratorZip& operator++() {
            ++it_1_;
            ++it_2_;
            return *this;
        }

    private:
        T_1 it_1_;
        T_2 it_2_;
    };

    ForZip(T_1 it_1_b, T_1 it_1_e, T_2 it_2_b, T_2 it_2_e)
        : it_1_begin_(it_1_b), it_1_end_(it_1_e), it_2_begin_(it_2_b), it_2_end_(it_2_e) {
    }

    IteratorZip begin() const {  // NOLINT
        IteratorZip zip_begin(it_1_begin_, it_2_begin_);
        return zip_begin;
    }

    IteratorZip end() const {  // NOLINT
        IteratorZip zip_end(it_1_end_, it_2_end_);
        return zip_end;
    }

private:
    T_1 it_1_begin_;
    T_1 it_1_end_;
    T_2 it_2_begin_;
    T_2 it_2_end_;
};

template <class T_1, class T_2>
auto Zip(const T_1& t_1, const T_2& t_2) {
    ForZip iter(std::begin(t_1), std::end(t_1), std::begin(t_2), std::end(t_2));
    IteratorRange res(iter.begin(), iter.end());
    return res;
}
