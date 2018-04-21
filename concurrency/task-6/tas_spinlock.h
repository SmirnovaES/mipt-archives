#pragma once

#include <atomic>
#include <mutex>

/////////////////////////////////////////////////////////////////////

// Test-And-Set spinlock
class TASSpinLock {
public:
    void Lock() {
        while (locked_.exchange(true , std::memory_order_acquire)) {
            std::this_thread::yield();
        }
    }

    void Unlock() {
        locked_.store(false , std::memory_order_release);
    }

private:
    std::atomic<bool> locked_{false};
};

/////////////////////////////////////////////////////////////////////

1) Чтение и запись в locked_ должны быть упорядочены, в этом смысл спинлока -- ожидающие потоки должны заметить, что критическая секция свободна
2) Если поток1 был в критической секции, а поток2 ожидал, и плсде выхода потока1 из критической секции в нее зашел поток2, то между locked_.store(false) и locked_.exchange(true) возникла стрекла synchronized-with => они связаны соотношением happens-before
3) Можно ослабить гарантии до aquire-release. Мы не можем ослабить до relaxed, т.к. в этом случае вообще нельзя гарантировать, что поток2 увидит запись locked_.store(false) от потока1.
С aquire-release будет работать, т.к. тогда locked_.store(false) и locked_.exchange(true) связаны соотношением syncronized-with (это гарантия aquire-release), а следовательно, и happens-before.