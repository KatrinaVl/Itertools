#pragma once

#include <utility>

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
