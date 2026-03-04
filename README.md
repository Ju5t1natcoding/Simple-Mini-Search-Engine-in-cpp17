# Simple Mini Search Engine (C++)

A command-line based Mini Search Engine implemented in modern C++, featuring:

* Inverted Index for fast exact word lookup
* Trie-based prefix autocomplete
* KMP (Knuth–Morris–Pratt) substring search
* Multi-document support
* Modular architecture

This project demonstrates practical usage of classical data structures and algorithms in an applied systems-style program.

---

# 🚀 Features

## 1. Inverted Index

Efficient word-to-document mapping:

```
word → [doc_id1, doc_id2, ...]
```

Allows near O(1) average-time exact word lookup.

---

## 2. Trie (Prefix Tree)

Used for:

* Fast prefix search
* Autocomplete suggestions
* Word frequency tracking

Supports:

* insert
* erase
* search
* prefix lookup
* autocomplete

---

## 3. KMP Substring Search

Efficient substring matching inside documents.

Time complexity:

* Preprocessing: O(m)
* Search: O(n)

Used for pattern search inside full document text.

---

## 4. Multi-Document Support

The engine supports loading multiple files:

```
load file1.txt
load file2.txt
```

Search operations are performed across all indexed documents.

---

# 🏗 Project Structure

```
.
├── main.cpp
├── Indexer.hpp
├── Trie.hpp
├── KMP.hpp
└── README.md
```

### Components

### `Trie`

Prefix tree implementation with:

* 256-character alphabet
* Word count tracking
* Autocomplete via DFS

### `KMP`

Knuth–Morris–Pratt pattern matching:

* LPS preprocessing
* Linear-time substring search

### `Indexer`

Core engine class responsible for:

* Loading documents
* Tokenization
* Building inverted index
* Managing search operations

### `main.cpp`

Command Line Interface:

* Parses commands
* Displays results
* Handles user interaction

---

# 💻 Build Instructions

### Requirements

* C++17 or later
* g++ / clang++ / MSVC

### Compile (Linux / macOS)

```bash
g++ -std=c++17 main.cpp -o search_engine
```

### Compile (Windows - MinGW)

```bash
g++ -std=c++17 main.cpp -o search_engine.exe
```

---

# 🧠 Usage

Run the executable:

```bash
./search_engine
```

Available commands:

```
load <file_path>        Load a text file
search <word>           Exact word search
substring <pattern>     Substring search using KMP
prefix <prefix>         Autocomplete suggestions
help                    Show command list
exit                    Exit program
```

---

# 🔍 Example Session

```
>> load data.txt
File loaded successfully.

>> search algorithm
Found in documents:
  Document 0

>> substring struct
Document 0 positions: 152 389

>> prefix alg
Suggestions:
  algorithm
  algorithms
```

---

# ⚙️ Implementation Details

## Tokenization

* Only alphabetic characters are considered part of words
* Case-sensitive indexing (by design choice)

## Inverted Index

Implemented using:

```cpp
std::unordered_map<std::string, std::vector<int32_t>>
```

Ensures:

* No duplicate document IDs per word
* Fast lookup performance

## Trie

* Fixed-size child array (256 ASCII)
* Depth-first search for autocomplete
* Memory cleaned via recursive destructor

## KMP

* Precomputes LPS array
* Supports efficient substring detection

---

# 📈 Time Complexity Overview

| Operation         | Complexity   |
| ----------------- | ------------ |
| Insert word       | O(L)         |
| Prefix search     | O(L + k)     |
| Exact word search | O(1) average |
| Substring search  | O(N + M)     |

Where:

* L = word length
* k = number of autocomplete results
* N = document length
* M = pattern length

---

# 🎯 Learning Objectives

This project demonstrates:

* Practical usage of classical algorithms
* Data structure integration
* Modular C++ design
* Command-line application development
* Memory management with dynamic structures
* Performance-oriented design decisions

---

# 🔮 Possible Improvements

Future enhancements could include:

* AND / OR multi-word queries
* Ranking (TF / TF-IDF)
* Case-insensitive mode
* Stop-word removal
* Persistent index storage
* File-based index serialization
* Unit tests
* GUI or Web interface
* Multi-threaded indexing

---

# 📌 Project Status

Version: **v1.0 — Simple Mini Search Engine**

This version includes:

* Exact search
* Substring search
* Autocomplete
* Multi-document indexing

---

# 🏷 Author

C++ implementation focused on algorithmic clarity and clean architecture.

---

# 📜 License

This project is intended for educational and portfolio purposes.
