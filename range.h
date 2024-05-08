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
