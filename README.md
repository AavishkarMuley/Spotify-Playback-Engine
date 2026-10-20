# In-Memory LRU Cache System

![C++](https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Data Structures](https://img.shields.io/badge/Data%20Structures-HashMap%20%7C%20Doubly%20Linked%20List-orange?style=for-the-badge)
![Time Complexity](https://img.shields.io/badge/Complexity-O(1)%20Time-brightgreen?style=for-the-badge)


A fast, in-memory Least Recently Used (LRU) Cache built in C++. It utilizes a custom Doubly Linked List coupled with a Hash Map (`std::unordered_map`) to deliver strict O(1) time complexity for all key lookups, updates, and evictions, along with an interactive terminal visualizer.

---

## Architecture & Design

The cache uses a hybrid data structure:
- **Doubly Linked List (Node)**: Maintains access recency. The node right after `head` represents the Most Recently Used (MRU) item, while the node right before `tail` represents the Least Recently Used (LRU) item. Adding, deleting, and moving nodes occurs in O(1) time via pointer manipulation.
- **Hash Map (`unordered_map<int, Node*>`):** Provides instant O(1) access to any node in the list by its key.

```
[Head (MRU)] <---> [Key: 2 | Val: 20] <---> [Key: 1 | Val: 10] <---> [Tail (LRU)]
       ▲                      ▲
       │                      │
    Key: 2 ───────────────────┘
    (Hash Map Pointer Index)
```

---

## Complexity

| Operation | Time Complexity | Space Complexity | Description |
| :--- | :---: | :---: | :--- |
| **`get(key)`** | **O(1)** | O(1) | Hash lookup; moves accessed node to MRU position |
| **`put(key, value)`** | **O(1)** | O(1) | Inserts or updates node; evicts LRU if capacity reached |
| **Overall Space** | — | **O(C)** | Where C is the maximum configured cache capacity |

---

## Features

- **Constant Time Operations**: Guaranteed O(1) performance for both data retrieval and insertion.
- **Automatic LRU Eviction**: Automatically purges the oldest unaccessed item when the cache limit is exceeded.
- **Live Terminal Visualizer**: Shows the exact state and order of the cache from `[MRU]` to `[LRU]` in real time after every operation.
- **Clean Pointer Management**: Uses dummy sentinel head and tail nodes to prevent edge-case pointer errors and memory leaks.

---

## Sample CLI Output

```text
==========================
[MRU] -> |3|30|->|1|10|->|2|20| <- [LRU]
==========================
Enter the operation you want to perform
Enter 1 to insert data
Enter 2 to get data
Enter 3 to exit
```

---

## How to Run

### Prerequisites
- A C++17 compatible compiler (`g++`, `clang++`, or MSVC).

### Compilation & Execution

```bash
# 1. Compile the code
g++ -std=c++17 main.cpp -o lru_cache

# 2. Run the executable (Windows)
.\lru_cache.exe

# 2. Run the executable (Linux/macOS)
./lru_cache
```

---

## Future Improvements
- [ ] Add thread safety using mutexes (`std::mutex` / `std::shared_mutex`).
- [ ] Support generic key-value types using C++ templates (`template <typename K, typename V>`).
- [ ] Add key expiration with Time-to-Live (TTL).

---
