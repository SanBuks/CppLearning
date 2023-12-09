#include <queue>
#include <thread>
#include <vector>
#include <format>
#include <future>
#include <utility>
#include <functional>
#include <iostream>
#include <condition_variable>

// 并发无序 使得 强关联互斥不推荐应用线程池

class ThreadPool {
 public:
  using Task = std::packaged_task<void()>;

  ThreadPool(const ThreadPool &rhs) = delete;
  ThreadPool &operator=(const ThreadPool &rhs) = delete;
  static ThreadPool &GetInstance(unsigned int num = 5);
  ~ThreadPool();

  template<typename F, typename... Args>
  auto Commit(F &&fn, Args &&... args) -> std::future<decltype(fn(args...))>;

  void Stop();
  void Start();

 private:
  explicit ThreadPool(unsigned int num);

  std::mutex cv_mtx_{};
  std::condition_variable cv_{};

  std::atomic_bool stop_{false};  // 线程池停止
  std::atomic_uint num_{5};       // 线程个数

  std::queue<Task> tasks_{};
  std::vector<std::thread> pool_{};
};

ThreadPool::ThreadPool(unsigned int num) { if (!num) num_ = 1; Start(); }
ThreadPool::~ThreadPool() { Stop(); }
ThreadPool &ThreadPool::GetInstance(unsigned int num) {
  static ThreadPool thread_pool(num);
  return thread_pool;
}

template<typename F, typename... Args>
auto ThreadPool::Commit(F &&fn, Args &&... args) -> std::future<decltype(fn(args...))> {
  using ReturnType = decltype(fn(args...));

  if (stop_.load()) { return std::future<ReturnType>{}; }

  auto process = std::bind(std::forward<F>(fn), std::forward<Args>(args)...);

  // ReturnType () <=> 返回 ReturnType 的空参函数类型
  auto task = std::make_shared<std::packaged_task<ReturnType()>>(process);

  std::future<ReturnType> ret = task->get_future();
  {
    std::lock_guard<std::mutex> guard(cv_mtx_);
    tasks_.emplace([task]() { (*task)(); });
  }
  cv_.notify_one();
  return ret;
}

void ThreadPool::Stop() {
  stop_.store(true);
  cv_.notify_all();
  for (auto &item : pool_) {
    if (item.joinable()) {
      item.join();
    }
  }
}

void ThreadPool::Start() {
  for (int i = 0; i < num_; ++i) {
    pool_.emplace_back([this]() {
      while (!this->stop_.load()) {
        Task task;
        {
          std::unique_lock<std::mutex> cv_mt(cv_mtx_);
          this->cv_.wait(cv_mt, [this] {
            return this->stop_.load() || !this->tasks_.empty();
          });
          if (this->tasks_.empty()) continue;
          task = std::move(this->tasks_.front());
          tasks_.pop();
        }
        this->num_--;
        task();
        this->num_++;
      }
    });
  }
}

std::string process(std::mutex &mtx, bool &flag, const std::string &str) {
  int times = 0;
  while (times < 6) {
    {
      std::lock_guard lock(mtx);
      if (!flag) {
        std::cout << std::this_thread::get_id() << " save record!" << std::endl;
        return "unfinished";
      }
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    ++times;
  }
  return str;
}

void stop_process_test() {
  bool process1_run_flag = true;
  bool process2_run_flag = true;

  std::condition_variable process1_cv;
  std::condition_variable process2_cv;

  std::mutex process1_mtx;
  std::mutex process2_mtx;

  auto future1 = ThreadPool::GetInstance().Commit(process, std::ref(process1_mtx), std::ref(process1_run_flag), "123");
  auto future2 = ThreadPool::GetInstance().Commit(process, std::ref(process2_mtx), std::ref(process2_run_flag), "123");

  std::this_thread::sleep_for(std::chrono::seconds(5));

  if (future1.wait_for(std::chrono::seconds(0)) !=  std::future_status::ready) {
    std::cout << "stop future1 \n";
    std::scoped_lock lock(process1_mtx);
    process1_run_flag = false;
  } else {
    std::cout << future1.get() << "\n";
  }

  if (future2.wait_for(std::chrono::seconds(0)) !=  std::future_status::ready) {
    std::cout << "stop future2 \n";
    std::scoped_lock lock(process2_mtx);
    process2_run_flag = false;
  } else {
    std::cout << future2.get() << "\n";
  }
}

int main() {
  stop_process_test();
  return 0;
}