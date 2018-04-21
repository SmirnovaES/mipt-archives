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

1) ������ � ������ � locked_ ������ ���� �����������, � ���� ����� �������� -- ��������� ������ ������ ��������, ��� ����������� ������ ��������
2) ���� �����1 ��� � ����������� ������, � �����2 ������, � ����� ������ ������1 �� ����������� ������ � ��� ����� �����2, �� ����� locked_.store(false) � locked_.exchange(true) �������� ������� synchronized-with => ��� ������� ������������ happens-before
3) ����� �������� �������� �� aquire-release. �� �� ����� �������� �� relaxed, �.�. � ���� ������ ������ ������ �������������, ��� �����2 ������ ������ locked_.store(false) �� ������1.
� aquire-release ����� ��������, �.�. ����� locked_.store(false) � locked_.exchange(true) ������� ������������ syncronized-with (��� �������� aquire-release), � �������������, � happens-before.