# 🧠 Memory Management Simulator

<div align="center">

![Memory Management](https://img.shields.io/badge/Memory-Management-blue?style=for-the-badge&logo=memory&logoColor=white)
![C Programming](https://img.shields.io/badge/C-Programming-orange?style=for-the-badge&logo=c&logoColor=white)
![Operating Systems](https://img.shields.io/badge/Operating-Systems-green?style=for-the-badge&logo=linux&logoColor=white)

**A comprehensive memory management simulator demonstrating virtual-to-physical address translation, TLB operations, page tables, and cache management.**

[📋 Features](#-features) • [🚀 Quick Start](#-quick-start) • [💻 Usage](#-usage) • [📊 Examples](#-examples) • [🎓 Learning Outcomes](#-learning-outcomes)

</div>

---

## 🔍 Overview

This project is a **Memory Management Simulator** written in C that demonstrates how modern operating systems handle memory management through paging. The simulator provides hands-on experience with:

- **Virtual-to-Physical Address Translation**
- **Translation Lookaside Buffer (TLB) Management**
- **Page Table Operations**
- **Cache Memory Simulation**
- **Page Fault Handling**

Perfect for understanding the inner workings of operating system memory management!

---

## ✨ Features

<table>
<tr>
<td align="center">🔄</td>
<td><strong>Address Translation</strong><br>Converts virtual addresses (0-65535) to physical addresses using paging</td>
</tr>
<tr>
<td align="center">⚡</td>
<td><strong>TLB Simulation</strong><br>8-entry Translation Lookaside Buffer with FIFO replacement policy</td>
</tr>
<tr>
<td align="center">📋</td>
<td><strong>Page Table Management</strong><br>Maps virtual pages to physical frames dynamically</td>
</tr>
<tr>
<td align="center">💾</td>
<td><strong>Cache Simulation</strong><br>16-block cache with hit/miss detection and FIFO replacement</td>
</tr>
<tr>
<td align="center">⚠️</td>
<td><strong>Page Fault Handling</strong><br>Simulates page loading from secondary storage</td>
</tr>
<tr>
<td align="center">📊</td>
<td><strong>Detailed Output</strong><br>Step-by-step breakdown of each memory access operation</td>
</tr>
</table>

---

## 🚀 Quick Start

### Prerequisites
- **GCC Compiler** (or any C compiler)
- **Basic understanding** of operating systems concepts

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/<your-username>/memory-management-simulator.git
   cd memory-management-simulator
   ```

2. **Compile the program**
   ```bash
   gcc Mem_simulator.c -o Mem_simulator
   ```

3. **Run the simulator**
   ```bash
   ./Mem_simulator
   ```

---

## 💻 Usage

### Interactive Mode
1. Launch the simulator: `./Mem_simulator`
2. Enter a virtual address (0-65535)
3. View the detailed translation process
4. Enter `-1` to exit

### Input Format
- **Valid Range**: 0 to 65535 (16-bit addresses)
- **Exit Command**: -1
- **Invalid addresses** outside the range are ignored

---

## ⚙️ System Configuration

<div align="center">

| Component | Specification | Description |
|-----------|---------------|-------------|
| **Memory Size** | 4 KB | Total physical memory |
| **Page Size** | 256 bytes | Fixed page/frame size |
| **Address Space** | 16-bit | 0 to 65535 virtual addresses |
| **TLB Entries** | 8 | Fast address translation cache |
| **Cache Blocks** | 16 | Data cache simulation |
| **Pages** | 256 | Total virtual pages (65536 ÷ 256) |
| **Frames** | 16 | Available physical frames (4096 ÷ 256) |
| **Replacement Policy** | FIFO | For both TLB and cache |

</div>

---

## 📊 Examples

### Example 1: TLB Hit & Cache Hit
```
Enter a virtual address (0 - 65535, -1 to exit): 56
┌─────────────────────────────────────────┐
│             TRANSLATION RESULT          │
├─────────────────────────────────────────┤
│ Virtual Address: 56                     │
│ Page Number: 0                          │
│ Offset: 56                              │
│ TLB: ✅ HIT                             │
│ Cache: ✅ HIT                           │
│ Physical Address: 56                    │
└─────────────────────────────────────────┘
```

### Example 2: Page Fault Scenario
```
Enter a virtual address (0 - 65535, -1 to exit): 5888
┌─────────────────────────────────────────┐
│             TRANSLATION RESULT          │
├─────────────────────────────────────────┤
│ Virtual Address: 5888                   │
│ Page Number: 23                         │
│ Offset: 0                               │
│ TLB: ❌ MISS                            │
│ Page Table: ❌ PAGE FAULT               │
│ Cache: ❌ MISS                          │
│ Physical Address: 1792                  │
│ Note: Page loaded from storage          │
└─────────────────────────────────────────┘
```

---

## 🧮 Address Translation Formula

The simulator uses these key formulas:

```c
// Extract page number and offset
page_number = virtual_address / PAGE_SIZE;    // PAGE_SIZE = 256
offset = virtual_address % PAGE_SIZE;

// Calculate physical address
physical_address = (frame_number * PAGE_SIZE) + offset;
```

**Why 256?** The page size is fixed at 256 bytes, making address calculation straightforward and efficient.

---

## 🏗️ Architecture Overview

```
Virtual Address (16-bit)
         ↓
┌─────────────────┐
│  Page | Offset  │
│   8   |   8     │  
└─────────────────┘
         ↓
┌─────────────────┐
│      TLB        │  ← Fast lookup (8 entries)
│    Lookup       │
└─────────────────┘
         ↓ (if miss)
┌─────────────────┐
│   Page Table    │  ← Main translation table
│    Lookup       │
└─────────────────┘
         ↓
┌─────────────────┐
│ Physical Memory │  ← Final address calculation
│   + Cache       │
└─────────────────┘
```

---

## 🎓 Learning Outcomes

After working with this simulator, you will understand:

### 🎯 **Core Concepts**
- How virtual memory provides the illusion of large, continuous address space
- The role of page tables in mapping virtual pages to physical frames
- Why TLBs are crucial for fast address translation performance

### 🔧 **Technical Skills**
- Address splitting into page number and offset components
- FIFO replacement algorithms for limited-size caches
- Page fault handling and memory allocation strategies

### 💡 **Practical Insights**
- Why page size affects system performance and memory utilization
- The trade-offs between TLB size and hit rates
- How cache hierarchies improve overall system performance

---

## 📚 Academic Context

**Course**: EEX5335 - Operating Systems  
**Institution**: The Open University of Sri Lanka  
**Department**: Electrical and Computer Engineering  

This simulator was developed as part of Lab-03 to provide hands-on experience with memory management concepts covered in operating systems theory.

---

## 📖 References

- **Abraham Silberschatz, Peter B. Galvin, Greg Gagne** - *Operating System Concepts* (Chapters 8 & 9)
- **GeeksforGeeks** - [Memory Management in Operating Systems](https://www.geeksforgeeks.org/operating-systems/memory-management-in-operating-system/)
- **Tutorials Point** - [OS Memory Management](https://www.tutorialspoint.com/operating_system/os_memory_management.htm)

---

## 👨‍💻 Author

**Kasun Mahela**   
Electrical and Computer Engineering  
The Open University of Sri Lanka

---

## 📄 License

This project is developed for educational purposes as part of an Operating Systems course. Feel free to use and modify for learning purposes.

---

<div align="center">

**⭐ Star this repository if it helped you understand memory management better!**

[🔝 Back to Top](#-memory-management-simulator)

</div>
