#include "lru_cache.h"
#include <chrono>
#include <iostream>
#include <thread>

void test_basic_operations() {
  std::cout << "=== 基本操作测试 ===" << std::endl;
  LRUCache<int, std::string> cache(3);

  cache.set(1, "one");
  cache.set(2, "two");
  cache.set(3, "three");
  //   cache.set(4, "four", 5);
  std::string val;
  if (cache.get(1, val)) {
    std::cout << "获取键1: " << val << std::endl;
  } else {
    std::cout << "键1不存在" << std::endl;
  }

  cache.set(4, "four"); // 应该淘汰键2

  if (cache.get(2, val)) {
    std::cout << "键2仍然存在" << std::endl;
  } else {
    std::cout << "键2已被淘汰" << std::endl;
  }
}

void test_lru_policy() {
  std::cout << "\n=== LRU策略测试 ===" << std::endl;
  LRUCache<int, std::string> cache(3);

  cache.set(1, "one");
  cache.set(2, "two");
  cache.set(3, "three");

  // 访问键1和键3，使键2成为最久未使用的
  std::string val;
  cache.get(1, val);
  cache.get(3, val);

  cache.set(4, "four"); // 应该淘汰键2

  if (cache.get(2, val)) {
    std::cout << "键2仍然存在" << std::endl;
  } else {
    std::cout << "键2已被淘汰" << std::endl;
  }
}

void test_expiration() {
  std::cout << "\n=== 过期时间测试 ===" << std::endl;
  LRUCache<int, std::string> cache(3);

  // 设置2秒后过期的条目
  auto now = std::chrono::steady_clock::now();
  int64_t expire_time =
      std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch())
          .count() +
      2;
  std::cout << "expire_time:"
            << std::chrono::duration_cast<std::chrono::seconds>(
                   now.time_since_epoch())
                   .count()
            << std::endl;
  cache.set(1, "one", expire_time);

  std::cout << "等待3秒..." << std::endl;
  std::string new_val;
  bool suc = cache.get(1, new_val);
  if (suc) {
    std::cout << "获取键1: " << new_val << std::endl;
  } else {
    std::cout << "键值1对应的值不存在" << std::endl;
  }

  std::this_thread::sleep_for(std::chrono::seconds(3));

  std::string val;
  if (cache.get(1, val)) {
    std::cout << "键1仍然存在: " << val << std::endl;
  } else {
    std::cout << "键1已过期" << std::endl;
  }
}

int main() {
  test_basic_operations();
  test_lru_policy();
  test_expiration();

  return 0;
}
