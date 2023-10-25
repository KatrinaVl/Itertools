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

template <class T>
class ForRange {
public:
    class RangeIterator {
    public:
        RangeIterator(const T& it, const T& step, const T& e) : it_(it), s_(step), e_(e) {
        }

        bool operator==(const RangeIterator& it) const {
            if (it_ == it.it_) {
                return true;
            }
            return false;
        }

        bool operator!=(const RangeIterator& it) const {
            if (it_ == it.it_) {
                return false;
            }
            return true;
        }

        auto operator*() const {
            return it_;
        }

        RangeIterator& operator++() {
            if (it_ + s_ <= e_) {
                it_ += s_;
            } else {
                it_ = e_;
            }
            return *this;
        }

    private:
        T it_;
        T s_;
        T e_;
    };

    ForRange(const T& b, const T& e, const T& s = 1) : it_begin_(b), it_end_(e), step_(s) {
    }

    RangeIterator begin() const {  // NOLINT
        RangeIterator zip_begin(it_begin_, step_, it_end_);
        return zip_begin;
    }

    RangeIterator end() const {  // NOLINT
        RangeIterator zip_end(it_end_, step_, it_end_);
        return zip_end;
    }

private:
    T it_begin_;
    T it_end_;
    T step_;
};

template <class T>
auto Range(const T& b, const T& e, const T& s) {
    ForRange iter(b, e, s);
    IteratorRange res(iter.begin(), iter.end());
    return res;
}

template <class T>
auto Range(const T& b, const T& e) {
    ForRange iter(b, e);
    IteratorRange res(iter.begin(), iter.end());
    return res;
}

template <class T>
auto Range(const T& e) {
    T b = 0;
    ForRange iter(b, e);
    IteratorRange res(iter.begin(), iter.end());
    return res;
}

template <class T>
class Subs {
public:
    class SubsIterator {
    public:
        SubsIterator(const T& b) : it_(b) {
        }
        bool operator==(const SubsIterator& it) const {
            if (it_ == it.it_) {
                return true;
            }
            return false;
        }

        bool operator!=(const SubsIterator& it) const {
            if (it_ == it.it_) {
                return false;
            }
            return true;
        }

        auto operator*() const {
            return *it_;
        }

        SubsIterator& operator++() {
            ++it_;
            return *this;
        }

    private:
        T it_;
    };
    Subs(const T& b, const T& e) : it_begin_(b), it_end_(e) {
    }

    SubsIterator begin() const {  // NOLINT
        SubsIterator p_begin(it_begin_);
        return p_begin;
    }

    SubsIterator end() const {  // NOLINT
        SubsIterator p_end(it_end_);
        return p_end;
    }

private:
    T it_begin_;
    T it_end_;
};

template <class T>
class ForGroup {
public:
    class IteratorGroup {
    public:
        IteratorGroup(const T& b, const T& e, const T& it) : it_e_(e), it_b_(b), it_(it) {
        }
        bool operator==(const IteratorGroup& it) const {
            if (it_ == it.it_) {
                return true;
            }
            return false;
        }

        bool operator!=(const IteratorGroup& it) const {
            if (it_ == it.it_) {
                return false;
            }
            return true;
        }

        auto operator*() const {
            auto it_new = it_;
            while (it_new != it_e_ && *it_new == *it_) {
                ++it_new;
            }
            Subs s(it_, it_new);
            return s;
        }

        IteratorGroup& operator++() {
            auto it_new = it_;
            while (it_new != it_e_ && *it_new == *it_) {
                ++it_new;
            }
            it_ = it_new;
            return *this;
        }

    private:
        T it_e_;
        T it_b_;
        T it_;
    };

    ForGroup(const T& b, const T& e) : it_begin_(b), it_end_(e) {
    }

    IteratorGroup begin() const {  // NOLINT
        IteratorGroup g_begin(it_begin_, it_end_, it_begin_);
        return g_begin;
    }

    IteratorGroup end() const {  // NOLINT
        IteratorGroup g_end(it_begin_, it_end_, it_end_);
        return g_end;
    }

private:
    T it_begin_;
    T it_end_;
};

template <class T>
auto Group(const T& t) {
    ForGroup iter_group(t.begin(), t.end());
    IteratorRange res(iter_group.begin(), iter_group.end());
    return res;
}
