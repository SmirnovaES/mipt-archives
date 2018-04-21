#include <mutex>
#include <vector>
#include <forward_list>
#include <atomic>
#include <condition_variable>
#include <algorithm>

class RWMutex {
 public:
    RWMutex(): writers(0), readers(0), is_writing(false) {}

    void LockWrite() {
        std::unique_lock<std::mutex> lock(local_mutex);
        while (is_writing || readers > 0) {
            cv_for_rw.wait(lock);
        }
        ++writers;
        is_writing = true;
    }

    void UnlockWrite() {
        std::unique_lock<std::mutex> unlock(local_mutex);
        is_writing = false;
        --writers;
        cv_for_rw.notify_all();
    }

    void LockRead() {
        std::unique_lock<std::mutex> lock(local_mutex);
        while (writers > 0) {
            cv_for_rw.wait(lock);
        }
        ++readers;
    }

    void UnlockRead() {
        std::unique_lock<std::mutex> lock(local_mutex);
        --readers;
        if (readers == 0) {
            cv_for_rw.notify_all();
        }
    }

 private:
    std::mutex local_mutex;
    std::condition_variable cv_for_rw;
    size_t writers;
    size_t readers;
    bool is_writing;
};



template <typename T>
class StripedHashSet{
public:
    StripedHashSet(std::size_t concurrency_level,
                   int growth_factor_ = 2, double max_load_factor_ = 0.75) {
        growth_factor = growth_factor_;
        max_load_factor = max_load_factor_;
        curr_size.store(0);
        data_size = concurrency_level * 4;
        mutexes_size = concurrency_level;
        mutexes = std::vector<RWMutex>(concurrency_level);
        data = std::vector<std::forward_list<T>>(concurrency_level * 4);
    }

    bool Insert(const T& element) {
        std::size_t hash_value = hash(element);
        std::size_t stripe_index = GetStripeIndex(hash_value);
        mutexes[stripe_index].LockWrite();
        std::size_t bucket_index = GetBucketIndex(hash_value);
        if (is_contains(element, bucket_index)) {
            mutexes[stripe_index].UnlockWrite();
            return false;
        }
        if(max_load_factor < (curr_size.load() * 1.0) / data_size) {
            mutexes[stripe_index].UnlockWrite();
            get_new_table();
            mutexes[stripe_index].LockWrite();
        }
        bucket_index = GetBucketIndex(hash_value);
        curr_size.fetch_add(1);
        data[bucket_index].push_front(element);
        mutexes[stripe_index].UnlockWrite();
        return true;
    }

    bool Remove(const T& element) {
        std::size_t hash_value = hash(element);
        size_t stripe_index = GetStripeIndex(hash_value);
        mutexes[stripe_index].LockWrite();
        size_t bucket_index = GetBucketIndex(hash_value);
        if (is_contains(element, bucket_index)) {
            data[bucket_index].remove(element);
            curr_size.fetch_sub(1);
            mutexes[stripe_index].UnlockWrite();
            return true;
        } else {
            mutexes[stripe_index].UnlockWrite();
            return false;
        }
    }

    bool Contains(const T& element) {
        size_t hash_value = hash(element);
        size_t stripe_index = GetStripeIndex(hash_value);
        mutexes[stripe_index].LockRead();
        size_t bucket_index = GetBucketIndex(hash_value);
        bool answer = is_contains(element, bucket_index);
        mutexes[stripe_index].UnlockRead();
        return answer;
    }

    std::size_t Size() {
        return curr_size.load();
    }

private:
    std::atomic<size_t> curr_size;
    int growth_factor;
    double max_load_factor;
    std::vector<RWMutex> mutexes;
    std::vector<std::forward_list<T>> data;
    std::size_t data_size;
    std::size_t mutexes_size;
    std::hash<T> hash;

    std::size_t GetBucketIndex(const std::size_t hash_value) {
        return hash_value % data.size();
    }

    std::size_t GetStripeIndex(const std::size_t hash_value) {
        return hash_value % mutexes.size();
    }

    void get_new_table() {
        for (std::size_t i = 0; i < mutexes_size; ++i) {
            mutexes[i].LockWrite();
        }
        if (max_load_factor < (curr_size.load() * 1.0) / data_size) {
            std::vector<std::forward_list<T>> new_data(data_size * growth_factor);
            for (std::size_t i = 0; i < data_size; i++) {
                for (auto &curr_value : data[i]) {
                    std::size_t hash_value = hash(curr_value);
                    new_data[hash_value % (data_size * growth_factor)].push_front(curr_value);
                }
            }
            data.swap(new_data);
            data_size *= growth_factor;
        }
        for (std::size_t i = 0; i < mutexes_size; ++i) {
            mutexes[i].UnlockWrite();
        }
    }

    bool is_contains(const T& element, std::size_t index) {
        return (std::find(data[index].begin(), data[index].end(), element) != data[index].end());
    }
};

template <typename T> using ConcurrentSet = StripedHashSet<T>;