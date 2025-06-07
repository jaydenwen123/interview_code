// 设计一个对象cache, 他支持下列两个基本操作:
// set(id, object), 根据id设置对象;
// get(id): 根据id得到一个对象;
// 同时它有下面几个性质:
// 1: x秒自动过期, 如果cache内的对象, x秒内没有被get或者set过, 则会自动过期;
// 2: 对象数限制, 该cache可以设置一个n, 表示cache最多能存储的对象数;
// 3: LRU置换, 当进行set操作时, 如果此时cache内对象数已经到达了n个,
// 则cache自动将最久未被使用过的那个对象剔除, 腾出空间放置新对象;
// 请你设计这样一个cache;

// 通过组合一些基本的数据结构,
// 来实现一些更高级的性质;

// 内部维护一个链表, list, 其元素为一个三元组(ID, timestamp, obj), 分别为对象ID,
// 上次被访问时间, 和对象内容; 在维护该list时, 需要保持一个性质,
// 越靠后的元素越新, 既timestamp越大; 内部再维护一个map,
// 该map表示一个ID到list节点的索引, 格式为map(ID, node); 对于get(id)操作: 1:
// 先在map中查找ID对应的list node; 2: 将node从list中取出, 即list.Remove(node);
// 3: 检查node.timestamp, 如果过期, 则返回null, 表示无数据, 并将ID从map中删除;
// 4: 如果未过期, 设置node.timestamp = now(), 并将node添加到list尾部,
// 即list.Append(node); 5: 返回node.obj; 对于set(id, obj)操作: 1:
// 同get(id)的1~3步操作, 删除对应的ID; 2: 如果此时空间满了, 既对象数为n,
// 则将list中表头的那个元素删除; 3: 更新list和map: node = new(ID, now(), obj),
// list.Append(node), map[ID] = node; 该题的cache有3个性质,
// 可随意组合选取不同的性质来实现, 当然实现得越多分越多;
// 能同时实现3个性质得全分, 写伪代码描述思路即可;
#include <list>
#include <unordered_map>
const static int64_t noExpireTime = -1;
template <typename K, typename V> class LRUCache {
public:
  LRUCache(int64_t capacity) : capacity_(capacity) {
    data_map_.reserve(capacity_);
  };
  bool set(const K &key, const V &val, int64_t expire_time = noExpireTime);
  bool get(const K &key, V &val);
  bool del(const K &key, V &val);

private:
  std::unordered_map<K, typename std::list<std::tuple<K, V, int64_t>>::iterator>
      data_map_;
  std::list<std::tuple<K, V, int64_t>> data_list_;
  int64_t capacity_;
};

template <typename K, typename V>
inline bool LRUCache<K, V>::set(const K &key, const V &val,
                                int64_t expire_time) {

  auto iter = data_map_.find(key);
  if (iter != data_map_.end()) {
    // 先移除
    data_list_.erase(iter->second);
    data_map_.erase(iter);
  }
  // 先判断元素是否存在
  if (data_map_.size() >= capacity_) {
    // 进行淘汰
    auto last = data_list_.back();
    data_list_.pop_back();
    data_map_.erase(std::get<0>(last));
  }

  auto item = std::make_tuple(key, val, expire_time);
  data_list_.emplace_front(item);
  data_map_[key] = data_list_.begin();
  //   如果之前不存在，就插入，如果存在就先删除，再插入
  return true;
}

template <typename K, typename V>
inline bool LRUCache<K, V>::get(const K &key, V &val) {
  auto iter = data_map_.find(key);
  if (iter == data_map_.end()) {
    return false;
  }
  std::tuple<K, V, int64_t> item = *(iter->second);
  int64_t expire_time = std::get<int64_t>(item);
  if (expire_time != noExpireTime &&
      expire_time < std::chrono::duration_cast<std::chrono::seconds>(
                        std::chrono::steady_clock::now().time_since_epoch())
                        .count()) {
    //   过期的数据删除
    data_list_.remove(item);
    data_map_.erase(iter);
    return false;
  }
  val = std::get<1>(item);
  // 刷新数据
  data_list_.splice(data_list_.begin(), data_list_, iter->second);
  data_map_[key] = data_list_.begin();
  return true;
}

template <typename K, typename V>
inline bool LRUCache<K, V>::del(const K &key, V &val) {
  // 先查找，然后再删除
  auto iter = data_map_.find(key);
  if (iter == data_map_.end()) {
    return false;
  }
  auto item = *(iter->second);
  int64_t expire_time = std::get<int64_t>(item);
  if (expire_time != noExpireTime &&
      expire_time < std::chrono::duration_cast<std::chrono::seconds>(
                        std::chrono::steady_clock::now().time_since_epoch())
                        .count()) {
    //   过期的数据删除
    data_list_.remove(iter->second);
    data_map_.erase(iter);
    return false;
  }
  val = std::get<1>(item);
  data_list_.remove(iter->second);
  data_map_.erase(iter);
  return true;
}
