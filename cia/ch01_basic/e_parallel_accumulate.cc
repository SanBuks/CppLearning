#include <thread>
#include <iterator>
#include <vector>
#include <numeric>
#include <iostream>
#include <format>

using cul = const unsigned long long;
using ul = unsigned long long;

// 单独线程逻辑, 计算一个范围
template<typename Iterator, typename T>
struct accumulate_block {
  void operator()(Iterator first, Iterator last, T &result) {
    result = std::accumulate(first, last, result);
  }
};

/**
 * @return 线程数量
 * @param min_per_thread 最小单个线程处理数量
 * @param size 处理总数量
 */
ul thread_num(cul min_per_thread, cul size) {
  cul max_thread = (size+ min_per_thread - 1) / min_per_thread;  // 向上取整
  cul hardware_threads = std::thread::hardware_concurrency();
  std::cout << std::format("hardware thread: {}\n", hardware_threads);
  cul num_threads = std::min(!hardware_threads ? 2 : hardware_threads, max_thread);
  return num_threads;
}

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
  auto const length = std::distance(first, last);
  if (!length) return init;

  auto num_threads = thread_num(25, length);
  cul block_size = length / num_threads;

  std::vector<T> results(num_threads);
  std::vector<std::thread> threads(num_threads - 1);  // 本身线程算一个

  Iterator block_start = first;
  Iterator block_end = first;
  for (unsigned long i = 0; i < (num_threads - 1); ++i) {
    std::advance(block_end, block_size);
    threads[i] = std::thread(accumulate_block<Iterator, T>(),    // 移动构造
                             block_start, block_end, std::ref(results[i]));
    block_start = block_end;
  }
  accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);

  for (auto & entry : threads) {
    entry.join();
  }
  return std::accumulate(results.begin(), results.end(), init);
}

int main() {
  std::vector<size_t> vec(100000);
  size_t sum_check = 0;
  for (size_t i = 0; i != vec.size(); ++i) {
    vec[i] = i;
    sum_check += vec[i];
  }

  size_t sum = parallel_accumulate(vec.begin(), vec.end(), 0ull);

  std::cout << sum << "\n" << sum_check << "\n";
  return 0;
}