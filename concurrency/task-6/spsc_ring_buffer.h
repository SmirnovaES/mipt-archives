#pragma once

#include <atomic>
#include <vector>

//////////////////////////////////////////////////////////////////////

// Single-Producer/Single-Consumer Fixed-Size Ring Buffer (Queue)

template <typename T>
class SPSCRingBuffer {
public:
    explicit SPSCRingBuffer(const size_t capacity)
        : buffer_(capacity + 1) {
    }

    bool Publish(T element) {
        const size_t curr_head = head_.load(std::memory_order_acquire);
        const size_t curr_tail = tail_.load(std::memory_order_relaxed);

        if (Full(curr_head, curr_tail)) {
            return false;
        }

        buffer_[curr_tail] = element;
        tail_.store(Next(curr_tail) , std::memory_order_release);
        return true;
    }

    bool Consume(T& element) {
        const size_t curr_head = head_.load(std::memory_order_relaxed);
        const size_t curr_tail = tail_.load(std::memory_order_acquire);

        if (Empty(curr_head, curr_tail)) {
            return false;
        }

        element = buffer_[curr_head];
        head_.store(Next(curr_head) , std::memory_order_release);
        return true;
    }

private:
    bool Full(const size_t head, const size_t tail) const {
        return Next(tail) == head;
    }

    bool Empty(const size_t head, const size_t tail) const {
        return tail == head;
    }

    size_t Next(const size_t slot) const {
        return (slot + 1) % buffer_.size();
    }

private:
    std::vector<T> buffer_;
    std::atomic<size_t> tail_{0};
    std::atomic<size_t> head_{0};
};

//////////////////////////////////////////////////////////////////////

1) ћы упор€дочиваем чтени€ и записи в tail_ и head_, т.к. работа с очередью идет по принципу положил-забрал.  онсьюмер должен видеть элемент в очереди, который туда положил продьюсер.
2) ≈сли сначала продьюсер положил элемент в очередь, а потом консьюмер его оттуда забирает, то от tail_.store(Next(curr_tail)) к tail_.load() будет стрелка synchronized-with, означающа€ happens-before между этими событи€ми. јналогично и дл€ head_.store(Next(curr_head)) и head_.load()
ƒл€  head_.load() и head_.store(Next(curr_head)) в Consume() отношение happens before возникает из-за program order (аналогично в Publish())
3) –ассмотрим Publish() (дл€ Consume() аналогично). „тение tail_ можно сделать relaxed, т.к. только в данном методе (то есть только один поток) мен€ет его значение. ј значит, гарантий relaxed достаточно, т.к. идет работа в одном потоке с одной €чейкой пам€ти.
„тение head_ нужно сделать aquire, парным с release-записью head_ в Consume(), т.к. нам важно, чтобы эти два событи€ были св€заны стрелкой syncronized-with. ѕо этой же причине запись в tail_ будет release.