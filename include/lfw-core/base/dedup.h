#ifndef LFW_CORE_BASE_DEDUP_H
#define LFW_CORE_BASE_DEDUP_H

#include <functional>
#include <future>
#include <map>
#include <mutex>
#include <string>

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/**
 * 异步调用去重 — 对应 TS dedup
 *
 * 相同 key 的并发调用只执行一次，其余等待同一结果。
 * key 由调用方外部拼接（如 "className.methodName.argsMD5"）。
 *
 * @param key  去重键（调用方负责保证唯一性）
 * @param body 实际执行的逻辑
 * @return     共享的 std::future<T>
 */
template <typename T>
std::shared_future<T> deduped(const std::string &key, std::function<T()> body)
{
  static std::mutex mtx;
  static std::map<std::string, std::shared_future<T>> pending;

  std::lock_guard<std::mutex> lock(mtx);

  auto it = pending.find(key);
  if (it != pending.end())
    return it->second;

  auto fut = std::async(std::launch::async, [key, body = std::move(body)]() -> T
                        {
    T result = body();
    {
      std::lock_guard<std::mutex> lk(mtx);
      const_cast<std::map<std::string, std::shared_future<T>> &>(pending).erase(key);
    }
    return result; });

  auto shared = fut.share();
  pending[key] = shared;
  return shared;
}

LFW_NS_END

#endif
