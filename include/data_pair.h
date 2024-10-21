#ifndef DATA_PAIR_H
#define DATA_PAIR_H

template<typename T, typename U>
class DataPair {
public:
    DataPair() : first(T()), second(U()) {}

    T getFirst() { return first; }
    U getSecond() { return second; }
    void setSecond(const U& newSecond) { second = newSecond; }
    void setFirst(const T& newFirst) { first = newFirst; }

    void clear() {
        first = T();
        second = U();
    }

private:
    T first;
    U second;
};

#endif // DATA_PAIR_H
