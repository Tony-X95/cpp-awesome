#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <algorithm>

// ==========================================
// 1. 觀察者介面 (Observer Interface)
// ==========================================
class Observer {
public:
    virtual ~Observer() = default;
    virtual void onNotify(const std::string& message) = 0;
};

class Subject {
private:
    std::vector<std::weak_ptr<Observer>> m_observers;
    std::mutex m_mutex;

public:
    void registerObserver(std::shared_ptr<Observer> observer) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_observers.push_back(observer);
    }

    // 異步發送通知
    void notifyObserversAsync(const std::string& message) {
        // 在新執行緒中執行通知，達到異步效果
        std::thread([this, message]() {
            std::vector<std::shared_ptr<Observer>> validObservers;
            
            // 💡 步驟 A：在鎖的保護下，快速篩選出還活著的觀察者，並提升為 shared_ptr
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                // 用來清除已經死掉的觀察者 (Clean up expired pointers)
                auto it = m_observers.begin();
                while (it != m_observers.end()) {
                    if (auto observer = it->lock()) { // 提升 weak_ptr 為 shared_ptr
                        validObservers.push_back(observer);
                        ++it;
                    } else {
                        // 觀察者已被銷毀，從列表中移除
                        it = m_observers.erase(it); // Remove expired weak_ptr
                    }
                }
            }// 💡 鎖在這裡釋放。我們不在持鎖時呼叫回呼函數，避免死結 (Deadlock)

            // 💡 步驟 B：安全地逐一發送通知
            // 此時 validObservers 內的 shared_ptr 確保了這些觀察者在迴圈執行期間絕對不會被銷毀
            for (const auto& observer : validObservers) {
                if (observer) {
                    observer->onNotify(message);
                }
            }
        }).detach();
    }
};

// ==========================================
// 3. 具體的觀察者實現
// ==========================================
class ConcreteObserver : public Observer {
private:
    std::string m_name;

public:
    ConcreteObserver(const std::string& name) : m_name(std::move(name)) {}
    ~ConcreteObserver() override {
        std::cout << "[Destructor] " << m_name << " is being destroyed." << std::endl;
    }

    void onNotify(const std::string& message) override {
        std::cout << "[Notification] " << m_name << " received message: " << message << std::endl;
    }
};

// ==========================================
// 4. 測試多執行緒與銷毀情境
// ==========================================
int main() {
    Subject newsAgency;

    auto subscriber1 = std::make_shared<ConcreteObserver>("Subscriber 1");
    auto subscriber2 = std::make_shared<ConcreteObserver>("Subscriber 2");

    newsAgency.registerObserver(subscriber1);
    newsAgency.registerObserver(subscriber2);

    std::cout << "--- Sending 1st News (Both alive) ---" << std::endl;
    newsAgency.notifyObserversAsync("Breaking News: Observer Pattern in C++!");

    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 等待通知完成

    std::cout << "--- Destroying Subscriber 2 ---" << std::endl;
    subscriber2.reset(); // 銷毀 Subscriber 2

    std::cout << "--- Sending 2nd News (Subscriber 2 destroyed) ---" << std::endl;
    newsAgency.notifyObserversAsync("Weather Update: It is sunny today!");

    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 等待通知完成
    std::cout << "--- Main thread finished ---" << std::endl;
    return 0;
}