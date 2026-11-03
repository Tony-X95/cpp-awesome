#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

std::queue<int> data_queue;  // shared queue for producer-consumer
std::mutex mtx;  // mutex for synchronizing access to the queue
std::condition_variable cv; // condition variable for signaling between producer and consumer
bool finished = false; // flag to indicate when the producer is done producing

void producer() {
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work

        {
            // 1. 上锁，保护共享队列
            std::lock_guard<std::mutex> lock(mtx);
            data_queue.push(i);
            std::cout << "[生产者] 生产了数据: " << i << std::endl;
        } // 2. lock_guard goes out of scope here, releasing the lock

        // 3. notify the consumer that new data is available
        cv.notify_one();
    }

    // 4. Indicate that production is finished
    {
        std::lock_guard<std::mutex> lock(mtx);
        finished = true;
    }
    cv.notify_all(); // notify all consumers that production is finished
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx); // 必须用 unique_lock
        
        // cv.wait 会做三件事：
        // a. 检查后面的 lambda 条件。若满足(true)则继续往下走。
        // b. 若不满足(false)，则[释放锁]并将当前线程挂起（休眠）。
        // c. 被 notify 唤醒后，会重新[重新获取锁]，然后再次检查条件。
        cv.wait(lock, [] { return !data_queue.empty() || finished; });
        
        // 如果队列为空且生产已结束，退出循环
        if (data_queue.empty() && finished) {
            break;
        }

        // 消费数据
        int value = data_queue.front();
        data_queue.pop();
        std::cout << "[消费者] 消费了数据: " << value << std::endl;
        
        lock.unlock(); // 手动提前解锁（良好的习惯，减少锁持有时间）
    }
    std::cout << "[消费者] 消费结束，线程退出。" << std::endl;
}

int main() {
    std::thread prod_thread(producer);
    std::thread cons_thread(consumer);

    prod_thread.join();
    cons_thread.join();

    std::cout << "生产者-消费者示例结束。" << std::endl;

    return 0;
}