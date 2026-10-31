# Spotify Playback & Playlist Engine (CLI)

![C++](https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Data Structures](https://img.shields.io/badge/Data%20Structures-Doubly%20Linked%20List%20%7C%20HashMap-orange?style=for-the-badge)
![Storage](https://img.shields.io/badge/Storage-File%20I%2FO-blueviolet?style=for-the-badge)

A console-based Spotify playback queue and playlist management engine implemented in C++. Built using a Doubly Linked List and Hash Map Indexing, it provides smooth track traversal, duplicate prevention, song search, persistent file storage, and a dynamic ad-injection simulation.

---

## Architecture & Design

The playback engine coordinates playback and playlist state using two core structures:
1. **Doubly Linked List**:
   - Represents the active track sequence.
   - Provides O(1) track skipping (`nextsong()` and `prevsong()`) without re-indexing.
   - Guarded with sentinel `head` and `tail` nodes to eliminate null-pointer boundary issues.
2. **Composite Hash Map (`unordered_map<string, Node*>`):**
   - Keys are generated as `"{Singer}_{SongName}"`.
   - Prevents duplicate tracks from being added in O(1) time.
   - Allows targeted song deletion in O(1) time without traversing the entire playlist.

```
                 Current Track
                       │
                       ▼
[Head] <---> [Song 1] <---> [Song 2] <---> [Song 3] <---> [Tail]
```

---

## Complexity

| Operation | Time Complexity | Space Complexity | Description |
| :--- | :---: | :---: | :--- |
| **`nextsong()` / `prevsong()`** | **O(1)** | O(1) | Immediate pointer traversal to adjacent track |
| **`addsong()`** | **O(1)** | O(1) | Hash lookup for duplicates + insertion at head |
| **`deletesong()`** | **O(1)** | O(1) | Hash lookup + node pointer detachment |
| **`searchsong()`** | **O(N)** | O(1) | Matches query against track titles and artist names |
| **`saveplaylist()` / `openplaylist()`** | **O(N)** | O(N) | Sequential File I/O to/from disk (`MyPlaylist.txt`) |

---

## Features

- **Bidirectional Playback**: Move forward and backward across tracks in constant O(1) time.
- **Queue Throttling**: Configurable capacity limit with automatic eviction of the oldest added tracks.
- **Duplicate Prevention**: Rejects duplicate songs instantly using composite key indexing.
- **Search System**: Case-aware keyword search that displays all matching songs and artists in the playlist.
- **File Persistence**: Save playlists to disk and reload them in future sessions using C++ File I/O (`fstream`).
- **Freemium Ad Simulation**: Dynamic ad injection that triggers a promotional banner and delay every 3 songs played.

---

## Sample CLI Output

```text
=================================================
             SPOTIFY PLAYBACK ENGINE             
=================================================
1. Create playlist
2. Add song
3. Delete song
4. Next song
5. Previous song
6. Save playlist
7. Open playlist
8. Search song
9. Exit
=================================================
Enter your choice: 4

Playing Next Song:
Track: Starboy | Artist: The Weeknd

=================================================
Upgrade to get ad-less music
=================================================
```

---

## How to Run

### Prerequisites
- A C++17 compatible compiler (e.g. MinGW GCC, Clang, or MSVC).

### Compilation & Execution

```bash
# 1. Compile the code
g++ -std=c++17 main.cpp -o spotify_engine

# 2. Run the executable (Windows)
.\spotify_engine.exe

# 2. Run the executable (Linux/macOS)
./spotify_engine
```

---

## Future Improvements
- [ ] Fisher-Yates algorithm for randomized queue shuffling.
- [ ] Circular linked list mode for seamless loop playback.
- [ ] Real audio decoding and playback using audio libraries (such as SFML Audio or miniaudio).

---

