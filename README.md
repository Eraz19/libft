# Libft Documentation

## Table of Contents
- [Overview](#overview)
- [Buffer Module](#buffer-module)
  - [Buffer Type Definitions](#buffer-type-definitions)
  - [Buffer Strategy Modes](#buffer-strategy-modes)
  - [Buffer Constructor Functions](#buffer-constructor-functions)
  - [Buffer Method Functions](#buffer-method-functions)
  - [Buffer Memory Management](#buffer-memory-management)
  - [Buffer Usage Examples](#buffer-usage-examples)
  - [Buffer Best Practices](#buffer-best-practices)
  - [Buffer Common Pitfalls](#buffer-common-pitfalls)
  - [Buffer Performance](#buffer-performance)
- [List Module](#list-module)
  - [List Type Definitions](#list-type-definitions)
  - [List Constructor Functions](#list-constructor-functions)
  - [List Access Functions](#list-access-functions)
  - [List Insertion Functions](#list-insertion-functions)
  - [List Iteration Functions](#list-iteration-functions)
  - [List Memory Management](#list-memory-management)
  - [List Usage Examples](#list-usage-examples)
  - [List Best Practices](#list-best-practices)
  - [List Common Pitfalls](#list-common-pitfalls)
  - [List Performance](#list-performance)
- [String Module](#string-module)
  - [String Type Definitions](#string-type-definitions)
  - [String Constructor Functions](#string-constructor-functions)
  - [String Comparison Functions](#string-comparison-functions)
  - [String Search Functions](#string-search-functions)
  - [String Insertion Functions](#string-insertion-functions)
  - [String Conversion Functions](#string-conversion-functions)
  - [String Iteration Functions](#string-iteration-functions)
  - [String Manipulation Functions](#string-manipulation-functions)
  - [String Memory Management](#string-memory-management)
  - [String Usage Examples](#string-usage-examples)
  - [String Best Practices](#string-best-practices)
  - [String Common Pitfalls](#string-common-pitfalls)
  - [String Performance](#string-performance)
- [Character Module](#character-module)
  - [Character Classification Functions](#character-classification-functions)
  - [Character Conversion Functions](#character-conversion-functions)
  - [Character Usage Examples](#character-usage-examples)
  - [Character Best Practices](#character-best-practices)
  - [Character Performance](#character-performance)
- [Math Module](#math-module)
  - [Absolute Value Functions](#absolute-value-functions)
  - [Math Usage Examples](#math-usage-examples)
  - [Math Best Practices](#math-best-practices)
  - [Math Performance](#math-performance)
- [Compilation and Usage](#compilation-and-usage)
  - [Building the Library](#building-the-library)
  - [Including Headers](#including-headers)
  - [Linking with Your Project](#linking-with-your-project)
  - [Module-Specific Headers](#module-specific-headers)
  - [Compilation Examples](#compilation-examples)
  - [Makefile Integration](#makefile-integration)
  - [Troubleshooting](#troubleshooting)
- [Integration and Interoperability](#integration-and-interoperability)
- [Thread Safety](#thread-safety)
- [Conclusion](#conclusion)

---

## Overview

**Libft** is a comprehensive C standard library implementation for 42 School projects. It provides essential data structures and utilities with a focus on performance, safety, and ease of use.

**Core Modules**:
- **Buffer Module**: Flexible raw memory buffer management
- **List Module**: Singly-linked list with size tracking
- **String Module**: Advanced string manipulation
- **Character Module**: Character classification and transformation
- **Math Module**: Mathematical utilities

This documentation covers the **Buffer**, **List**, **String**, **Character**, and **Math** modules in detail.

---

# Buffer Module

The **Buffer Module** provides a flexible and efficient system for managing raw memory buffers in C. It implements two complementary buffer types for different use cases.

**Key Features**:
- **Constant Buffers (`t_cbuf`)**: Immutable views into existing memory
- **Dynamic Buffers (`t_dbuf`)**: Growable, heap-allocated buffers
- **Growth Strategies**: Exact or exponential allocation modes
- **Type-Agnostic**: Work with any binary data
- **Zero-Copy Operations**: Efficient buffer slicing

This module is designed for scenarios requiring binary data manipulation, dynamic array management, and efficient memory operations without the constraints of null-terminated strings.

---

## Buffer Type Definitions

### `t_cbuf` - Constant Buffer
```c
typedef struct t_cbuffer
{
    const void  *data;   // Pointer to constant data
    size_t      size;    // Size of the buffer in bytes
} t_cbuf;
```

**Purpose**: Provides a read-only view into existing memory without ownership.

**Characteristics**:
- Does **not** own the memory it points to
- Cannot modify the underlying data
- Lightweight (no heap allocation)
- Ideal for passing data without copying

**Use Cases**:
- Passing binary data to functions
- Creating views into larger buffers
- Interfacing with const data

### `t_dbuf` - Dynamic Buffer
```c
typedef struct t_dbuffer
{
    void    *data;   // Pointer to allocated data
    size_t  size;    // Total allocated size in bytes
    size_t  len;     // Current used length in bytes
} t_dbuf;
```

**Purpose**: Provides a dynamically growable buffer with full memory ownership.

**Characteristics**:
- **Owns** the memory it manages (must be freed)
- Supports dynamic growth with configurable strategies
- Tracks both capacity (`size`) and usage (`len`)
- Can be resized automatically on insertion

**Use Cases**:
- Building binary data structures dynamically
- Managing arrays of arbitrary types
- Buffer accumulation patterns

## Buffer Strategy Modes

### `t_buf_strat` - Buffer Growth Strategy
```c
typedef enum e_buf_strategy
{
    E_,   // Exact allocation: allocate only what's needed
    x2_,  // Exponential growth: double capacity when needed
} t_buf_strat;
```

**`E_` (Exact Mode)**:
- Allocates only the exact amount needed
- Minimizes memory usage
- Causes more frequent reallocations
- **Use when**: Memory is constrained, or final size is known

**`x2_` (Double Mode)**:
- Doubles the buffer capacity when expansion is needed
- Reduces reallocation frequency
- Trades memory for performance
- **Use when**: Many insertions expected, or performance is critical

## Buffer Constructor Functions

### `cbuf()` - Create Constant Buffer from Data
```c
t_cbuf cbuf(const void *data, size_t size);
```

**Description**: Creates a constant buffer view pointing to existing data.

**Parameters**:
- `data`: Pointer to the constant data
- `size`: Size of the data in bytes

**Returns**: A `t_cbuf` with:
- `data`: Points to the input data
- `size`: Equal to the input size

**Example**:
```c
int arr[] = {1, 2, 3, 4, 5};
t_cbuf buf = cbuf(arr, sizeof(arr));
// buf.data points to arr, buf.size = 20
```

**Error Handling**: Returns a null buffer (`data=NULL, size=0`) if input `data` is `NULL`.

**Memory**: Does **not** allocate or copy memory. The original data must remain valid.

### `cbuf_d()` - Convert Dynamic Buffer to Constant Buffer
```c
t_cbuf cbuf_d(t_dbuf buf);
```

**Description**: Creates a constant buffer view from a dynamic buffer, using only the active portion (`len`).

**Parameters**:
- `buf`: The dynamic buffer to create a view from

**Returns**: A `t_cbuf` with:
- `data` pointing to `buf.data`
- `size` set to `buf.len`

**Example**:
```c
t_dbuf dbuf = dbuf_s(100);
dbuf.len = 10;  // Only 10 bytes are used
t_cbuf cbuf = cbuf_d(dbuf);
// cbuf.size = 10 (not 100)
```

**Error Handling**: Returns a nullbuffer (`data=NULL, size=0`) if input `buf.data` is `NULL`.

**Memory**: Does **not** take ownership. Original `dbuf` must still be freed separately.

### `dbuf_s()` - Create Dynamic Buffer with Size
```c
t_dbuf dbuf_s(size_t size);
```

**Description**: Allocates a new dynamic buffer with the specified capacity, initialized to zero.

**Parameters**:
- `size`: Number of bytes to allocate

**Returns**: A `t_dbuf` with:
- `data`: Allocated and zero-initialized memory
- `size`: Equal to the requested size
- `len`: Initialized to 0

**Example**:
```c
t_dbuf buf = dbuf_s(1024);
// buf.data = allocated 1024 bytes (all zeros)
// buf.size = 1024
// buf.len = 0
```

**Error Handling**: Returns a null buffer (`data=NULL, size=0, len=0`) on allocation failure.

**Memory**: Caller is responsible for freeing with `free_dbuf()`.

### `dbuf_c()` - Create Dynamic Buffer from Constant Buffer
```c
t_dbuf dbuf_c(t_cbuf buf);
```

**Description**: Creates a new dynamic buffer by copying data from a constant buffer.

**Parameters**:
- `buf`: The constant buffer to copy from

**Returns**: A new `t_dbuf` containing a copy of the data with:
- `data`: New allocated memory with copied content
- `size`: Equal to `buf.size`
- `len`: Equal to `buf.size` (buffer is "full")

**Example**:
```c
const char *str = "Hello";
t_cbuf cbuf = cbuf(str, 5);
t_dbuf dbuf = dbuf_c(cbuf);
// dbuf contains a heap-allocated copy of "Hello"
// dbuf.len = 5, dbuf.size = 5
```

**Error Handling**: Returns a null buffer (`data=NULL, size=0, len=0`) on allocation failure or if input is NULL.

**Memory**: Allocates new memory. Caller must free with `free_dbuf()`.

### `dbuf_d()` - Create Dynamic Buffer from Dynamic Buffer
```c
t_dbuf dbuf_d(t_dbuf buf);
```
**Description**: Creates a new dynamic buffer by copying data from another dynamic buffer.

**Parameters**:
- `buf`: The dynamic buffer to copy from

**Returns**: A new `t_dbuf` containing a copy of the data with:
- `data`: New allocated memory with copied content
- `size`: Equal to `buf.size`
- `len`: Equal to `buf.len`

**Example**:
```c
t_dbuf original = dbuf_s(100);
original.len = 50; // Assume 50 bytes are used
t_dbuf copy = dbuf_d(original);
// copy contains a heap-allocated copy of the first 50 bytes of original
// copy.len = 50, copy.size = 100
```

**Error Handling**: Returns a null buffer (`data=NULL, size=0, len=0`) on allocation failure or if input is NULL.

**Memory**: Allocates new memory. Caller must free with `free_dbuf()`.

## Buffer Method Functions

### Buffer Insertion Functions

#### `buf_insertc()` - Insert Constant Buffer
```c
t_dbuf buf_insertc(t_dbuf buf, t_cbuf insrt, size_t i, t_buf_strat mode);
```

**Description**: Inserts a constant buffer into a dynamic buffer at the specified position.

**Parameters**:
- `buf`: The dynamic buffer to insert into (may be reallocated)
- `insrt`: The constant buffer to insert
- `i`: Insertion index in bytes
- `mode`: Growth strategy (`E_` or `x2_`)

**Returns**: The resulting dynamic buffer (may be a new allocation).

**Behavior**:
1. If i is greater than `buf.len`, inserts at the end
2. Reallocates if needed based on `mode`
3. Updates `buf.len` accordingly and `buf.size` if reallocated
4. If `insrt.data` is NULL, no insertion occurs and original `buf` is returned
5. If `buf.data` is NULL, returns a new buffer copied from `insrt`

**Memory Ownership**:

⚠️ **CRITICAL**: If reallocation occurs:
1. The original `buf` pointer is freed and invalidated.
2. The returned buffer must be reassigned to avoid dangling pointers.
Always reassign:
```c
	buf = buf_insertc(buf, insrt, i, mode);  // ✓ Correct
	buf_insertc(buf, insrt, i, mode);        // ✗ Memory leak!
```

**Example**:
```c
t_dbuf buf = dbuf_s(10);

buf = buf_insertc(buf, cbuf("DEF", 3), 3, E_);
// buf now contains "DEF" at the beginning because i (3) > buf.len (0)
//	so insertion happens at the end of the empty buffer (i.e., at index 0)
// buf.len = 3
// No reallocation needed

buf = buf_insertc(buf, cbuf("ABC", 3), 0, E_);
// buf now contains "ABCDEF" because "ABC" is inserted at index 0 (prepended)
// buf.len = 6
// No reallocation needed

buf = buf_insertc(buf, cbuf("GHI", 3), buf.len, E_);
// buf now contains "ABCDEFGHI" because "GHI" is appended at the end (index buf.len)
// buf.len = 9
// No reallocation needed

buf = buf_insertc(buf, cbuf("JKL", 3), buf.len, E_);
// buf now contains "ABCDEFGHIJKL" because "JKL" is appended at the end
// buf.len = 12
// Reallocation occurs since initial size was 10 with E_ mode so new size is exactly 12

buf = buf_insertc(buf, cbuf("MNO", 3), buf.len, x2_);
// buf now contains "ABCDEFGHIJKLMNO" because "MNO" is appended at the end
// buf.len = 15
// Reallocation occurs since initial size was 12, new size is 24 (doubled initial size (12))
// 	with x2_ mode
```

**Error Handling**: On reallocation failure, returns a null buffer (`data=NULL, size=0, len=0`) and the original `buf` is freed. Users must check for NULL and handle the failure appropriately.

**Example Error Handling**:
```c
buf = buf_insertc(buf, insrt, i, x2_);
if (buf.data == NULL)
{
    perror("Fatal: allocation failed");
    exit(EXIT_FAILURE);
}
```

#### `buf_insert()` - Insert Dynamic Buffer
```c
t_dbuf buf_insert(t_dbuf buf, t_dbuf insrt, size_t i, t_buf_strat mode);
```

**Description**: Inserts a dynamic buffer into another dynamic buffer at the specified position.

**Parameters**:
- `buf`: The dynamic buffer to insert into (may be reallocated)
- `insrt`: The dynamic buffer to insert (**will be freed**)
- `i`: Insertion index in bytes
- `mode`: Growth strategy (`E_` or `x2_`)

**Returns**: The resulting dynamic buffer (may be a new allocation).

**Behavior**: 
1. If i is greater than `buf.len`, inserts at the end
2. Reallocates if needed based on `mode`
3. Updates `buf.len` accordingly and `buf.size` if reallocated
4. **Consumes** (frees) the `insrt` buffer.
5. If `insrt.data` is NULL, no insertion occurs and original `buf` is returned
6. If `buf.data` is NULL, returns a new buffer copied from `insrt`

**Memory Ownership**:

⚠️ **CRITICAL**: If reallocation occurs:
1. The original `buf` pointer is freed and invalidated.
2. The returned buffer must be reassigned to avoid dangling pointers.
Always reassign:
```c
	buf = buf_insert(buf, insrt, i, mode);  // ✓ Correct
	buf_insert(buf, insrt, i, mode);        // ✗ Memory leak!
```

**Example**:
```c
t_dbuf buf = dbuf_s(10);

t_dbuf insrt1 = dbuf_c(cbuf("DEF", 3));
buf = buf_insert(buf, insrt1, 3, E_);
insrt1.data // is now invalid (freed in buf_insert)
// buf now contains "DEF" at the beginning because i (3) > buf.len (0)
//	so insertion happens at the end of the empty buffer (i.e., at index 0)
// buf.len = 3
// No reallocation needed

t_dbuf insrt2 = dbuf_c(cbuf("ABC", 3));
t_dbuf insrt3 = dbuf_d(insrt2);
buf = buf_insert(buf, dbuf_c(cbuf("ABC", 3)), 0, E_);
insrt2.data // is now invalid (freed in buf_insert)
insrt3.data // is still valid, this is a way to keep a copy if needed
// buf now contains "ADEFBC" because "ABC" is inserted at index 0 (prepended)
// buf.len = 6
// No reallocation needed

buf = buf_insert(buf, dbuf_c(cbuf("GHI", 3)), buf.len, E_);
// buf now contains "ADEFBCGHI" because "GHI" is appended at the end (index buf.len)
// buf.len = 9
// No reallocation needed

buf = buf_insert(buf, dbuf_c(cbuf("JKL", 3)), buf.len, E_);
// buf now contains "ADEFBCGHJKL" because "JKL" is appended at the end
// buf.len = 12
// Reallocation occurs since initial size was 10 with E_ mode so new size is exactly 12

buf = buf_insert(buf, dbuf_c(cbuf("MNO", 3)), buf.len, x2_);
// buf now contains "ADEFBCGHJKLMNO" because "MNO" is appended at the end
// buf.len = 15
// Reallocation occurs since initial size was 12, new size is 24 (doubled initial size (12))
// 	with x2_ mode
```

**Error Handling**: Returns a new buffer from `insrt` if `buf.data` is NULL. On reallocation failure, returns a null buffer (`data=NULL, size=0, len=0`) and both `buf` and `insrt` are freed. Users must check for NULL and handle the failure appropriately.

**Example Error Handling**:
```c
buf = buf_insert(buf, insrt, i, x2_);
if (buf.data == NULL)
{
    perror("Fatal: allocation failed");
    exit(EXIT_FAILURE);
}
```

### Buffer Exploration Functions

#### `buf_shift()` - Shift Constant Buffer
```c
t_cbuf buf_shift(t_cbuf buf, size_t offset);
```

**Description**: Creates a new view into a buffer by advancing the pointer by `offset` bytes.

**Parameters**:
- `buf`: The constant buffer to shift
- `offset`: Number of bytes to advance the pointer

**Returns**: A new `t_cbuf` of the remaining buffer after shifting and tracking the size of the remaining data.

**Behavior**:
1. If `buf.data == NULL`, returns `buf` unchanged
2. If `offset` > `buf.size`, returns empty buffer (`data=NULL, size=0`) to indicate no data left

**Example**:
```c
t_cbuf buf = cbuf("ABCDEFGH", 8);

t_cbuf rest = buf_shift(buf, 3);
// rest.data points to "DEFGH" (data + 3)
// rest.size = 5

t_cbuf empty = buf_shift(buf, 100);
// empty.data = NULL, empty.size = 0
```

## Buffer Memory Management

### `free_dbuf()` - Free Dynamic Buffer
```c
void free_dbuf(t_dbuf *buf);
```

**Description**: Frees the memory allocated for a dynamic buffer and resets its fields.

**Parameters**:
- `buf`: Pointer to the dynamic buffer to free

**Returns**: None

**Behavior**:
1. Frees `buf->data` if not NULL (safe no-op if already freed)
2. Resets `buf->len = 0`
3. Resets `buf->size = 0`
4. Sets `buf->data = NULL`

**Example**:
```c
t_dbuf buf = dbuf_s(100);
// ... use buffer ...
free_dbuf(&buf);
// buf is now {NULL, 0, 0}
```

### Buffer Memory Ownership Rules

#### Constant Buffers (`t_cbuf`)
- **Never** own memory
- Can point to stack, static, or heap memory owned by others
- Do **not** call `free()` on `cbuf.data`
- Need to ensure the underlying memory outlives the `t_cbuf`

#### Dynamic Buffers (`t_dbuf`)
- **Always** own their memory
- Must be freed with `free_dbuf()` when done
- Can be transferred/consumed by functions like `buf_insert()`
- After consumption, the buffer is invalid

#### Functions That Consume Buffers
These functions free their input and return new buffers:
- `buf_insert()`: Always frees `insrt`
- `buf_insertc()` / `buf_insert()`: May free and reallocate `buf`

**Golden Rule**: Always reassign when calling consuming functions:
```c
buf_insert(buf, other_buf, 0, x2_);			// ✗ WRONG - Memory leak if buf is reallocated
buf = buf_insert(buf, other_buf, 0, x2_);	// ✓ CORRECT
```

## Buffer Usage Examples

### Example 1: Basic Buffer Creation and Manipulation
```c
#include "libft.h"

void example_basic(void)
{
    // Create a dynamic buffer
    t_dbuf buf = dbuf_s(16);
    // Create constant buffer from data
    t_cbuf greeting = cbuf("Hello", 5);
    
    // Insert data
    buf = buf_insertc(buf, greeting, 0, x2_);    
    // buf now contains "Hello"
    // buf.len = 5, buf.size = 16
    
    // Clean up
    free_dbuf(&buf);
}
```

### Example 2: Building an Array Dynamically
```c
#include "libft.h"

void example_int_array(void)
{
    // Create buffer for integers
    t_dbuf int_buf = dbuf_s(sizeof(int) * 4);
    
    // Add integers one by one
    for (int i = 1; i <= 10; i++)
    {
        t_cbuf num = cbuf(&i, sizeof(int));
        int_buf = buf_insertc(int_buf, num, int_buf.len, x2_);
    }
    
    // Access the array
    int *array = (int *)int_buf.data;
    size_t count = int_buf.len / sizeof(int);
    
	printf("%d", count);
	// Output: 10
    for (size_t i = 0; i < count; i++)
        printf("%d ", array[i]);
    // Output: 1 2 3 4 5 6 7 8 9 10

    free_dbuf(&int_buf);
}
```

### Example 3: Binary Data Parsing
```c
#include "libft.h"

void example_parsing(void)
{
    // Simulate binary data stream
    uint8_t data[] = {0xFF, 0xFE, 0x01, 0x02, 0x03, 0x04};
    t_cbuf stream = cbuf(data, sizeof(data));
    
    // Read header (2 bytes)
    uint8_t *header = (uint8_t *)stream.data;
    printf("Header: 0x%02X%02X\n", header[0], header[1]);
	// Output: Header: 0xFFFE
    
    // Shift past header
    stream = buf_shift(stream, 2);
    
    // Process remaining data
    while (stream.size > 0)
    {
        uint8_t *byte = (uint8_t *)stream.data;
        printf("Byte: 0x%02X\n", *byte);
		// Output loop 1: "Byte: 0x01"
		// Output loop 2: "Byte: 0x02"
		// ...
        stream = buf_shift(stream, 1);
    }
}
```

### Example 4: Buffer Merging
```c
#include "libft.h"

void example_merge(void)
{
    t_dbuf buf1 = dbuf_c(cbuf("First", 5));
    t_dbuf buf2 = dbuf_c(cbuf("Second", 6));
    
    t_dbuf merged = buf_insert(buf1, buf2, buf1.len, E_);
    // merged contains "FirstSecond"
    // buf1 and buf2 are both freed and invalid now

    free_dbuf(&merged);
}
```

### Example 5: Keep a Copy of Inserted Buffer
```c
#include "libft.h"
void example_keep_copy(void)
{
	t_dbuf buf = dbuf_s(10);
	
	t_dbuf to_insert = dbuf_c(cbuf("Data", 4));
	t_dbuf to_insert_copy = dbuf_d(to_insert); // Create a copy before insertion

	buf = buf_insert(buf, to_insert, 0, x2_);
	// to_insert is now freed and invalid
	// to_insert_copy is still valid and can still be used for other purposes

	free_dbuf(&to_insert_copy);
	free_dbuf(&buf);
}
```

## Buffer Best Practices

### 1. **Always Reassign After Insert Operations**
```c
// ✓ CORRECT
buf = buf_insert(buf, other, 0, x2_);
buf = buf_insertc(buf, cbuf_data, 0, x2_);

// ✗ WRONG - Memory leak if buf is reallocated
buf_insert(buf, other, 0, x2_);
```

### 2. **Check for Allocation Failures**
```c
t_dbuf buf = dbuf_s(1024);
if (buf.data == NULL)
{
    // Handle allocation failure
    return ERROR;
}
```

### 3. **Use x2_ Mode for Repeated Insertions**
```c
// Efficient: O(n) total time
t_dbuf buf = dbuf_s(0);
for (int i = 0; i < 1000; i++)
    buf = buf_insertc(buf, data, buf.len, x2_);  // Amortized O(1)

// Inefficient: O(n²) total time
for (int i = 0; i < 1000; i++)
    buf = buf_insertc(buf, data, buf.len, E_);   // Always realloc
```

### 4. **Use E_ Mode When Size is Known**
```c
// If you know you need exactly 100 elements
t_dbuf buf = dbuf_s(100 * sizeof(int));
// Use E_ since we won't grow beyond this
buf = buf_insertc(buf, item, buf.len, E_);
```

### 5. **Use Const Buffers for Read-Only Operations**
```c
// Pass by const buffer to avoid copies
void print_data(t_cbuf data)
{
    // data is just a view, no ownership
}

t_dbuf my_buf = create_data();
print_data(cbuf_d(my_buf));
free_dbuf(&my_buf);
```

### 6. **Keep a Copy of Inserted Buffers if Needed**
```c
t_dbuf to_insert = dbuf_c(cbuf("Data", 4));
t_dbuf to_insert_copy = dbuf_d(to_insert); // Create a copy before insertion
buf = buf_insert(buf, to_insert, 0, x2_);
// to_insert is now freed and invalid
// to_insert_copy is still valid
```

## Buffer Common Pitfalls

### ❌ Pitfall 1: Not Reassigning After Insert
```c
t_dbuf buf = dbuf_s(10);
buf_insertc(buf, data, 0, x2_);  // If realloc happens, buf is now invalid!
// Using buf here = undefined behavior
```

**Solution**:
```c
buf = buf_insertc(buf, data, 0, x2_);  // ✓
```

### ❌ Pitfall 2: Using Buffer After buf_insert Consumption
```c
t_dbuf buf1 = dbuf_s(10);
t_dbuf buf2 = dbuf_s(10);
buf1 = buf_insert(buf1, buf2, 0, x2_);
free_dbuf(&buf2);  // ✗ Double free! buf2 already freed
```

**Solution**:
```c
buf1 = buf_insert(buf1, buf2, 0, x2_);
// Don't touch buf2 again, it's gone
```

### ❌ Pitfall 3: Freeing Constant Buffer Data
```c
const char *str = "Hello";
t_cbuf buf = cbuf(str, 5);
free((void *)buf.data);  // ✗ Freeing string literal!
```

**Solution**:
```c
// Don't free const buffer data - you don't own it
```

# String Module

The **String Module** provides an advanced string manipulation system built on top of the buffer module. It implements two complementary string types that combine the power of C strings with modern safety and convenience features.

**Key Features**:
- **Constant Strings (`t_cstr`)**: Immutable string views with length tracking
- **Dynamic Strings (`t_dstr`)**: Growable, heap-allocated strings
- **Automatic Length Tracking**: No need for strlen() calls
- **Type Conversions**: Convert between integers, longs, and strings with any base
- **Rich API**: Split, trim, find, compare, and more
- **Null-Terminated**: Compatible with standard C string functions

This module is designed for efficient string manipulation while maintaining safety and avoiding common C string pitfalls like buffer overflows.

---

## String Type Definitions

### `t_cstr` - Constant String
```c
typedef struct t_cstring
{
    const t_i8  *s;      // Pointer to the string data
    size_t      len;     // Length without null terminator
    size_t      size;    // Total size including null terminator
} t_cstr;
```

**Purpose**: Provides an immutable string view with pre-calculated length.

**Characteristics**:
- Does **not** own the memory it points to
- Always null-terminated (when created from valid C string)
- Pre-computed `len` for O(1) length queries
- `size = len + 1` (includes null terminator)
- Lightweight, can be passed by value
- Compatible with standard C string functions

**Use Cases**:
- Function parameters (pass strings without copying)
- Viewing substrings of existing strings
- Working with string literals
- Avoiding repeated strlen() calls

### `t_dstr` - Dynamic String
```c
typedef struct t_dstring
{
    t_i8    *s;      // Pointer to the string data
    size_t  len;     // Length without null terminator
    size_t  size;    // Total allocated size
} t_dstr;
```

**Purpose**: Provides a growable, heap-allocated string with ownership.

**Characteristics**:
- **Owns** the memory it manages (must be freed)
- Always null-terminated
- Tracks both length (`len`) and capacity (`size`)
- Can grow dynamically through insertion operations
- Compatible with standard C string functions

**Use Cases**:
- Building strings dynamically
- String concatenation
- String modification
- Temporary string buffers

## String Constructor Functions

### `cstr()` - Create Constant String from C String
```c
t_cstr cstr(const t_i8 *s);
```

**Description**: Creates a constant string structure from a null-terminated C string.

**Parameters**:
- `s`: Pointer to a null-terminated string

**Returns**: A `t_cstr` with:
- `s`: Points to the input string
- `len`: Length of the string (computed)
- `size`: `len + 1`

**Example**:
```c
t_cstr str = cstr("Hello, World!");
// str.s = "Hello, World!"
// str.len = 13
// str.size = 14
```

**Error Handling**: Returns a null string (`s=NULL, len=0, size=0`) if input is NULL.

**Memory**: Does **not** allocate or copy memory. The original string must remain valid.

### `cstr_d()` - Convert Dynamic String to Constant String
```c
t_cstr cstr_d(t_dstr str);
```

**Description**: Creates a constant string view from a dynamic string.

**Parameters**:
- `str`: The dynamic string to create a view from

**Returns**: A `t_cstr` with:
- `s`: Points to the dynamic string's data
- `len`: Length of the dynamic string
- `size`: Size of the dynamic string

**Example**:
```c
t_dstr dynamic = dstr_c(cstr("Hello"));
t_cstr view = cstr_d(dynamic);
// view references dynamic's data
```

**Error Handling**: Returns a null string (`s=NULL, len=0, size=0`) if input `str.s` is NULL.

**Memory**: Does not take ownership. Original must be freed separately.

### `dstr_s()` - Create Dynamic String with Size
```c
t_dstr dstr_s(size_t size);
```

**Description**: Allocates a new empty dynamic string with the specified capacity.

**Parameters**:
- `size`: Number of bytes to allocate (should include space for null terminator)

**Returns**: A `t_dstr` with:
- `s`: Allocated and null-initialized
- `len`: `0`
- `size`: Equal to requested size

**Example**:
```c
t_dstr str = dstr_s(100);
// str.s is allocated 100 bytes
// str.s[0] = '\0'
// str.len = 0
// str.size = 100
```

**Error Handling**: Returns a null string (`s=NULL, len=0, size=0`) on allocation failure or if size is 0.

**Memory**: Caller is responsible for freeing with `free_dstr()`.

### `dstr_c()` - Create Dynamic String from Constant String
```c
t_dstr dstr_c(t_cstr str);
```

**Description**: Creates a new dynamic string by copying a constant string.

**Parameters**:
- `str`: The constant string to copy

**Returns**: A new `t_dstr` containing a copy of the string with:
- `s`: New allocated memory with copied content
- `len`: Equal to `str.len`
- `size`: Equal to `str.len + 1`

**Example**:
```c
t_cstr src = cstr("Hello");
t_dstr copy = dstr_c(src);
// copy.s contains a heap-allocated copy of "Hello"
// copy.len = 5
// copy.size = 6
```

**Error Handling**: Returns a null string (`s=NULL, len=0, size=0`) on allocation failure or if input `str.s` is NULL.

**Memory**: Allocates new memory. Must be freed with `free_dstr()`.

### `dstr_d()` - Create Dynamic String from Dynamic String
```c
t_dstr dstr_d(t_dstr str);
```

**Description**: Creates a new dynamic string by copying another dynamic string.

**Parameters**:
- `str`: The dynamic string to copy

**Returns**: A new `t_dstr` containing a copy of the string with:
- `s`: New allocated memory with copied content
- `len`: Equal to `str.len`
- `size`: Equal to `str.size`

**Example**:
```c
t_dstr original = dstr_c(cstr("Hello"));
t_dstr copy = dstr_d(original);
// copy.s contains a heap-allocated copy of "Hello"
// copy.len = 5
// copy.size = 6
```

**Error Handling**: Returns a null string (`s=NULL, len=0, size=0`) on allocation failure or if input `str.s` is NULL.

**Memory**: Allocates new memory. Must be freed with `free_dstr()`.

## String Method Functions

### String Insertion Functions

#### `str_insertc()` - Insert Constant String
```c
t_dstr str_insertc(t_dstr str, t_cstr insrt, size_t i);
```

**Description**: Inserts a constant string into a dynamic string at a specific index.

**Parameters**:
- `str`: Dynamic string to insert into (**will be freed**)
- `insrt`: Constant string to insert
- `i`: Character index for insertion

**Returns**: A new dynamic string with both the original and inserted content.

**Behavior**:
1. If `i` is greater than `str.len`, inserts at the end
2. Always allocates new string sized `str.len + insrt.len + 1`
3. Frees original `str` and returns new string
4. If both `str.s` and `insrt.s` are NULL, returns null string `{s=NULL, len=0, size=0}`

**Memory Ownership**:

⚠️ **CRITICAL**: Always allocates new memory:
1. The original `str` pointer is freed and invalidated.
2. The returned buffer must be reassigned to avoid dangling pointers.
Always reassign:
```c
	str = str_insertc(str, insrt, i);  // ✓ Correct
	str_insertc(str, insrt, i);        // ✗ Memory leak!
```

**Example**:
```c
t_dstr str_init = dstr_s(0);
t_dstr str;

str = str_insertc(str_init, cstr("DEF"), 3);
str_init.s // is now invalid (freed in str_insertc)
// str now contains "DEF" at the beginning because i (3) > str.len (0)
//	so insertion happens at the end of the empty string (i.e., at index 0)
// str.len = 3
// str.size = 4
// Allocate new memory

str = str_insertc(str, cstr("ABC"), 0);
// str now contains "ABCDEF" because "ABC" is inserted at index 0 (prepended)
// str.len = 6
// str.size = 7
// Allocate new memory

str = str_insertc(str, cstr("GHI"), str.len);
// str now contains "ABCDEFGHI" because "GHI" is appended at the end (index str.len)
// str.len = 9
// str.size = 10
// Allocate new memory
```

**Error Handling**: Returns a null string (`s=NULL, len=0, size=0`) on allocation failure. The original `str` is freed before returning NULL. Users must check for NULL and handle the failure appropriately.

**Example Error Handling**:
```c
str = str_insertc(str, insrt, i);
if (str.s == NULL)
{
    perror("Fatal: allocation failed");
    exit(EXIT_FAILURE);
}
```

#### `str_insert()` - Insert Dynamic String
```c
t_dstr str_insert(t_dstr str, t_dstr insrt, size_t i);
```

**Description**: Inserts a dynamic string into another dynamic string at a specific index.

**Parameters**:
- `str`: String to insert into (**will be freed**)
- `insrt`: String to insert (**will be freed**)
- `i`: Character index for insertion

**Returns**: A new dynamic string with both the original and inserted content.

**Behavior**:
1. If `i` is greater than `str.len`, inserts at the end
2. Always allocates new string sized `str.len + insrt.len + 1`
3. Frees both original `str` and `insrt`, returns new string
4. If both `str.s` and `insrt.s` are NULL, returns null string `{s=NULL, len=0, size=0}`

**Memory Ownership**:

⚠️ **CRITICAL**: Always allocates new memory:
1. The original `str` and `insrt` pointers are freed and invalidated.
2. The returned buffer must be reassigned to avoid dangling pointers.
Always reassign:
```c
	str = str_insert(str, insrt, i);  // ✓ Correct
	str_insert(str, insrt, i);        // ✗ Memory leak!
```

**Example**:
```c
t_dstr str_init = dstr_s(0);
t_dstr insrt = dstr_c(cstr("DEF"));
t_dstr str;

str = str_insert(str_init, insrt, 3);
str_init.s // is now invalid (freed in str_insert)
insrt.s    // is now invalid (freed in str_insert)
// str now contains "DEF" at the beginning because i (3) > str.len (0)
//	so insertion happens at the end of the empty string (i.e., at index 0)
// str.len = 3
// str.size = 4
// Allocate new memory

str = str_insert(str, dstr_c(cstr("ABC")), 0);
// str now contains "ABCDEF" because "ABC" is inserted at index 0 (prepended)
// str.len = 6
// str.size = 7
// Allocate new memory

str = str_insert(str, dstr_c(cstr("GHI")), str.len);
// str now contains "ABCDEFGHI" because "GHI" is appended at the end (index str.len)
// str.len = 9
// str.size = 10
// Allocate new memory
```

**Error Handling**: Returns a null string (`s=NULL, len=0, size=0`) on allocation failure. Both `str` and `insrt` are freed before returning NULL. Users must check for NULL and handle the failure appropriately.

**Example Error Handling**:
```c
str = str_insert(str, insrt, i);
if (str.s == NULL)
{
    perror("Fatal: allocation failed");
    exit(EXIT_FAILURE);
}
```

### String Exploration Functions

#### `str_shift()` - Shift String View
```c
t_cstr str_shift(t_cstr str, size_t offset);
```

**Description**: Creates a new view into a string by advancing the pointer by `offset` characters.

**Parameters**:
- `str`: String to shift
- `offset`: Number of characters to skip

**Returns**: A new `t_cstr` of the remaining string after shifting and tracking the length of the remaining string and size.

**Behavior**:
1. If `str.s == NULL`, returns `str` unchanged
2. If `offset` >= `str.len`, returns empty string (`s=NULL, len=0, size=0`) to indicate no data left

**Example**:
```c
t_cstr str = cstr("Hello, World!");
t_cstr shifted = str_shift(str, 7);
// shifted.s points to "World!"
// shifted.len = 6

t_cstr empty = str_shift(str, 100);
// empty.s = NULL, empty.len = 0, empty.size = 0
```

### String Comparison Functions

#### `str_cmp()` - Compare Strings
```c
t_i32 str_cmp(t_cstr str1, t_cstr str2);
```

**Description**: Lexicographically compares two strings (can be used to check string equality).

**Parameters**:
- `str1`: First string to compare
- `str2`: Second string to compare

**Returns**: The difference between the first differing characters:
- `< 0` if `str1` is less than `str2`
- `0` if they are equal
- `> 0` if `str1` is greater than `str2`

**Example**:
```c
t_cstr a = cstr("apple");
t_cstr b = cstr("banana");
if (str_cmp(a, b) < 0)
    printf("apple comes before banana\n");

t_cstr c = cstr("apple");
if (str_cmp(a, c) == 0)
	printf("The two strings are equal\n");
```

### String Search Functions

#### `str_findchr()` - Find First Character
```c
t_cstr str_findchr(t_cstr str, t_i32 c);
```

**Description**: Locates the first occurrence of a character.

**Parameters**:
- `str`: String to search in
- `c`: Character to find

**Returns**: A `t_cstr` starting at the first occurrence, or contains NULL if not found.

**Example**:
```c
t_cstr str = cstr("Hello, World!");
t_cstr result = str_findchr(str, 'W');
// result.s points to "World!"

t_cstr not_found = str_findchr(str, 'x');
// not_found.s == NULL
```

#### `str_findlastchr()` - Find Last Character
```c
t_cstr str_findlastchr(t_cstr str, t_i32 c);
```

**Description**: Locates the last occurrence of a character.

**Parameters**:
- `str`: String to search in
- `c`: Character to find

**Returns**: A `t_cstr` starting at the last occurrence, or contains NULL if not found.

**Example**:
```c
t_cstr str = cstr("Hello, World!");
t_cstr result = str_findlastchr(str, 'o');
// result.s points to "orld!"

t_cstr not_found = str_findlastchr(str, 'x');
// not_found.s == NULL
```

#### `str_findindex()` - Find Character Index
```c
ssize_t str_findindex(t_cstr str, t_i8 c);
```

**Description**: Returns the index of the first occurrence of a character.

**Parameters**:
- `str`: String to search in
- `c`: Character to find

**Returns**: Index of first occurrence, or `-1` if not found.

**Example**:
```c
t_cstr str = cstr("Hello");
ssize_t idx = str_findindex(str, 'l');
// idx = 2

ssize_t idx2 = str_findindex(str, 'x');
// idx2 = -1
```

#### `str_findlastindex()` - Find Last Character Index
```c
ssize_t str_findlastindex(t_cstr str, t_i8 c);
```

**Description**: Returns the index of the last occurrence of a character.

**Parameters**:
- `str`: String to search in
- `c`: Character to find

**Returns**: Index of last occurrence, or `-1` if not found.

**Example**:
```c
t_cstr str = cstr("Hello");
ssize_t idx = str_findlastindex(str, 'l');
// idx = 3

ssize_t idx2 = str_findlastindex(str, 'x');
// idx2 = -1
```

#### `str_findsub()` - Find Substring
```c
t_cstr str_findsub(t_cstr str, t_cstr sub);
```

**Description**: Locates a substring.

**Parameters**:
- `str`: String to search in
- `sub`: Substring to find

**Returns**: A `t_cstr` starting at the first occurrence, contains NULL if not found.

**Behavior**:
1. If `sub.len == 0`, returns `str` (empty substring found at start)

**Example**:
```c
t_cstr text = cstr("Hello, World!");
t_cstr pattern = cstr("World");
t_cstr result = str_findsub(text, pattern);
// result.s points to "World!"

t_cstr not_found = str_findsub(text, cstr("Earth"));
// not_found.s == NULL

t_cstr empty_sub = str_findsub(text, cstr("", 0));
// empty_sub.s points to "Hello, World!" (the start of text)
```

### String Conversion Functions

#### `str_to_int()` - Parse Integer from String
```c
t_i32 str_to_int(t_cstr nptr, t_cstr base);
```

**Description**: Converts a string to an integer in any base (doesn't check if base is valid).

**Parameters**:
- `nptr`: String containing the number
- `base`: Character set representing the base (e.g., "0123456789" for decimal)

**Returns**: The parsed integer value.

**Valid Base rules**:
1. No whitespace characters in base
2. No '+' or '-' signs in base
3. All characters must be unique

**Example**:
```c
t_cstr num = cstr("42");
t_cstr dec_base = cstr("0123456789"); 
t_i32 value = str_to_int(num, dec_base);
// value = 42

t_cstr hex = cstr("2A");
t_cstr hex_base = cstr("0123456789abcdef");
t_i32 val = str_to_int(hex, hex_base);
// val = 42
```

#### `str_from_int()` - Convert Integer to String
```c
t_dstr str_from_int(t_i32 n, t_cstr base, t_bool sign);
```

**Description**: Converts an integer to a string in any base (doesn't check if base is valid).

**Parameters**:
- `n`: Integer value to convert
- `base`: Character set for the base
- `sign`: If TRUE, handle as signed integer

**Returns**: A new `t_dstr` containing the string representation of the integer.

**Memory Ownership**: Allocates new memory. Caller must free with `free_dstr()`.

**Example**:
```c
t_cstr dec = cstr("0123456789");
t_dstr str = str_from_int(42, dec, TRUE);
// str.s = "42"

t_cstr hex = cstr("0123456789abcdef");
t_dstr hexstr = str_from_int(255, hex, FALSE);
// hexstr.s = "ff"
```

**Error Handling**: Returns a null string (`s=NULL, len=0, size=0`) on allocation failure.

#### `str_to_long()` / `str_from_long()` - Long Conversions
```c
t_i64 str_to_long(t_cstr nptr, t_cstr base);
t_dstr str_from_long(t_i64 n, t_cstr base, t_bool sign);
```

**Description**: Same as int conversions but for 64-bit long integers (see previous section).

#### `str_from_char()` - Convert Character to String
```c
t_dstr str_from_char(t_i8 c);
```

**Description**: Creates a dynamic string from a single character.

**Parameters**:
- `c`: Character to convert

**Returns**: A new `t_dstr` containing the character as a string.

**Memory Ownership**: Allocates new memory. Caller must free with `free_dstr()`.

**Example**:
```c
t_dstr str = str_from_char('A');
// str.s = "A"
```	

**Error Handling**: Returns a null string (`s=NULL, len=0, size=0`) on allocation failure.

#### `str_from_buf()` - Convert Buffer to String
```c
t_dstr	str_from_buf(t_dbuf *buf);
```

**Description**: Creates a dynamic string from a buffer.

**Parameters**:
- `buf`: Pointer to the buffer to convert (**will be freed**)

**Returns**: A new `t_dstr` containing the buffer's data as a string (add null-terminator).

**Behavior**:
1. If `buf->data` is NULL, returns null string (`s=NULL, len=0, size=0`)

**Memory Ownership**: Allocates new memory. Caller must free with `free_dstr()`.

**Example**:
```c
t_dbuf buf = dbuf_c(cbuf("Hello", 5));
t_dstr str = str_from_buf(&buf);
// str.s = "Hello" (null-terminated)
// str.len = 5
// str.size = 6
buf.data // is now invalid (freed in str_from_buf)
```

**Error Handling**: Returns a null string (`s=NULL, len=0, size=0`) on allocation failure. The original `buf` is freed before returning NULL. Users must check for NULL and handle the failure appropriately.

### String Iteration Functions

#### `str_foreach()` - Iterate Over String
```c
void str_foreach(t_cstr str, void (*f)(t_u32, t_i8));
```

**Description**: Applies a side effect function to each character with its index.

**Parameters**:
- `str`: String to iterate over
- `f`: Function receiving (index, character)

**Example**:
```c
void print_char_and_index(t_u32 i, t_i8 c)
{
    printf("[%u] = '%c'\n", i, c);
}

t_cstr str = cstr("Hello");
str_foreach(str, print_char_and_index);
// Output:
// [0] = 'H'
// [1] = 'e'
// ...
```

#### `str_map()` - Transform String
```c
t_dstr str_map(t_dstr str, t_i8 (*f)(t_u32, t_i8));
```

**Description**: Creates a new string by applying a transformation to each character with its index.

**Parameters**:
- `str`: String to apply the transformation to (**will be freed**)
- `f`: Function that transforms (index, character) → new character

**Returns**: A new transformed string.

**Memory Ownership**:
⚠️ **CRITICAL**: Always allocates new memory:
1. The original `str` pointer is freed and invalidated.
2. The returned buffer must be reassigned to avoid dangling pointers.
Always reassign:
```c
	str = str_map(str, f);  // ✓ Correct
	str_map(str, f);        // ✗ Memory leak!
```

**Example**:
```c
t_i8 to_upper(t_u32 i, t_i8 c)
{
    if (c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}

t_dstr str = dstr_c(cstr("hello"));
str = str_map(str, to_upper);
// str.s = "HELLO"
```

**Error Handling**: Returns a null string (`s=NULL, len=0, size=0`) on allocation failure. The original `str` is freed before returning NULL. Users must check for NULL and handle the failure appropriately.

### String printing Functions

#### `str_print()` - Print String to File Descriptor
```c
void str_print(t_cstr str, t_i32 fd);
```

**Description**: Writes a string to a file descriptor.

**Parameters**:
- `str`: String to print
- `fd`: File descriptor (0=stdin, 1=stdout, 2=stderr)

**Example**:
```c
t_cstr msg = cstr("Hello, World!\n");
str_print(msg, STDOUT_FILENO);  // Print to stdout
```

### String Manipulation Functions

#### `str_repeat()` - Repeat String N Times
```c
t_dstr str_repeat(t_cstr str, size_t n);
```

**Description**: Creates a new string by repeating the input `n` times.

**Parameters**:
- `str`: String to repeat
- `n`: Number of repetitions

**Returns**: A new `t_dstr` with repeated content.

**Example**:
```c
t_cstr pattern = cstr("Ha");
t_dstr laugh = str_repeat(pattern, 3);
// laugh.s = "HaHaHa"
```

### `str_split()` - Split String by Delimiter
```c
t_dbuf str_split(t_cstr str, t_i8 c);
```

**Description**: Splits a string into an array of substrings using a delimiter.

**Parameters**:
- `str`: String to split
- `c`: Delimiter character

**Returns**: A `t_dbuf` containing an array of `t_dstr` structures.

**Example**:
```c
t_cstr text = cstr("one,two,three");
t_dbuf parts = str_split(text, ',');

// Access individual parts
t_dstr *array = (t_dstr *)parts.data;
size_t count = parts.len / sizeof(t_dstr);

for (size_t i = 0; i < count; i++)
    printf("%s\n", array[i].s);
// Output: one, two, three

// Free all strings and buffer
free_dstrs(&parts);
```

**Memory**: Returns array of dynamic strings. Use `free_dstrs()` to free.

### `str_trim()` - Trim Characters from Ends
```c
t_dstr str_trim(t_dstr str, t_cstr set);
```

**Description**: Removes characters from the beginning and end of a string.

**Parameters**:
- `str`: String to trim (**will be freed**)
- `set`: Set of characters to remove

**Returns**: A new trimmed string.

**Memory Ownership**:
```
⚠️ CRITICAL: Consumes input string!
   str = str_trim(str, set);  // ✓ Correct
```

**Example**:
```c
t_dstr str = dstr_c(cstr("  Hello  "));
t_cstr whitespace = cstr(" \t\n");
str = str_trim(str, whitespace);
// str.s = "Hello"
```

## String Memory Management

### `free_dstr()` - Free Dynamic String
```c
void free_dstr(t_dstr *str);
```

**Description**: Frees a dynamic string and zeros its memory.

**Parameters**:
- `str`: Pointer to the string to free

**Behavior**:
1. Zeros all bytes in the string
2. Frees the allocated memory
3. Resets all fields to zero/NULL

**Example**:
```c
t_dstr str = dstr_c(cstr("Hello"));
// ... use string ...
free_dstr(&str);
// str.s = NULL, str.len = 0, str.size = 0
```

**Safety**: Double-free safe, leaves string in valid empty state.

---

### `free_dstrs()` - Free Array of Dynamic Strings
```c
void free_dstrs(t_dbuf *str_buf);
```

**Description**: Frees an array of dynamic strings (typically from `str_split()`).

**Parameters**:
- `str_buf`: Pointer to buffer containing array of `t_dstr`

**Behavior**:
1. Frees each string in the array
2. Frees the buffer itself

**Example**:
```c
t_dbuf parts = str_split(cstr("a,b,c"), ',');
// ... use parts ...
free_dstrs(&parts);
```

---

### String Memory Ownership Rules

#### Constant Strings (`t_cstr`)
- **Never** own memory
- Can point to string literals, stack strings, or heap strings
- Do **not** call `free()` on `cstr.s`
- Ensure the underlying string outlives the `t_cstr`

#### Dynamic Strings (`t_dstr`)
- **Always** own their memory
- Must be freed with `free_dstr()` when done
- Can be consumed by functions like `str_insert()`, `str_trim()`, `str_map()`
- After consumption, the string is invalid

#### Functions That Consume Strings
These functions free their input:
- `str_insert()`: Frees `insrt`
- `str_insertc()` / `str_insert()`: May reallocate `str`
- `str_map()`: Frees and replaces `str`
- `str_trim()`: Frees and replaces `str`
- `dstr_buf()`: Frees the buffer

**Golden Rule**: Always reassign when calling consuming functions:
```c
str = str_trim(str, set);
str = str_map(str, func);
str = str_insert(str, other, pos);
```

---

## String Usage Examples

### Example 1: Basic String Operations
```c
#include "libft.h"

void example_basic(void)
{
    // Create strings
    t_cstr hello = cstr("Hello");
    t_cstr world = cstr("World");
    
    // Create dynamic copy
    t_dstr greeting = dstr_c(hello);
    
    // Insert
    greeting = str_insertc(greeting, cstr(", "), greeting.len);
    greeting = str_insertc(greeting, world, greeting.len);
    greeting = str_insertc(greeting, cstr("!"), greeting.len);
    
    // greeting.s = "Hello, World!"
    printf("%s\n", greeting.s);
    
    free_dstr(&greeting);
}
```

### Example 2: String Splitting and Processing
```c
#include "libft.h"

void example_split(void)
{
    t_cstr csv = cstr("apple,banana,cherry");
    t_dbuf parts = str_split(csv, ',');
    
    t_dstr *fruits = (t_dstr *)parts.data;
    size_t count = parts.len / sizeof(t_dstr);
    
    for (size_t i = 0; i < count; i++)
    {
        printf("Fruit %zu: %s\n", i + 1, fruits[i].s);
        // Process each fruit...
    }
    
    free_dstrs(&parts);
}
```

### Example 3: Number Conversions
```c
#include "libft.h"

void example_conversions(void)
{
    // String to int
    t_cstr num_str = cstr("42");
    t_i32 value = str_to_int(num_str, cstr(CHARSET_DEC));
    printf("Parsed: %d\n", value);
    
    // Int to string (various bases)
    t_dstr dec = str_from_int(255, cstr(CHARSET_DEC), FALSE);
    t_dstr hex = str_from_int(255, cstr(CHARSET_HEX), FALSE);
    
    printf("Decimal: %s\n", dec.s);  // "255"
    printf("Hex: %s\n", hex.s);      // "ff"
    
    free_dstr(&dec);
    free_dstr(&hex);
}
```

### Example 4: String Trimming and Cleaning
```c
#include "libft.h"

void example_trim(void)
{
    t_dstr input = dstr_c(cstr("  \t Hello World  \n"));
    t_cstr whitespace = cstr(" \t\n\r");
    
    input = str_trim(input, whitespace);
    // input.s = "Hello World"
    
    printf("Trimmed: '%s'\n", input.s);
    
    free_dstr(&input);
}
```

### Example 5: String Transformation
```c
#include "libft.h"

t_i8 reverse_case(t_u32 i, t_i8 c)
{
    (void)i;
    if (c >= 'a' && c <= 'z')
        return c - 32;
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}

void example_transform(void)
{
    t_dstr text = dstr_c(cstr("Hello World"));
    text = str_map(text, reverse_case);
    // text.s = "hELLO wORLD"
    
    printf("%s\n", text.s);
    free_dstr(&text);
}
```

### Example 6: String Search and Replace
```c
#include "libft.h"

void example_search(void)
{
    t_cstr text = cstr("The quick brown fox");
    
    // Find substring
    t_cstr found = str_findsub(text, cstr("brown"), text.len);
    if (found.s != NULL)
        printf("Found at: %s\n", found.s);  // "brown fox"
    
    // Find character
    ssize_t idx = str_findindex(text, 'q');
    printf("'q' is at index: %zd\n", idx);  // 4
    
    // Find last occurrence
    t_cstr last = str_findlastchr(text, 'o');
    printf("Last 'o': %s\n", last.s);  // "ox"
}
```

---

## String Best Practices

### 1. **Always Reassign After Consuming Operations**
```c
// ✓ CORRECT
str = str_trim(str, set);
str = str_map(str, func);
str = str_insert(str, other, pos);

// ✗ WRONG - Using freed memory
str_trim(str, set);
// str is now invalid!
```

### 2. **Check NULL Returns from Search Functions**
```c
t_cstr result = str_findchr(str, 'x');
if (result.s != NULL)
{
    // Use result safely
}
```

### 3. **Use const Strings for Parameters**
```c
// ✓ GOOD - No unnecessary copies
void process_string(t_cstr str)
{
    // Just viewing, not modifying
}

// ✗ BAD - Passing dynamic string when not needed
void process_string(t_dstr str);  // Implies ownership transfer
```

### 4. **Free Dynamic Strings Promptly**
```c
void build_message(void)
{
    t_dstr msg = dstr_c(cstr("Error: "));
    msg = str_insertc(msg, cstr("File not found"), msg.len);
    str_print(cstr_d(msg), 2);
    free_dstr(&msg);  // Free immediately after use
}
```

### 5. **Use Pre-defined Base Constants**
```c
// ✓ CORRECT
t_i32 num = str_to_int(str, cstr(CHARSET_DEC));
t_i32 hex = str_to_int(str, cstr(CHARSET_HEX));

// ✗ WRONG - Creating strings repeatedly
t_i32 num = str_to_int(str, cstr("0123456789"));
```

### 6. **Handle Split Results Properly**
```c
t_dbuf parts = str_split(str, ',');
// ... use parts ...
free_dstrs(&parts);  // Frees all strings AND the buffer
```

### 7. **Leverage Length Tracking**
```c
// ✓ EFFICIENT - O(1)
if (str.len > 0)
    process(str);

// ✗ INEFFICIENT - O(n)
if (strlen(str.s) > 0)  // Don't do this when you have str.len!
    process(str);
```

---

## String Common Pitfalls

### ❌ Pitfall 1: Not Reassigning After str_trim/str_map
```c
t_dstr str = dstr_c(cstr("  hello  "));
str_trim(str, cstr(" "));  // ✗ str is now freed!
printf("%s\n", str.s);     // Undefined behavior
```

**Solution**:
```c
str = str_trim(str, cstr(" "));  // ✓
```

---

### ❌ Pitfall 2: Using cstr After Source is Freed
```c
t_dstr temp = dstr_c(cstr("Hello"));
t_cstr view = cstr_d(temp);
free_dstr(&temp);
printf("%s\n", view.s);  // ✗ Dangling pointer!
```

**Solution**:
```c
// Ensure source outlives the view
```

---

### ❌ Pitfall 3: Freeing String Literals
```c
t_cstr str = cstr("Hello");
free((void *)str.s);  // ✗ Freeing literal!
```

**Solution**:
```c
// Never free cstr.s - you don't own it
```

---

### ❌ Pitfall 4: Wrong Base String Format
```c
// ✗ WRONG - base has duplicates or invalid chars
t_i32 num = str_to_int(cstr("10"), cstr("00123"));  // '0' appears twice
```

**Solution**:
```c
// Use valid base strings with unique characters
t_i32 num = str_to_int(cstr("10"), cstr(CHARSET_DEC));  // ✓
```

---

### ❌ Pitfall 5: Not Freeing Split Results
```c
t_dbuf parts = str_split(cstr("a,b,c"), ',');
// ... use parts ...
free_dbuf(&parts);  // ✗ Leaks the individual strings!
```

**Solution**:
```c
free_dstrs(&parts);  // ✓ Frees strings AND buffer
```

---

### ❌ Pitfall 6: Confusing len and size
```c
t_dstr str = dstr_s(10);
memcpy(str.s, "Hello", 5);
// ✗ WRONG - len not updated
printf("Length: %zu\n", str.len);  // Still 0!
```

**Solution**:
```c
// Use the string functions which maintain len automatically
str = str_insertc(str, cstr("Hello"), 0);  // ✓ len updated
```

---

## String Performance

### Time Complexity

| Operation | Complexity | Notes |
|-----------|------------|-------|
| `cstr()` | O(n) | Must compute length |
| `dstr_c()` | O(n) | Copies string |
| `dstr_sub()` | O(k) | k = substring length |
| `str_cmp()` | O(min(n,m)) | Early exit on difference |
| `str_findchr()` | O(n) | Linear search |
| `str_findsub()` | O(n*m) | Naive substring search |
| `str_insertc()` | O(n+k) | May shift data |
| `str_split()` | O(n) | Single pass |
| `str_trim()` | O(n) | Scans from both ends |
| `str_to_int()` | O(n) | Parses each digit |
| `str_from_int()` | O(log n) | Digits in number |
| `str_map()` | O(n) | Single pass |
| `str_repeat()` | O(n*k) | n = string len, k = count |

Where n, m = string lengths, k = insertion/substring length

### Space Complexity

- **Constant strings**: O(1) - just metadata
- **Dynamic strings**: O(n) - allocated buffer
- **Split operation**: O(n + k) where k = number of parts

### Performance Tips

**1. Use Constant Strings When Possible**
```c
// ✓ Fast - no allocation
void process(t_cstr str) { /* ... */ }

// ✗ Slower - allocates
void process(t_dstr str) { /* ... */ }
```

**2. Pre-allocate for Known Size**
```c
// ✓ Efficient
t_dstr result = dstr_s(expected_size);
result = str_insertc(result, data, 0);

// ✗ Less efficient - multiple reallocations
t_dstr result = dstr_s(1);
for (...)
    result = str_insertc(result, data, result.len);
```

**3. Leverage Length Tracking**
```c
// ✓ O(1)
if (str.len == 0)
    return;

// ✗ O(n)
if (strlen(str.s) == 0)  // Unnecessary!
    return;
```

---

# List Module

The **List Module** provides a singly-linked list implementation with a comprehensive API for managing dynamic collections in C. It implements a wrapper structure that tracks both the head node and list size for efficient operations.

**Key Features**:
- **Size Tracking**: O(1) size queries without traversal
- **Type-Agnostic**: Store any data type via `void*` pointers
- **Flexible Insertion**: Insert at any position in the list
- **Functional Iteration**: `foreach` and `map` operations
- **Safe Memory Management**: Customizable deletion callbacks

This module is ideal for dynamic collections where insertion order matters and random access is not frequently required.

---

## List Type Definitions

### `t_node` - List Node
```c
typedef struct s_node
{
    void            *content;  // Pointer to the node's content
    struct s_node   *next;     // Pointer to the next node
} t_node;
```

**Purpose**: Represents a single node in the singly-linked list.

**Characteristics**:
- Stores a `void*` pointer to any data type
- Links to the next node in the sequence
- Must be allocated on the heap
- Node owns its structure but **not** necessarily its content

**Ownership Model**:
- The **node structure** is owned by the list
- The **content** ownership depends on context (user-defined)
- Use `del` callbacks to specify content cleanup

---

### `t_lst` - List Structure
```c
typedef struct s_list
{
    t_node  *nodes;  // Pointer to the first node
    size_t  size;    // Number of nodes in the list
} t_lst;
```

**Purpose**: Wrapper structure that manages the linked list.

**Characteristics**:
- Maintains a pointer to the head node
- Tracks the number of nodes for O(1) size queries
- Provides a consistent interface for list operations
- Can represent an empty list (`nodes = NULL, size = 0`)

**Important Properties**:
- `nodes`: Head of the list (NULL if empty)
- `size`: Current number of nodes (0 if empty)
- Invariant: `(nodes == NULL) ⟺ (size == 0)`

**Advantages Over Raw Linked Lists**:
1. O(1) size queries (no traversal needed)
2. Consistent API across all operations
3. Easier to validate list state
4. Clear ownership semantics

---

## Constructor Functions

### `lst_()` - Create Empty List
```c
t_lst lst_(void);
```

**Description**: Creates a new empty list with no nodes.

**Parameters**: None

**Returns**: A `t_lst` structure with:
- `nodes`: Set to `NULL`
- `size`: Set to `0`

**Example**:
```c
t_lst my_list = lst_();
// my_list.nodes = NULL
// my_list.size = 0
```

**Use Case**: Initialize a new list before adding elements.

**Memory**: No heap allocation. The returned structure is stack-allocated.

---

### `lst_n()` - Create List from Node
```c
t_lst lst_n(t_node *node);
```

**Description**: Creates a new list with a single node as the head.

**Parameters**:
- `node`: Pointer to the node to use as the first element (can be NULL)

**Returns**: A `t_lst` structure with:
- `nodes`: Points to the provided node
- `size`: Set to `1` (or `0` if node was NULL)

**Example**:
```c
t_node *first = node("Hello");
t_lst my_list = lst_n(first);
// my_list.nodes = first
// my_list.size = 1
```

**Memory Ownership**: The list takes ownership of the node structure but not necessarily the content.

**Null Safety**: Passing NULL creates an empty list.

---

### `node()` - Create New Node
```c
t_node *node(void *content);
```

**Description**: Allocates and initializes a new list node with the given content.

**Parameters**:
- `content`: Pointer to the content to store (can be any type)

**Returns**: 
- Pointer to the newly allocated node
- `NULL` if allocation fails

**Node Structure**:
- `content`: Set to the provided pointer
- `next`: Initialized to `NULL`

**Example**:
```c
int *value = malloc(sizeof(int));
*value = 42;
t_node *n = node(value);
if (n == NULL)
{
    // Handle allocation failure
    free(value);
}
```

**Memory**:
- Allocates memory for the node structure only
- Does **not** allocate or copy content
- Content pointer is stored as-is
- Caller must free the node and manage content lifecycle

**Error Handling**: Always check for NULL return value.

---

## Access Functions

### `get()` - Get Node at Index
```c
t_node *get(t_lst lst, size_t index);
```

**Description**: Retrieves the node at the specified index in the list.

**Parameters**:
- `lst`: The list to traverse (passed by value, not modified)
- `index`: Zero-based index of the node to retrieve

**Returns**: 
- Pointer to the node at the specified index
- `NULL` if index is out of bounds or list is empty

**Behavior**:
- Traverses the list from the head
- Returns NULL for invalid indices (>= size)
- Does not modify the list

**Example**:
```c
t_lst list = create_list_with_data();
t_node *third = get(list, 2);  // Get 3rd element
if (third != NULL)
{
    int *value = (int *)third->content;
    printf("Value: %d\n", *value);
}
```

**Time Complexity**: O(n) where n = index

**Bounds Checking**: Always returns NULL for out-of-bounds access (no crashes).

---

## Insertion Functions

### `lst_insert()` - Insert Node at Index
```c
void lst_insert(t_lst *lst, t_node *node, size_t index);
```

**Description**: Inserts a node at the specified position in the list.

**Parameters**:
- `lst`: Pointer to the list to modify
- `node`: The node to insert (must be pre-allocated)
- `index`: Position where the node should be inserted

**Behavior**:
1. If `index >= lst->size`, appends to the end
2. Adjusts links to maintain list integrity
3. Updates `lst->size` automatically
4. Handles insertion at head (index 0) correctly

**Index Clamping**: Indices beyond the list size are clamped to `size` (append).

**Example**:
```c
t_lst list = lst_();

// Insert at head
t_node *first = node("First");
lst_insert(&list, first, 0);

// Insert at end
t_node *second = node("Second");
lst_insert(&list, second, 1);

// Insert in middle
t_node *middle = node("Middle");
lst_insert(&list, middle, 1);
// List order: "First" -> "Middle" -> "Second"
```

**Memory Ownership**: The list takes ownership of the node. Do not free it manually.

**Safety**:
- Safe to call with NULL list or node (no-op)
- Automatically clamps index to valid range

**Time Complexity**: 
- O(1) for insertion at head (index 0)
- O(n) for insertion elsewhere (requires traversal)

---

## Iteration Functions

### `lst_foreach()` - Apply Function to Each Node
```c
void lst_foreach(t_lst lst, void (*f)(void *));
```

**Description**: Applies a function to the content of each node in the list for side effects.

**Parameters**:
- `lst`: The list to iterate over (passed by value, not modified)
- `f`: Function pointer that takes the content of each node

**Behavior**:
- Traverses the list from head to tail
- Calls `f(node->content)` for each node
- Does not modify the list structure
- Safe with empty lists (no-op)

**Example**:
```c
void print_int(void *content)
{
    int *num = (int *)content;
    printf("%d ", *num);
}

t_lst numbers = create_number_list();
lst_foreach(numbers, print_int);
// Output: 1 2 3 4 5
```

**Use Cases**:
- Printing list contents
- Accumulating values
- Performing side effects on each element
- Validation or counting operations

**Time Complexity**: O(n) where n = list size

**Thread Safety**: Not thread-safe. Do not modify the list during iteration.

---

### `lst_map()` - Transform List with Function
```c
t_lst lst_map(t_lst lst, void *(*f)(void *), void (*del)(void *));
```

**Description**: Creates a new list by applying a transformation function to each node's content.

**Parameters**:
- `lst`: The list to transform (**will be freed**)
- `f`: Function that transforms content (must return new allocated content or NULL)
- `del`: Function to free content on error

**Returns**: 
- A new `t_lst` with transformed content
- Empty list (`nodes=NULL, size=0`) on allocation failure

**Memory Ownership**:
```
⚠️ CRITICAL: This function CONSUMES the input list!
1. Input 'lst' is always freed
2. Returns a newly allocated list
3. On error, cleans up all allocated resources

Always reassign:
   lst = lst_map(lst, transform, del);  // ✓ Correct
```

**Behavior**:
1. Creates a new empty list
2. Iterates through original list
3. Calls `f(content)` for each node
4. Creates new nodes with transformed content
5. On success: frees original list, returns new list
6. On failure: frees both lists and all transformed content

**Example**:
```c
void *double_int(void *content)
{
    int *original = (int *)content;
    int *doubled = malloc(sizeof(int));
    if (doubled)
        *doubled = (*original) * 2;
    return doubled;
}

void free_int(void *content)
{
    free(content);
}

t_lst numbers = create_list();
numbers = lst_map(numbers, double_int, free_int);
// Original list is freed, numbers now contains doubled values
```

**Error Handling**:
- If `f()` returns NULL: cleanup and return empty list
- If node allocation fails: cleanup and return empty list
- Uses `del()` to free content on cleanup

**Use Cases**:
- Transforming data types
- Deep copying lists with modified values
- Pipeline-style data processing

**Time Complexity**: O(n) where n = list size

**Important**: The transformation function `f` must allocate new memory for transformed content.

---

## Memory Management

### `free_lst()` - Free Entire List
```c
void free_lst(t_lst *lst, void (*del)(void *));
```

**Description**: Frees all nodes in the list and their content using a custom deletion function.

**Parameters**:
- `lst`: Pointer to the list to free
- `del`: Function pointer to free each node's content

**Behavior**:
1. Traverses the entire list
2. Calls `del(node->content)` for each node
3. Frees each node structure
4. Decrements `size` to 0
5. Sets `lst->nodes` to NULL

**Example**:
```c
void free_int(void *content)
{
    free(content);
}

t_lst numbers = create_number_list();
// ... use list ...
free_lst(&numbers, free_int);
// numbers.nodes = NULL, numbers.size = 0
```

**Deletion Callback**:
- The `del` function receives each node's content
- Responsible for freeing the content memory
- Called for every node in the list

**Common Deletion Functions**:
```c
// For malloc'd primitives
void free_simple(void *content) { free(content); }

// For strings
void free_string(void *content) { free(content); }

// For no cleanup (content not owned)
void no_op(void *content) { (void)content; }

// For complex structures
void free_person(void *content)
{
    t_person *p = (t_person *)content;
    free(p->name);
    free(p);
}
```

**Safety**:
- Double-free safe (checks nodes)
- Leaves list in valid empty state
- Safe to call multiple times

**Time Complexity**: O(n) where n = list size

---

### `free_node()` - Free Single Node at Index
```c
void free_node(t_lst *lst, size_t index, void (*del)(void *));
```

**Description**: Removes and frees a single node at the specified index.

**Parameters**:
- `lst`: Pointer to the list to modify
- `index`: Zero-based index of the node to remove
- `del`: Function pointer to free the node's content

**Behavior**:
1. Traverses to the specified index
2. Calls `del(node->content)` to free content
3. Adjusts links to maintain list integrity
4. Frees the node structure
5. Decrements `lst->size`

**Example**:
```c
void free_int(void *content)
{
    free(content);
}

t_lst list = create_list();
free_node(&list, 2, free_int);  // Remove 3rd element
// List size reduced by 1, links maintained
```

**Bounds Checking**: 
- Returns immediately if `index >= lst->size`
- No-op for out-of-bounds access
- Safe to call with invalid indices

**Edge Cases**:
- Removing head (index 0): Updates `lst->nodes`
- Removing tail: Works correctly
- Removing middle nodes: Adjusts `prev->next`

**Time Complexity**: O(n) where n = index

---

### Memory Ownership Model

#### Node Structure Ownership
The **list owns the node structures**:
- Allocated with `node()`
- Freed by `free_lst()` or `free_node()`
- Do not manually `free()` nodes in a list

#### Content Ownership
The **content ownership is flexible**:

**Pattern 1: List Owns Content** (Most Common)
```c
// List takes ownership of allocated content
int *value = malloc(sizeof(int));
*value = 42;
t_node *n = node(value);
lst_insert(&list, n, 0);

// When done, list frees both nodes and content
free_lst(&list, free);
```

**Pattern 2: Shared Ownership**
```c
// Multiple nodes reference same data
static char *shared = "Shared String";
t_node *n1 = node(shared);
t_node *n2 = node(shared);

// Use no-op deletion since we don't own the data
void no_del(void *c) { (void)c; }
free_lst(&list, no_del);
```

**Pattern 3: Complex Ownership**
```c
typedef struct s_data
{
    char *name;
    int  *values;
} t_data;

void free_data(void *content)
{
    t_data *d = (t_data *)content;
    free(d->name);
    free(d->values);
    free(d);
}

// Use custom deletion for nested structures
free_lst(&list, free_data);
```

#### Functions That Consume Lists
These functions free their input:
- `lst_map()`: Always frees the input list
- `free_lst()`: Frees all nodes and content
- `free_node()`: Frees one node and its content

**Golden Rule**: Understand which functions consume resources and reassign accordingly:
```c
lst = lst_map(lst, transform, del);  // ✓ lst is consumed and replaced
```

---

## Usage Examples

### Example 1: Creating and Populating a List
```c
#include "libft.h"

void free_int(void *content)
{
    free(content);
}

void example_basic(void)
{
    // Create an empty list
    t_lst numbers = lst_();
    
    // Add numbers to the list
    for (int i = 1; i <= 5; i++)
    {
        int *num = malloc(sizeof(int));
        *num = i * 10;
        t_node *n = node(num);
        lst_insert(&numbers, n, numbers.size);  // Append
    }
    
    // numbers contains: 10 -> 20 -> 30 -> 40 -> 50
    // numbers.size = 5
    
    // Clean up
    free_lst(&numbers, free_int);
}
```

### Example 2: Accessing List Elements
```c
#include "libft.h"

void example_access(void)
{
    t_lst list = create_number_list();
    
    // Get element at index 2
    t_node *third = get(list, 2);
    if (third != NULL)
    {
        int *value = (int *)third->content;
        printf("Third element: %d\n", *value);
    }
    
    // Iterate through all elements
    for (size_t i = 0; i < list.size; i++)
    {
        t_node *current = get(list, i);
        int *val = (int *)current->content;
        printf("%d ", *val);
    }
    printf("\n");
    
    free_lst(&list, free);
}
```

### Example 3: List Transformation with lst_map
```c
#include "libft.h"

void *square_number(void *content)
{
    int *original = (int *)content;
    int *squared = malloc(sizeof(int));
    if (squared)
        *squared = (*original) * (*original);
    return squared;
}

void free_int(void *content)
{
    free(content);
}

void example_map(void)
{
    t_lst numbers = create_numbers_1_to_5();
    
    // Transform list: square each number
    numbers = lst_map(numbers, square_number, free_int);
    // Original list is freed
    // numbers now contains: 1 -> 4 -> 9 -> 16 -> 25
    
    free_lst(&numbers, free_int);
}
```

### Example 4: Iterating with lst_foreach
```c
#include "libft.h"

void print_string(void *content)
{
    char *str = (char *)content;
    printf("%s\n", str);
}

int g_sum = 0;
void accumulate(void *content)
{
    int *num = (int *)content;
    g_sum += *num;
}

void example_foreach(void)
{
    t_lst names = create_name_list();
    
    // Print all names
    lst_foreach(names, print_string);
    
    // Calculate sum
    t_lst nums = create_number_list();
    g_sum = 0;
    lst_foreach(nums, accumulate);
    printf("Sum: %d\n", g_sum);
    
    free_lst(&names, no_op);  // String literals
    free_lst(&nums, free);
}
```

### Example 5: Removing Elements
```c
#include "libft.h"

void example_removal(void)
{
    t_lst list = create_list_with_5_items();
    
    // Remove element at index 2
    free_node(&list, 2, free);
    // list.size is now 4
    
    // Remove first element
    free_node(&list, 0, free);
    // list.size is now 3, list.nodes points to new head
    
    // Remove all remaining elements
    free_lst(&list, free);
    // list.nodes = NULL, list.size = 0
}
```

### Example 6: Managing Complex Structures
```c
#include "libft.h"

typedef struct s_person
{
    char *name;
    int  age;
} t_person;

void free_person(void *content)
{
    t_person *p = (t_person *)content;
    free(p->name);
    free(p);
}

t_person *create_person(const char *name, int age)
{
    t_person *p = malloc(sizeof(t_person));
    if (!p)
        return NULL;
    p->name = strdup(name);
    p->age = age;
    return p;
}

void example_complex(void)
{
    t_lst people = lst_();
    
    // Add people to list
    lst_insert(&people, node(create_person("Alice", 30)), 0);
    lst_insert(&people, node(create_person("Bob", 25)), 1);
    lst_insert(&people, node(create_person("Charlie", 35)), 2);
    
    // Access and use
    t_node *first = get(people, 0);
    t_person *alice = (t_person *)first->content;
    printf("%s is %d years old\n", alice->name, alice->age);
    
    // Clean up with custom deletion
    free_lst(&people, free_person);
}
```

---

## Best Practices

### 1. **Always Check Node Allocation**
```c
// ✓ CORRECT
t_node *n = node(data);
if (n == NULL)
{
    // Handle allocation failure
    free(data);
    return ERROR;
}

// ✗ WRONG - No NULL check
t_node *n = node(data);
lst_insert(&list, n, 0);  // Undefined if n is NULL
```

### 2. **Use Appropriate Deletion Callbacks**
```c
// ✓ CORRECT - Match deletion to ownership
free_lst(&list, free);        // For malloc'd content
free_lst(&list, free_custom); // For complex structures
free_lst(&list, no_op);       // For non-owned content

// ✗ WRONG - Memory leak
free_lst(&list, no_op);  // When content is malloc'd
```

### 3. **Understand lst_map Consumption**
```c
// ✓ CORRECT - Reassign result
list = lst_map(list, transform, free);

// ✗ WRONG - Original list is freed, becomes dangling
lst_map(list, transform, free);
// Using 'list' here is undefined behavior
```

### 4. **Use get() for Random Access Sparingly**
```c
// ✗ INEFFICIENT - O(n²) complexity
for (size_t i = 0; i < list.size; i++)
{
    t_node *n = get(list, i);  // Traverses from head each time
    process(n->content);
}

// ✓ EFFICIENT - O(n) complexity
t_node *current = list.nodes;
while (current != NULL)
{
    process(current->content);
    current = current->next;
}

// Or use lst_foreach
lst_foreach(list, process);
```

### 5. **Insert at Head for Best Performance**
```c
// ✓ EFFICIENT - O(1) per insertion
for (int i = 0; i < 1000; i++)
    lst_insert(&list, node(data), 0);  // Insert at head

// ✗ INEFFICIENT - O(n) per insertion
for (int i = 0; i < 1000; i++)
    lst_insert(&list, node(data), list.size);  // Append
```

### 6. **Free Lists Promptly**
```c
void process_data(void)
{
    t_lst temp = create_temp_list();
    // ... use temp ...
    free_lst(&temp, free);  // Free as soon as done
}
```

### 7. **Document Content Ownership**
```c
/**
 * Creates a list of strings. Caller owns the list
 * and must free it with free_lst(&list, free).
 */
t_lst create_string_list(void)
{
    // Implementation
}
```

---

## Common Pitfalls

### ❌ Pitfall 1: Forgetting to Free Content
```c
t_lst list = create_list();
// ... use list ...
free_lst(&list, no_op);  // ✗ Memory leak if content was malloc'd!
```

**Solution**:
```c
free_lst(&list, free);  // ✓ Frees both nodes and content
```

---

### ❌ Pitfall 2: Using List After lst_map
```c
t_lst original = create_list();
t_lst transformed = lst_map(original, func, del);
free_lst(&original, del);  // ✗ Double free!
```

**Solution**:
```c
list = lst_map(list, func, del);  // ✓ Reassign, original is gone
```

---

### ❌ Pitfall 3: Manually Freeing Nodes in a List
```c
t_node *n = node(data);
lst_insert(&list, n, 0);
free(n);  // ✗ Double free! List owns the node now
```

**Solution**:
```c
// Let the list manage nodes
// Use free_lst or free_node to remove
```

---

### ❌ Pitfall 4: O(n²) Iteration Pattern
```c
for (size_t i = 0; i < list.size; i++)
    process(get(list, i));  // ✗ O(n²) - traverses from head each time
```

**Solution**:
```c
lst_foreach(list, process);  // ✓ O(n)
// Or manual iteration
t_node *curr = list.nodes;
while (curr)
{
    process(curr->content);
    curr = curr->next;
}
```

---

### ❌ Pitfall 5: Not Checking get() Return Value
```c
t_node *n = get(list, 10);
int *value = (int *)n->content;  // ✗ Segfault if n is NULL!
```

**Solution**:
```c
t_node *n = get(list, 10);
if (n != NULL)
    int *value = (int *)n->content;  // ✓
```

---

### ❌ Pitfall 6: Wrong Deletion Function
```c
typedef struct { char *name; } t_data;
t_lst list = create_data_list();
free_lst(&list, free);  // ✗ Leaks t_data->name!
```

**Solution**:
```c
void free_data(void *c)
{
    t_data *d = (t_data *)c;
    free(d->name);
    free(d);
}
free_lst(&list, free_data);  // ✓
```

---

### ❌ Pitfall 7: Modifying List During Iteration
```c
t_node *curr = list.nodes;
while (curr)
{
    if (should_remove(curr->content))
        free_node(&list, find_index(curr), del);  // ✗ Breaks iteration!
    curr = curr->next;
}
```

**Solution**:
```c
// Collect indices to remove, then remove in reverse
// Or build a new list with desired elements
```

---

## Performance Considerations

### Performance Tips

**1. Insert at Head for Efficiency**
```c
// O(1) per insertion = O(n) total
for (int i = 0; i < n; i++)
    lst_insert(&list, node(data), 0);
```

**2. Avoid Repeated Random Access**
```c
// ✗ O(n²) - bad
for (size_t i = 0; i < list.size; i++)
    process(get(list, i)->content);

// ✓ O(n) - good
lst_foreach(list, process);
```

**3. Build Lists in Reverse if Appending**
```c
// Build in reverse order at head (O(n))
for (int i = n; i >= 0; i--)
    lst_insert(&list, node(data[i]), 0);

// Better than appending each time (O(n²))
```

**4. Use lst_map for Transformations**
```c
// ✓ Single pass, functional style
list = lst_map(list, transform, del);

// vs manual loop with new list creation
```

### When to Use Lists vs Arrays/Buffers

**Use Lists When**:
- Frequent insertions/deletions at arbitrary positions
- Size unknown or highly variable
- Need to maintain insertion order
- Rarely need random access

**Use Arrays/Buffers When**:
- Need random access frequently
- Size is known or changes rarely
- Memory locality is important
- Need to pass to C APIs expecting contiguous memory

---

## Integration with Other Modules

The list module works well with other libft modules:

### With String Module
```c
#include "libft.h"

t_lst split_to_list(t_cstr str, char delim)
{
    t_dbuf parts = str_split(str, delim);  // Get array of strings
    t_lst list = lst_();
    
    // Convert array to list
    for (size_t i = 0; i < parts.len / sizeof(t_dstr); i++)
    {
        t_dstr *s = &((t_dstr *)parts.data)[i];
        lst_insert(&list, node(s->s), list.size);
    }
    
    free_dbuf(&parts);  // Free array structure
    return list;
}
```

### As Generic Stack
```c
// Push
void push(t_lst *stack, void *data)
{
    lst_insert(stack, node(data), 0);  // O(1)
}

// Pop
void *pop(t_lst *stack)
{
    if (stack->size == 0)
        return NULL;
    t_node *top = stack->nodes;
    void *data = top->content;
    stack->nodes = top->next;
    stack->size--;
    free(top);
    return data;
}
```

### As Generic Queue (Inefficient)
```c
// Enqueue (O(n) - not ideal)
void enqueue(t_lst *queue, void *data)
{
    lst_insert(queue, node(data), queue->size);
}

// Dequeue (O(1))
void *dequeue(t_lst *queue)
{
    return pop(queue);  // Same as stack pop
}
```

---

## Thread Safety

⚠️ **Not Thread-Safe**: List operations are not thread-safe by design.

**Recommendations**:
- Use separate lists per thread
- Or synchronize access with mutexes
- Never share `t_lst` across threads without protection
- Read-only access may be safe but risky

---

## Comparison with Standard C Lists

### Advantages
- Size tracking built-in (O(1) queries)
- Consistent API with clear ownership
- Functional operations (`map`, `foreach`)
- Type-safe through conventions

### Limitations
- Singly-linked only (no reverse traversal)
- No built-in sorting
- No built-in searching (use `lst_foreach`)
- Not circular

---

## Conclusion

The list module provides a solid foundation for dynamic collections in C. By understanding node ownership, using appropriate iteration patterns, and choosing the right insertion strategies, you can build efficient and maintainable code.

**Key Takeaways**:
1. Lists own node structures, content ownership is flexible
2. Use `lst_foreach` for iteration, not repeated `get()`
3. Insert at head for O(1) performance
4. Always provide appropriate deletion callbacks
5. `lst_map` consumes and replaces the input list
6. Check `NULL` returns from `node()` and `get()`
7. Lists are best for sequential access, not random access

---

*Last Updated: January 2, 2026*  
*Part of the libft library for 42 School projects*
```c
t_dbuf buf1 = dbuf_s(10);
t_dbuf buf2 = dbuf_s(10);
buf1 = buf_insert(buf1, buf2, 0, x2_);
free_dbuf(&buf2);  // ✗ Double free! buf2 already freed
```

**Solution**:
```c
buf1 = buf_insert(buf1, buf2, 0, x2_);
// Don't touch buf2 again, it's gone
```

---

### ❌ Pitfall 3: Freeing Constant Buffer Data
```c
const char *str = "Hello";
t_cbuf buf = cbuf(str, 5);
free((void *)buf.data);  // ✗ Freeing string literal!
```

**Solution**:
```c
// Don't free const buffer data - you don't own it
```

---

### ❌ Pitfall 4: Using Shifted Buffer After Original is Freed
```c
t_dbuf owner = dbuf_s(100);
t_cbuf view = cbuf_d(owner);
t_cbuf shifted = buf_shift(view, 10);
free_dbuf(&owner);
// shifted.data now points to freed memory!
```

**Solution**:
```c
// Ensure views don't outlive their source
```

---

### ❌ Pitfall 5: Assuming Capacity After Creation
```c
t_dbuf buf = dbuf_s(100);
buf.len = 100;  // ✗ Wrong! len should only be set by insertion
memcpy(buf.data, src, 100);  // Data is there, but len is misleading
```

**Solution**:
```c
t_dbuf buf = dbuf_s(100);
buf = buf_insertc(buf, cbuf(src, 100), 0, E_);  // ✓ Properly sets len
```

---

### ❌ Pitfall 6: Type Confusion in Buffer Operations
```c
t_dbuf int_buf = dbuf_s(10 * sizeof(int));
t_cbuf insert = cbuf(&some_int, sizeof(int));
int_buf = buf_insertc(int_buf, insert, 5, E_);  // ✗ Index 5 is byte 5, not int[5]!
```

**Solution**:
```c
// Use byte offsets consistently
int_buf = buf_insertc(int_buf, insert, 5 * sizeof(int), E_);  // ✓
```

---

### ❌ Pitfall 7: Not Checking size Field in Const Buffers
```c
t_cbuf buf = buf_shift(source, 1000);
// buf.size might be 0 if shift exceeded bounds
uint8_t byte = *(uint8_t *)buf.data;  // ✗ Might dereference NULL
```

**Solution**:
```c
if (buf.data != NULL && buf.size > 0)
    uint8_t byte = *(uint8_t *)buf.data;  // ✓
```

---

# Character Module

The **Character Module** provides a complete set of character classification and case conversion utilities. These functions are type-safe wrappers around standard C library character functions, using libft's custom type system.

**Key Features**:
- **Type-Safe**: Uses `t_i32` and `t_bool` custom types
- **Complete Coverage**: All standard character classification functions
- **Case Conversion**: Upper and lowercase transformations
- **ASCII Validation**: Check character encoding validity
- **Consistent API**: Uniform return types and behavior

These functions are essential building blocks for string processing, parsing, and validation operations.

---

## Character Classification Functions

### `c_isalpha()` - Check if Alphabetic
```c
t_bool c_isalpha(t_i32 c);
```

**Description**: Tests whether a character is an alphabetic letter (A-Z or a-z).

**Parameters**:
- `c`: Character to test (typically 0-127 for ASCII)

**Returns**:
- `TRUE` if the character is alphabetic (A-Z or a-z)
- `FALSE` otherwise

**Example**:
```c
if (c_isalpha('A'))
    printf("A is alphabetic\n");  // Prints

if (c_isalpha('5'))
    printf("5 is alphabetic\n");  // Does not print
```

**Range**: Matches characters in ranges `['A'-'Z']` and `['a'-'z']`

**Time Complexity**: O(1)

---

### `c_isdigit()` - Check if Digit
```c
t_bool c_isdigit(t_i32 c);
```

**Description**: Tests whether a character is a decimal digit (0-9).

**Parameters**:
- `c`: Character to test

**Returns**:
- `TRUE` if the character is a digit ('0'-'9')
- `FALSE` otherwise

**Example**:
```c
if (c_isdigit('5'))
    printf("'5' is a digit\n");  // Prints

if (c_isdigit('A'))
    printf("'A' is a digit\n");  // Does not print
```

**Range**: Matches characters in range `['0'-'9']`

**Use Cases**:
- Number parsing
- Input validation
- Tokenization

---

### `c_isalnum()` - Check if Alphanumeric
```c
t_bool c_isalnum(t_i32 c);
```

**Description**: Tests whether a character is alphanumeric (letter or digit).

**Parameters**:
- `c`: Character to test

**Returns**:
- `TRUE` if the character is alphabetic or a digit
- `FALSE` otherwise

**Implementation**: Combines `c_isalpha()` and `c_isdigit()`

**Example**:
```c
if (c_isalnum('A'))
    printf("'A' is alphanumeric\n");  // Prints

if (c_isalnum('5'))
    printf("'5' is alphanumeric\n");  // Prints

if (c_isalnum('!'))
    printf("'!' is alphanumeric\n");  // Does not print
```

**Range**: Matches `['A'-'Z']`, `['a'-'z']`, and `['0'-'9']`

**Use Cases**:
- Identifier validation
- Variable name checking
- Filtering non-alphanumeric characters

---

### `c_isascii()` - Check if ASCII
```c
t_bool c_isascii(t_i32 c);
```

**Description**: Tests whether a value is a valid ASCII character.

**Parameters**:
- `c`: Value to test (may be outside ASCII range)

**Returns**:
- `TRUE` if the value is in the ASCII range (0-127)
- `FALSE` otherwise

**Example**:
```c
if (c_isascii(65))
    printf("65 is ASCII\n");  // Prints (65 = 'A')

if (c_isascii(200))
    printf("200 is ASCII\n");  // Does not print (extended ASCII)
```

**Range**: `[0-127]`

**Use Cases**:
- Validating input before processing
- Checking compatibility with ASCII-only systems
- Detecting extended or multi-byte characters

**Note**: Extended ASCII (128-255) returns FALSE

---

### `c_isprint()` - Check if Printable
```c
t_bool c_isprint(t_i32 c);
```

**Description**: Tests whether a character is printable (visible character or space).

**Parameters**:
- `c`: Character to test

**Returns**:
- `TRUE` if the character is printable (space through tilde)
- `FALSE` otherwise (control characters, DEL, etc.)

**Example**:
```c
if (c_isprint('A'))
    printf("'A' is printable\n");  // Prints

if (c_isprint(' '))
    printf("Space is printable\n");  // Prints

if (c_isprint('\n'))
    printf("Newline is printable\n");  // Does not print

if (c_isprint(127))
    printf("DEL is printable\n");  // Does not print
```

**Range**: `[' '-'~']` (32-126 in ASCII)

**Includes**:
- All letters, digits, punctuation
- Space character (32)

**Excludes**:
- Control characters (0-31)
- DEL character (127)

**Use Cases**:
- Text filtering
- Display validation
- Safe output checking

---

## Character Conversion Functions

### `c_toupper()` - Convert to Uppercase
```c
t_i32 c_toupper(t_i32 c);
```

**Description**: Converts a lowercase letter to its uppercase equivalent.

**Parameters**:
- `c`: Character to convert

**Returns**:
- Uppercase equivalent if `c` is lowercase ('a'-'z')
- The character unchanged otherwise

**Example**:
```c
char result = c_toupper('a');  // result = 'A'
char result = c_toupper('Z');  // result = 'Z' (unchanged)
char result = c_toupper('5');  // result = '5' (unchanged)
```

**Conversion Range**: `['a'-'z'] → ['A'-'Z']`

**Non-Lowercase**: All other characters returned unchanged

**Algorithm**: Subtracts 32 (difference between 'a' and 'A')

**Use Cases**:
- Case-insensitive comparisons
- Normalizing user input
- Converting strings to uppercase

---

### `c_tolower()` - Convert to Lowercase
```c
t_i32 c_tolower(t_i32 c);
```

**Description**: Converts an uppercase letter to its lowercase equivalent.

**Parameters**:
- `c`: Character to convert

**Returns**:
- Lowercase equivalent if `c` is uppercase ('A'-'Z')
- The character unchanged otherwise

**Example**:
```c
char result = c_tolower('A');  // result = 'a'
char result = c_tolower('z');  // result = 'z' (unchanged)
char result = c_tolower('5');  // result = '5' (unchanged)
```

**Conversion Range**: `['A'-'Z'] → ['a'-'z']`

**Non-Uppercase**: All other characters returned unchanged

**Algorithm**: Adds 32 (difference between 'A' and 'a')

**Use Cases**:
- Case-insensitive comparisons
- Normalizing user input
- Converting strings to lowercase

---

## Character Usage Examples

### Example 1: Validating an Identifier
```c
#include "libft.h"

/**
 * Check if a string is a valid C identifier
 * Rules: Must start with letter or underscore,
 *        followed by alphanumeric or underscore
 */
t_bool is_valid_identifier(const char *str)
{
    if (!str || !*str)
        return (FALSE);
    
    // First character: letter or underscore
    if (!c_isalpha(str[0]) && str[0] != '_')
        return (FALSE);
    
    // Remaining characters: alphanumeric or underscore
    for (size_t i = 1; str[i]; i++)
    {
        if (!c_isalnum(str[i]) && str[i] != '_')
            return (FALSE);
    }
    
    return (TRUE);
}

// Usage
is_valid_identifier("myVar123");   // TRUE
is_valid_identifier("_private");   // TRUE
is_valid_identifier("123abc");     // FALSE (starts with digit)
is_valid_identifier("my-var");     // FALSE (contains hyphen)
```

### Example 2: Case-Insensitive String Comparison
```c
#include "libft.h"

/**
 * Compare two strings case-insensitively
 */
t_i32 strcmp_case_insensitive(const char *s1, const char *s2)
{
    size_t i = 0;
    
    while (s1[i] && s2[i])
    {
        t_i32 c1 = c_tolower(s1[i]);
        t_i32 c2 = c_tolower(s2[i]);
        
        if (c1 != c2)
            return (c1 - c2);
        
        i++;
    }
    
    return (c_tolower(s1[i]) - c_tolower(s2[i]));
}

// Usage
strcmp_case_insensitive("Hello", "HELLO");  // 0 (equal)
strcmp_case_insensitive("Apple", "Banana"); // < 0
```

### Example 3: Extracting Numbers from Text
```c
#include "libft.h"

/**
 * Extract all digits from a string into an array
 */
void extract_digits(const char *str, char *digits, size_t size)
{
    size_t j = 0;
    
    for (size_t i = 0; str[i] && j < size - 1; i++)
    {
        if (c_isdigit(str[i]))
            digits[j++] = str[i];
    }
    
    digits[j] = '\0';
}

// Usage
char digits[100];
extract_digits("Phone: 555-1234", digits, sizeof(digits));
// digits = "5551234"
```

### Example 4: Filtering Printable Characters
```c
#include "libft.h"

/**
 * Remove non-printable characters from a string
 */
void filter_printable(char *str)
{
    size_t i = 0;
    size_t j = 0;
    
    while (str[i])
    {
        if (c_isprint(str[i]))
            str[j++] = str[i];
        i++;
    }
    
    str[j] = '\0';
}

// Usage
char text[] = "Hello\nWorld\t!";
filter_printable(text);
// text = "HelloWorld!"
```

### Example 5: Converting String to Uppercase
```c
#include "libft.h"

/**
 * Convert entire string to uppercase in-place
 */
void str_to_uppercase(char *str)
{
    for (size_t i = 0; str[i]; i++)
        str[i] = c_toupper(str[i]);
}

// Usage
char text[] = "Hello, World!";
str_to_uppercase(text);
// text = "HELLO, WORLD!"
```

### Example 6: Counting Character Types
```c
#include "libft.h"

typedef struct s_char_stats
{
    size_t letters;
    size_t digits;
    size_t spaces;
    size_t other;
} t_char_stats;

/**
 * Analyze character composition of a string
 */
t_char_stats analyze_string(const char *str)
{
    t_char_stats stats = {0, 0, 0, 0};
    
    for (size_t i = 0; str[i]; i++)
    {
        if (c_isalpha(str[i]))
            stats.letters++;
        else if (c_isdigit(str[i]))
            stats.digits++;
        else if (str[i] == ' ')
            stats.spaces++;
        else
            stats.other++;
    }
    
    return stats;
}

// Usage
t_char_stats stats = analyze_string("Hello 123!");
// stats.letters = 5
// stats.digits = 3
// stats.spaces = 1
// stats.other = 1
```

---

## Character Best Practices

### 1. **Use Character Functions for Clarity**
```c
// ✓ CLEAR - Intent is obvious
if (c_isdigit(c))
    process_digit(c);

// ✗ OBSCURE - Magic numbers
if (c >= '0' && c <= '9')
    process_digit(c);
```

### 2. **Prefer Character Functions Over Magic Constants**
```c
// ✓ GOOD - Readable and maintainable
if (c_isprint(c))
    display(c);

// ✗ BAD - Hard to understand
if (c >= 32 && c <= 126)
    display(c);
```

### 3. **Check ASCII Before Processing**
```c
// ✓ SAFE - Validate input
if (c_isascii(c) && c_isalpha(c))
    process(c);

// ✗ RISKY - May fail on extended characters
if (c_isalpha(c))  // Undefined for c > 127
    process(c);
```

### 4. **Use Conversion Functions Consistently**
```c
// ✓ CONSISTENT
for (size_t i = 0; str[i]; i++)
    str[i] = c_tolower(str[i]);

// ✗ INCONSISTENT - Mix of methods
for (size_t i = 0; str[i]; i++)
    str[i] = (str[i] >= 'A' && str[i] <= 'Z') ? str[i] + 32 : str[i];
```

### 5. **Combine Character Checks Efficiently**
```c
// ✓ EFFICIENT - Use c_isalnum
if (c_isalnum(c))
    process(c);

// ✗ REDUNDANT
if (c_isalpha(c) || c_isdigit(c))
    process(c);
```

### 6. **Handle International Characters Carefully**
```c
// ✓ AWARE - Know the limitations
if (c_isascii(c))
{
    if (c_isalpha(c))
        process_ascii_letter(c);
}
else
{
    // Handle Unicode/extended characters separately
    process_extended(c);
}
```

### 7. **Document Character Assumptions**
```c
/**
 * parse_token - Parse ASCII identifier token
 * 
 * @str: Input string (must be ASCII)
 * @return: Parsed token or NULL
 * 
 * NOTE: Only handles ASCII characters. Unicode not supported.
 */
char *parse_token(const char *str)
{
    // Implementation using c_isalnum, etc.
}
```

---

## Character Performance

### Time Complexity

All character functions have **O(1)** constant time complexity:

| Function | Complexity | Operations |
|----------|------------|------------|
| `c_isalpha()` | O(1) | 2 range checks |
| `c_isdigit()` | O(1) | 1 range check |
| `c_isalnum()` | O(1) | 3 range checks |
| `c_isascii()` | O(1) | 1 range check |
| `c_isprint()` | O(1) | 1 range check |
| `c_toupper()` | O(1) | 1 range check + optional arithmetic |
| `c_tolower()` | O(1) | 1 range check + optional arithmetic |

### Performance Characteristics

**Advantages**:
- ✓ **Extremely Fast**: Simple comparisons and arithmetic
- ✓ **No Branching Overhead**: Modern CPUs optimize range checks well
- ✓ **No Memory Access**: All operations on registers
- ✓ **Cacheable**: Small functions easily inlined

**Typical Costs** (on modern x86-64):
- Classification: ~1-3 CPU cycles
- Conversion: ~2-4 CPU cycles

### Optimization Tips

**1. Inline for Critical Paths**
```c
// Functions are small enough to inline automatically
// Modern compilers will optimize this aggressively
```

**2. Batch Processing**
```c
// ✓ EFFICIENT - Process in tight loop
for (size_t i = 0; i < len; i++)
    if (c_isdigit(str[i]))
        digits[j++] = str[i];

// ✗ LESS EFFICIENT - Function call overhead per check
for (size_t i = 0; i < len; i++)
    process_if_digit(&str[i]);  // Call overhead
```

**3. Short-Circuit Evaluation**
```c
// ✓ OPTIMAL - Check cheaper conditions first
if (c != '\0' && c_isalpha(c))
    process(c);

// Less optimal order
if (c_isalpha(c) && c != '\0')  // Still checks alpha first
    process(c);
```

**4. Use c_isalnum for Combined Checks**
```c
// ✓ FASTER - One function call
if (c_isalnum(c))
    process(c);

// ✗ SLOWER - Two function calls
if (c_isalpha(c) || c_isdigit(c))
    process(c);
```

### Space Complexity

- **Memory Usage**: None (no state, no allocation)
- **Stack Usage**: Minimal (single parameter, single return)

### Benchmark Results (Approximate)

Processing 1 million characters on modern CPU:

| Operation | Time |
|-----------|------|
| `c_isalpha()` | ~1-2 ms |
| `c_toupper()` | ~2-3 ms |
| `c_isalnum()` | ~1-3 ms |
| Combined checks | ~3-5 ms |

**Note**: Actual performance depends on CPU, compiler optimization level, and cache behavior.

---

# Math Module

The **Math Module** provides essential mathematical utility functions, starting with robust absolute value implementations. These functions are designed to handle edge cases safely and return appropriate unsigned types.

**Key Features**:
- **Overflow Safe**: Correctly handles minimum integer values
- **Type Conversion**: Returns unsigned types to avoid overflow
- **Multiple Sizes**: Supports both 32-bit and 64-bit integers
- **Predictable**: No undefined behavior for edge cases

---

## Absolute Value Functions

### `abs_i()` - Absolute Value of Integer
```c
t_u32 abs_i(t_i32 c);
```

**Description**: Computes the absolute value of a signed 32-bit integer, returning an unsigned result to avoid overflow.

**Parameters**:
- `c`: Signed integer value (`t_i32`)

**Returns**: Absolute value as unsigned integer (`t_u32`)

**Special Handling**:
```c
abs_i(INT32_MIN)  // Returns 2147483648 (I32_MAX + 1)
```

**Why Unsigned Return?**
The absolute value of `INT32_MIN` (-2147483648) is 2147483648, which exceeds `INT32_MAX` (2147483647). By returning `t_u32`, we avoid overflow.

**Example**:
```c
t_u32 result;

result = abs_i(42);          // result = 42
result = abs_i(-42);         // result = 42
result = abs_i(0);           // result = 0
result = abs_i(I32_MIN);     // result = 2147483648
```

**Algorithm**:
1. Check if value is `I32_MIN` (special case)
2. If negative, negate and cast to unsigned
3. Otherwise, cast to unsigned directly

**Time Complexity**: O(1)

**Space Complexity**: O(1)

---

### `abs_l()` - Absolute Value of Long
```c
t_u64 abs_l(t_i64 c);
```

**Description**: Computes the absolute value of a signed 64-bit long integer, returning an unsigned result.

**Parameters**:
- `c`: Signed long integer value (`t_i64`)

**Returns**: Absolute value as unsigned long integer (`t_u64`)

**Special Handling**:
```c
abs_l(INT64_MIN)  // Returns 9223372036854775808 (I64_MAX + 1)
```

**Example**:
```c
t_u64 result;

result = abs_l(42L);         // result = 42
result = abs_l(-42L);        // result = 42
result = abs_l(0L);          // result = 0
result = abs_l(I64_MIN);     // result = 9223372036854775808
```

**Use Cases**:
- Processing large integers
- File sizes and offsets
- Timestamps and durations
- Cryptographic computations

**Time Complexity**: O(1)

**Space Complexity**: O(1)

---

## Math Usage Examples

### Example 1: Computing Distance
```c
#include "libft.h"

/**
 * Compute absolute difference between two integers
 */
t_u32 distance(t_i32 a, t_i32 b)
{
    // Avoid overflow by using proper type
    t_i64 diff = (t_i64)a - (t_i64)b;
    return ((t_u32)abs_l(diff));
}

// Usage
t_u32 dist = distance(100, -100);  // dist = 200
t_u32 dist = distance(I32_MAX, I32_MIN);  // Handles overflow
```

### Example 2: Finding Maximum Absolute Value
```c
#include "libft.h"

/**
 * Find maximum absolute value in array
 */
t_u32 max_abs(const t_i32 *arr, size_t len)
{
    if (!arr || len == 0)
        return (0);
    
    t_u32 max = abs_i(arr[0]);
    
    for (size_t i = 1; i < len; i++)
    {
        t_u32 current = abs_i(arr[i]);
        if (current > max)
            max = current;
    }
    
    return (max);
}

// Usage
t_i32 values[] = {-50, 100, -200, 42};
t_u32 max = max_abs(values, 4);  // max = 200
```

### Example 3: Percentage Calculation
```c
#include "libft.h"

/**
 * Calculate percentage difference between two values
 */
double percent_difference(t_i32 a, t_i32 b)
{
    if (b == 0)
        return (0.0);
    
    t_i64 diff = (t_i64)a - (t_i64)b;
    t_u64 abs_diff = abs_l(diff);
    t_u64 abs_base = abs_l((t_i64)b);
    
    return ((double)abs_diff / (double)abs_base * 100.0);
}

// Usage
double diff = percent_difference(150, 100);  // 50.0%
```

### Example 4: Manhattan Distance
```c
#include "libft.h"

typedef struct s_point
{
    t_i32 x;
    t_i32 y;
} t_point;

/**
 * Compute Manhattan distance between two points
 */
t_u64 manhattan_distance(t_point a, t_point b)
{
    t_i64 dx = (t_i64)a.x - (t_i64)b.x;
    t_i64 dy = (t_i64)a.y - (t_i64)b.y;
    
    return (abs_l(dx) + abs_l(dy));
}

// Usage
t_point p1 = {10, 20};
t_point p2 = {-5, 30};
t_u64 dist = manhattan_distance(p1, p2);  // dist = 25
```

### Example 5: Range Validation
```c
#include "libft.h"

/**
 * Check if value is within tolerance of target
 */
t_bool within_tolerance(t_i32 value, t_i32 target, t_u32 tolerance)
{
    t_i64 diff = (t_i64)value - (t_i64)target;
    return (abs_l(diff) <= tolerance);
}

// Usage
if (within_tolerance(sensor_reading, expected, 5))
    printf("Sensor reading is within acceptable range\n");
```

### Example 6: Sorting by Absolute Value
```c
#include "libft.h"

/**
 * Comparison function for sorting by absolute value
 */
int cmp_by_abs(const void *a, const void *b)
{
    t_i32 val_a = *(const t_i32 *)a;
    t_i32 val_b = *(const t_i32 *)b;
    
    t_u32 abs_a = abs_i(val_a);
    t_u32 abs_b = abs_i(val_b);
    
    if (abs_a < abs_b)
        return (-1);
    if (abs_a > abs_b)
        return (1);
    return (0);
}

// Usage with qsort
t_i32 numbers[] = {-30, 5, -20, 40, -10};
qsort(numbers, 5, sizeof(t_i32), cmp_by_abs);
// Result: {5, -10, -20, -30, 40}
```

---

## Math Best Practices

### 1. **Use Unsigned Return Values**
```c
// ✓ CORRECT - Assign to unsigned
t_u32 result = abs_i(value);

// ✗ WRONG - May overflow for I32_MIN
t_i32 result = (t_i32)abs_i(I32_MIN);  // Undefined!
```

### 2. **Prevent Overflow in Subtraction**
```c
// ✓ SAFE - Promote before subtraction
t_i64 diff = (t_i64)a - (t_i64)b;
t_u64 abs_diff = abs_l(diff);

// ✗ RISKY - May overflow
t_i32 diff = a - b;  // Overflow possible
t_u32 abs_diff = abs_i(diff);
```

### 3. **Check for Special Cases**
```c
// ✓ AWARE - Document edge case behavior
/**
 * NOTE: For I32_MIN, result exceeds I32_MAX.
 * Returns 2147483648 as unsigned.
 */
t_u32 result = abs_i(I32_MIN);
```

### 4. **Use Appropriate Size**
```c
// ✓ CORRECT - Use abs_l for large values
t_i64 large_value = 5000000000L;
t_u64 result = abs_l(large_value);

// ✗ WRONG - Truncation/overflow
t_u32 result = abs_i((t_i32)large_value);  // Data loss!
```

### 5. **Validate Before Casting Back**
```c
// ✓ SAFE - Check before narrowing
t_u32 abs_val = abs_i(value);
if (abs_val <= I32_MAX)
{
    t_i32 safe_value = (t_i32)abs_val;
    // Use safe_value
}
```

### 6. **Document Unsigned Semantics**
```c
/**
 * calculate_difference - Compute absolute difference
 * 
 * @a: First value
 * @b: Second value
 * @return: Absolute difference as unsigned (may exceed I32_MAX)
 */
t_u32 calculate_difference(t_i32 a, t_i32 b)
{
    t_i64 diff = (t_i64)a - (t_i64)b;
    return ((t_u32)abs_l(diff));
}
```

---

## Math Performance

### Time Complexity

| Function | Complexity | Operations |
|----------|-----------|------------|
| `abs_i()` | O(1) | 1-2 comparisons, 1 negation (if negative) |
| `abs_l()` | O(1) | 1-2 comparisons, 1 negation (if negative) |

### Performance Characteristics

**Advantages**:
- ✓ **Extremely Fast**: 2-4 CPU cycles typically
- ✓ **No Branching** (on modern CPUs with CMOV)
- ✓ **Inlineable**: Compilers optimize aggressively
- ✓ **No Memory Access**: Pure register operations

**Typical Assembly** (x86-64 with optimization):
```asm
; abs_i(x) optimized
mov    eax, edi      ; Load parameter
neg    eax           ; Negate
cmovl  eax, edi      ; Conditionally move if negative
```

### Space Complexity

- **Memory Usage**: None
- **Stack Usage**: Minimal (one parameter, one return value)

### Optimization Tips

**1. Compiler Intrinsics**
Modern compilers recognize absolute value patterns and may use specialized instructions:
```c
// Compiler may use abs() intrinsic automatically
```

**2. SIMD for Bulk Operations**
For processing arrays, consider vectorization:
```c
// Process 4 values at once with SIMD
// (Advanced optimization, not in libft)
```

**3. Avoid Unnecessary Conversions**
```c
// ✓ EFFICIENT - Direct use
t_u32 result = abs_i(value);

// ✗ WASTEFUL - Extra cast
t_i32 temp = abs_i(value);  // Truncates!
t_u32 result = (t_u32)temp;
```

### Benchmark Results

Processing 10 million absolute value calculations:

| Function | Time | Throughput |
|----------|------|------------|
| `abs_i()` | ~5-10 ms | ~1-2 billion ops/sec |
| `abs_l()` | ~5-10 ms | ~1-2 billion ops/sec |

**Note**: Performance depends on CPU, compiler, and whether values are in cache.

---

# Compilation and Usage

This section explains how to build the libft library, include it in your projects, and link against specific modules.

---

## Building the Library

### Quick Start

To build the complete library with all modules:

```bash
make
```

This produces `libft.a`, a static library containing all compiled modules (buffer, list, string, character, and math).

### Makefile Targets

| Command | Description |
|---------|-------------|
| `make` or `make all` | Compiles all source files and creates `libft.a` |
| `make clean` | Removes all object files (`objs/*.o`) |
| `make fclean` | Removes object files and the library (`libft.a`) |
| `make re` | Performs `fclean` followed by `all` (full rebuild) |

### Build Output

```bash
$ make
 ----- libft -----
 Generating objs/buffer_cbuf.o
 Generating objs/buffer_dbuf.o
 Generating objs/buffer_free.o
 Generating objs/buffer_insert.o
 Generating objs/buffer_shift.o
 Generating objs/char_isalnum.o
 Generating objs/char_isalpha.o
 ...
 SUCCESSFULLY generating libft.a
```

The build process:
1. Creates an `objs/` directory if it doesn't exist
2. Compiles each `.c` file to `.o` with category prefixes
3. Archives all object files into `libft.a`

### Compilation Flags

The library is compiled with:
- `-Wall`: Enable all warnings
- `-Wextra`: Enable extra warnings
- `-Werror`: Treat warnings as errors
- `-fPIC`: Position-independent code (for shared library compatibility)

---

## Including Headers

### Main Header

To use libft in your code, include the main header:

```c
#include "libft.h"
```

This single header provides access to **all modules** (buffer, list, string, character, and math).

### Header Location

When compiling your project, specify the header directory:

```bash
gcc -I/path/to/libft/includes your_file.c -L/path/to/libft -lft
```

The `-I` flag tells the compiler where to find `libft.h`.

---

## Module-Specific Headers

While `libft.h` includes everything, you can also include module-specific headers if you prefer fine-grained control:

### Individual Module Headers

```c
#include "libft_buffer.h"   // Buffer module only
#include "libft_list.h"     // List module only
#include "libft_string.h"   // String module only
#include "libft_char.h"     // Character module only
#include "libft_math.h"     // Math module only
#include "libft_types.h"    // Type definitions (t_i32, t_bool, etc.)
```

### Header Dependencies

- `libft_types.h`: Core types (included by all other headers)
- `libft_buffer.h`: Requires `libft_types.h`
- `libft_list.h`: Requires `libft_types.h`
- `libft_string.h`: Requires `libft_types.h`, `libft_buffer.h`
- `libft_char.h`: Requires `libft_types.h`
- `libft_math.h`: Requires `libft_types.h`

### Example: Using Specific Modules

```c
// Only use string and character functions
#include "libft_types.h"
#include "libft_string.h"
#include "libft_char.h"

int main(void)
{
    t_cstr str = cstr("Hello World");
    if (c_isalpha(str.s[0]))
        printf("First character is alphabetic\n");
    return 0;
}
```

---

## Linking with Your Project

### Basic Linking

After building `libft.a`, link it with your project:

```bash
gcc -o my_program my_program.c -L. -lft
```

Breakdown:
- `-L.`: Look for libraries in the current directory
- `-lft`: Link against `libft.a` (drops 'lib' prefix and '.a' suffix)

### Specifying Library Path

If `libft.a` is in a different directory:

```bash
gcc -o my_program my_program.c -L/path/to/libft -lft
```

### Complete Example

```bash
# Build libft
cd /path/to/libft
make

# Compile your program
cd /path/to/your/project
gcc -I/path/to/libft/includes -o my_program main.c \
    -L/path/to/libft -lft
```

---

## Compilation Examples

### Example 1: Simple Program Using Strings

**File: `test_string.c`**
```c
#include "libft.h"
#include <stdio.h>

int main(void)
{
    t_cstr greeting = cstr("Hello, World!");
    t_dbuf words = str_split(greeting, ' ');
    
    t_dstr *array = (t_dstr *)words.data;
    size_t count = words.len / sizeof(t_dstr);
    
    for (size_t i = 0; i < count; i++)
        printf("Word %zu: %s\n", i + 1, array[i].s);
    
    free_dstrs(&words);
    return 0;
}
```

**Compilation:**
```bash
gcc -Wall -Wextra -Werror -I./includes test_string.c -L. -lft -o test_string
./test_string
```

**Output:**
```
Word 1: Hello,
Word 2: World!
```

---

### Example 2: Using Lists and Character Functions

**File: `test_list.c`**
```c
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void print_if_alpha(void *content)
{
    char *str = (char *)content;
    if (c_isalpha(str[0]))
        printf("%s\n", str);
}

int main(void)
{
    t_lst words = lst_();
    
    lst_insert(&words, node("apple"), 0);
    lst_insert(&words, node("123"), 0);
    lst_insert(&words, node("banana"), 0);
    
    printf("Words starting with letter:\n");
    lst_foreach(words, print_if_alpha);
    
    // Content is static strings, use no-op deleter
    void no_del(void *c) { (void)c; }
    free_lst(&words, no_del);
    
    return 0;
}
```

**Compilation:**
```bash
gcc -Wall -Wextra -I./includes test_list.c -L. -lft -o test_list
./test_list
```

**Output:**
```
Words starting with letter:
banana
apple
```

---

### Example 3: Buffer and Math Operations

**File: `test_buffer_math.c`**
```c
#include "libft.h"
#include <stdio.h>

int main(void)
{
    // Create buffer of integers
    t_dbuf buf = dbuf_s(10 * sizeof(int));
    
    int values[] = {-5, 10, -15, 20, -25};
    for (int i = 0; i < 5; i++)
    {
        t_cbuf val = cbuf(&values[i], sizeof(int));
        buf = buf_insertc(buf, val, buf.len, x2_);
    }
    
    // Calculate sum of absolute values
    int *arr = (int *)buf.data;
    size_t count = buf.len / sizeof(int);
    t_u64 sum = 0;
    
    for (size_t i = 0; i < count; i++)
        sum += abs_i(arr[i]);
    
    printf("Sum of absolute values: %lu\n", sum);
    
    free_dbuf(&buf);
    return 0;
}
```

**Compilation:**
```bash
gcc -Wall -Wextra -I./includes test_buffer_math.c -L. -lft -o test_buffer_math
./test_buffer_math
```

**Output:**
```
Sum of absolute values: 75
```

---

## Makefile Integration

### Basic Integration

Add libft as a dependency in your project's Makefile:

```makefile
# Variables
NAME = my_program
LIBFT = libft/libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./libft/includes

# Source files
SRCS = main.c utils.c
OBJS = $(SRCS:.c=.o)

# Rules
all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(NAME): $(OBJS)
	$(CC) $(OBJS) -L./libft -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
```

### Advanced Integration with Automatic Rebuild

```makefile
# Variables
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = $(LIBFT_DIR)/includes

NAME = my_program
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(LIBFT_INC)

SRCS = main.c
OBJS = $(SRCS:.c=.o)

# Rules
all: $(NAME)

# Force libft rebuild check on every make
$(LIBFT): FORCE
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "✓ Built $(NAME) successfully"

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

FORCE:

.PHONY: all clean fclean re FORCE
```

### Usage

```bash
make          # Build libft and your program
make clean    # Clean object files
make fclean   # Clean everything
make re       # Full rebuild
```

---

## Troubleshooting

### Issue 1: "libft.h: No such file or directory"

**Problem:** Compiler can't find the header file.

**Solution:** Specify the include directory with `-I`:
```bash
gcc -I/path/to/libft/includes your_file.c -L/path/to/libft -lft
```

---

### Issue 2: "undefined reference to `cstr`"

**Problem:** Functions are declared but not linked.

**Solution:** Ensure you're linking with `-lft` and the library path is correct:
```bash
gcc your_file.c -L/path/to/libft -lft
```

Check that `libft.a` exists in the specified directory:
```bash
ls -l /path/to/libft/libft.a
```

---

### Issue 3: Link order matters

**Problem:** Getting undefined references even with `-lft`.

**Solution:** Put the library **after** your source files:
```bash
# ✓ CORRECT
gcc main.c utils.c -L./libft -lft

# ✗ WRONG
gcc -lft main.c utils.c
```

---

### Issue 4: Multiple definition errors

**Problem:** Symbols defined multiple times.

**Solution:** Make sure you're not including `.c` files, only `.h` files:
```c
#include "libft.h"     // ✓ Correct
#include "libft.c"     // ✗ Wrong!
```

---

### Issue 5: "Permission denied" when running make

**Problem:** No execute permissions on scripts or the current directory is not writable.

**Solution:**
```bash
chmod +x /path/to/libft  # If directory permission issue
cd /path/to/libft && make  # Ensure you're in the right directory
```

---

## Directory Structure Reference

```
libft/
├── Makefile              # Build configuration
├── README.md             # This documentation
├── includes/             # Header files
│   ├── libft.h           # Main header (includes all modules)
│   ├── libft_buffer.h    # Buffer module types and functions
│   ├── libft_char.h      # Character module functions
│   ├── libft_list.h      # List module types and functions
│   ├── libft_math.h      # Math module functions
│   ├── libft_string.h    # String module types and functions
│   └── libft_types.h     # Core type definitions
├── srcs/                 # Source files
│   ├── buffer/           # Buffer implementation
│   ├── char/             # Character implementation
│   ├── list/             # List implementation
│   ├── math/             # Math implementation
│   └── string/           # String implementation
├── objs/                 # Object files (generated)
└── libft.a               # Compiled library (generated)
```

---

## Quick Reference Card

### Building
```bash
make          # Compile library
make clean    # Remove objects
make fclean   # Remove everything
make re       # Rebuild from scratch
```

### Compiling Your Code
```bash
gcc -I./libft/includes your_file.c -L./libft -lft -o your_program
```

### Essential Includes
```c
#include "libft.h"        // All modules
```

### Module Headers (Optional)
```c
#include "libft_buffer.h" // Buffers
#include "libft_list.h"   // Lists
#include "libft_string.h" // Strings
#include "libft_char.h"   // Characters
#include "libft_math.h"   // Math
```

### Type Definitions Available
- `t_i8`, `t_i32`, `t_i64`: Signed integers
- `t_u8`, `t_u32`, `t_u64`: Unsigned integers
- `t_bool`: Boolean type (`TRUE`, `FALSE`)
- `t_cbuf`, `t_dbuf`: Buffer types
- `t_cstr`, `t_dstr`: String types
- `t_lst`, `t_node`: List types
- `t_buf_strat`: Buffer strategy enum (`E_`, `x2_`)

---

## Integration and Interoperability

The **buffer**, **list**, and **string** modules are designed to work together seamlessly, providing powerful combinations for complex data manipulation.

### Buffer + List Integration

#### Store Buffers in a List
```c
// List of dynamic buffers
t_lst buffer_list = lst_();
t_dbuf *buf = malloc(sizeof(t_dbuf));
*buf = dbuf_s(100);
lst_insert(&buffer_list, node(buf), 0);

// Free with custom deleter
void free_buffer(void *content)
{
    t_dbuf *b = (t_dbuf *)content;
    free_dbuf(b);
    free(b);
}
free_lst(&buffer_list, free_buffer);
```

#### Convert List to Buffer
```c
// Build a list, then convert to contiguous buffer
t_lst items = create_item_list();
t_dbuf array = dbuf_s(items.size * sizeof(item_t));
t_node *curr = items.nodes;
size_t offset = 0;
while (curr)
{
    array = buf_insertc(array, cbuf(curr->content, sizeof(item_t)), 
                        offset, E_);
    offset += sizeof(item_t);
    curr = curr->next;
}
```

---

### String + Buffer Integration

#### Convert Buffer to String
```c
// Build string in a buffer, then convert
t_dbuf buf = dbuf_s(100);
buf = buf_insertc(buf, cbuf("Hello", 5), 0, x2_);
buf = buf_insertc(buf, cbuf(" World", 6), buf.len, x2_);
t_dstr str = dstr_buf(&buf);  // Takes ownership of buffer
// buf is now invalid, str owns the data
```

#### Split String into Buffer Array
```c
// Parse CSV into buffer of strings
t_cstr csv = cstr("name,age,email");
t_dbuf fields = str_split(csv, ',');

// Access as array
t_dstr *array = (t_dstr *)fields.data;
size_t count = fields.len / sizeof(t_dstr);
for (size_t i = 0; i < count; i++)
    printf("Field %zu: %s\n", i, array[i].s);

free_dstrs(&fields);
```

---

### String + List Integration

#### List of Strings
```c
// Create list of dynamic strings
t_lst names = lst_();
lst_insert(&names, node(dstr_c(cstr("Alice"))), 0);
lst_insert(&names, node(dstr_c(cstr("Bob"))), 0);

// Free with string deleter
void free_string(void *content)
{
    t_dstr *s = (t_dstr *)content;
    free_dstr(s);
    free(s);
}
free_lst(&names, free_string);
```

#### Process Strings with List Functions
```c
// Transform strings using lst_map
void *uppercase_string(void *content)
{
    t_dstr *old = (t_dstr *)content;
    t_dstr *new = malloc(sizeof(t_dstr));
    *new = str_map(*old, to_uppercase);
    return new;
}

void free_string_ptr(void *content)
{
    t_dstr *s = (t_dstr *)content;
    free_dstr(s);
    free(s);
}

t_lst strings = create_string_list();
strings = lst_map(strings, uppercase_string, free_string_ptr);
```

---

### Buffer + List + String: Complete Example

```c
#include "libft.h"

// Parse lines from file into structured data
typedef struct s_record
{
    t_dstr name;
    t_i32  age;
    t_dstr email;
} t_record;

t_lst parse_csv_file(const char *filename)
{
    // Read file into buffer
    t_dbuf file_buf = read_file_to_buffer(filename);
    
    // Convert to string for processing
    t_dstr content = dstr_buf(&file_buf);
    
    // Split into lines
    t_dbuf lines = str_split(cstr_d(content), '\n');
    t_dstr *line_array = (t_dstr *)lines.data;
    size_t line_count = lines.len / sizeof(t_dstr);
    
    // Parse each line into a list of records
    t_lst records = lst_();
    for (size_t i = 0; i < line_count; i++)
    {
        t_dbuf fields = str_split(cstr_d(line_array[i]), ',');
        t_dstr *field_array = (t_dstr *)fields.data;
        
        t_record *rec = malloc(sizeof(t_record));
        rec->name = field_array[0];
        rec->age = str_to_int(cstr_d(field_array[1]), cstr(CHARSET_DEC));
        rec->email = field_array[2];
        
        lst_insert(&records, node(rec), records.size);
        free_dbuf(&fields);
    }
    
    free_dstrs(&lines);
    free_dstr(&content);
    return records;
}

void free_record(void *content)
{
    t_record *rec = (t_record *)content;
    free_dstr(&rec->name);
    free_dstr(&rec->email);
    free(rec);
}

// Usage
t_lst data = parse_csv_file("users.csv");
// ... process records ...
free_lst(&data, free_record);
```

---

### Character + String Integration

#### String Validation with Character Functions
```c
#include "libft.h"

/**
 * Validate that a string contains only alphanumeric characters
 */
t_bool is_alphanumeric_string(t_cstr str)
{
    for (size_t i = 0; i < str.len; i++)
    {
        if (!c_isalnum(str.s[i]))
            return (FALSE);
    }
    return (TRUE);
}

// Usage
t_cstr username = cstr("user123");
if (is_alphanumeric_string(username))
    printf("Valid username\n");
```

#### Case Conversion with String Module
```c
#include "libft.h"

/**
 * Convert string to uppercase using character functions
 */
t_i8 to_upper_char(t_u32 i, t_i8 c)
{
    (void)i;
    return (c_toupper(c));
}

t_dstr str_to_upper(t_dstr str)
{
    return str_map(str, to_upper_char);
}

// Usage
t_dstr text = dstr_c(cstr("hello world"));
text = str_to_upper(text);
// text.s = "HELLO WORLD"
free_dstr(&text);
```

---

### Math + String Integration

#### Parsing with Validation
```c
#include "libft.h"

/**
 * Parse integer from string with validation
 */
t_bool parse_signed_int(t_cstr str, t_i32 *result)
{
    if (str.len == 0)
        return (FALSE);
    
    size_t i = 0;
    t_bool negative = FALSE;
    
    // Handle sign
    if (str.s[0] == '-')
    {
        negative = TRUE;
        i++;
    }
    else if (str.s[0] == '+')
        i++;
    
    // Validate remaining characters are digits
    if (i >= str.len)
        return (FALSE);
    
    for (; i < str.len; i++)
    {
        if (!c_isdigit(str.s[i]))
            return (FALSE);
    }
    
    // Parse the number
    t_i32 value = str_to_int(str, cstr(CHARSET_DEC));
    *result = negative ? -abs_i(value) : value;
    
    return (TRUE);
}

// Usage
t_i32 value;
if (parse_signed_int(cstr("-42"), &value))
    printf("Parsed: %d\n", value);
```

#### Distance Calculations with Strings
```c
#include "libft.h"

/**
 * Compute edit distance using absolute value
 */
t_u32 char_distance(t_i8 a, t_i8 b)
{
    return abs_i((t_i32)a - (t_i32)b);
}

// Usage in string comparison
t_u64 string_distance(t_cstr s1, t_cstr s2)
{
    size_t min_len = s1.len < s2.len ? s1.len : s2.len;
    t_u64 distance = 0;
    
    for (size_t i = 0; i < min_len; i++)
        distance += char_distance(s1.s[i], s2.s[i]);
    
    // Add penalty for length difference
    distance += abs_l((t_i64)s1.len - (t_i64)s2.len) * 10;
    
    return distance;
}
```

---

### Complete Integration Example: Text Processing Pipeline

```c
#include "libft.h"

/**
 * Process text file: filter, normalize, count words
 */

// Step 1: Filter non-printable characters
t_dstr filter_text(t_dstr input)
{
    t_i8 filter_char(t_u32 i, t_i8 c)
    {
        (void)i;
        return c_isprint(c) ? c : ' ';
    }
    return str_map(input, filter_char);
}

// Step 2: Normalize to lowercase
t_dstr normalize_text(t_dstr input)
{
    t_i8 lower_char(t_u32 i, t_i8 c)
    {
        (void)i;
        return c_tolower(c);
    }
    return str_map(input, lower_char);
}

// Step 3: Split into words and count
typedef struct s_word_count
{
    t_dstr word;
    size_t count;
} t_word_count;

t_lst count_words(t_cstr text)
{
    // Split by spaces
    t_dbuf words = str_split(text, ' ');
    t_dstr *word_array = (t_dstr *)words.data;
    size_t word_count = words.len / sizeof(t_dstr);
    
    // Build list of unique words with counts
    t_lst counts = lst_();
    
    for (size_t i = 0; i < word_count; i++)
    {
        if (word_array[i].len == 0)
            continue;
        
        // Check if word already exists
        t_bool found = FALSE;
        t_node *curr = counts.nodes;
        
        while (curr)
        {
            t_word_count *wc = (t_word_count *)curr->content;
            if (str_cmp(cstr_d(wc->word), cstr_d(word_array[i])) == 0)
            {
                wc->count++;
                found = TRUE;
                free_dstr(&word_array[i]);
                break;
            }
            curr = curr->next;
        }
        
        if (!found)
        {
            t_word_count *wc = malloc(sizeof(t_word_count));
            wc->word = word_array[i];
            wc->count = 1;
            lst_insert(&counts, node(wc), 0);
        }
    }
    
    free_dbuf(&words);
    return counts;
}

// Main pipeline
void process_text_file(const char *filename)
{
    // Read file
    t_dbuf file_buf = read_file_to_buffer(filename);
    t_dstr content = dstr_buf(&file_buf);
    
    // Filter and normalize
    content = filter_text(content);
    content = normalize_text(content);
    
    // Trim whitespace
    content = str_trim(content, cstr(" \t\n\r"));
    
    // Count words
    t_lst word_counts = count_words(cstr_d(content));
    
    // Print results
    printf("Word counts:\n");
    t_node *curr = word_counts.nodes;
    while (curr)
    {
        t_word_count *wc = (t_word_count *)curr->content;
        printf("  %s: %zu\n", wc->word.s, wc->count);
        curr = curr->next;
    }
    
    // Cleanup
    void free_word_count(void *content)
    {
        t_word_count *wc = (t_word_count *)content;
        free_dstr(&wc->word);
        free(wc);
    }
    
    free_lst(&word_counts, free_word_count);
    free_dstr(&content);
}
```

This example demonstrates:
- **Character module**: Filtering and case conversion
- **String module**: Parsing, trimming, splitting
- **List module**: Storing word counts
- **Buffer module**: Initial file reading
- **Math module**: Could be used for statistical analysis

---

## Thread Safety

⚠️ **Not Thread-Safe**: Buffer, list, string, character, and math operations are not thread-safe by design.

**Recommendations**:
- Use separate data structures per thread
- Synchronize access with mutexes when sharing
- Never share `t_dbuf`, `t_dstr`, or `t_lst` across threads without protection
- Read-only access to constant types (`t_cbuf`, `t_cstr`) may be safe but is still risky
- Character and math functions are stateless but not designed for concurrent access to shared data

---

## Conclusion

The **Libft** library provides a comprehensive, powerful toolkit for C programming, with five specialized modules covering data structures, string manipulation, character operations, and mathematical utilities.

---

### Module Summaries

#### Buffer Module Summary

The buffer module excels at:
- Raw binary data manipulation
- Building dynamic arrays of any type
- Zero-copy views and slicing
- Efficient memory reallocation strategies

**Key Takeaways**:
1. Use `t_cbuf` for views, `t_dbuf` for ownership
2. Always reassign after consuming operations
3. Choose `x2_` for performance, `E_` for space efficiency
4. Check for allocation failures
5. Free dynamic buffers promptly

---

#### List Module Summary

The list module excels at:
- Sequential data collections with frequent insertions
- Unknown or highly variable sizes
- Functional programming patterns (`map`, `foreach`)
- Flexible content ownership models

**Key Takeaways**:
1. Lists own node structures, content ownership is flexible
2. Use `lst_foreach` for iteration, not repeated `get()`
3. Insert at head for O(1) performance
4. Always provide appropriate deletion callbacks
5. `lst_map` consumes and replaces the input list
6. Check NULL returns from `node()` and `get()`

---

#### String Module Summary

The string module excels at:
- Safe, convenient string manipulation
- Automatic length tracking
- String transformations and parsing
- Base conversion and number formatting

**Key Takeaways**:
1. Use `t_cstr` for views, `t_dstr` for ownership
2. Always reassign after consuming operations (`str_trim`, `str_map`)
3. Check NULL returns from search functions
4. Use `free_dstrs()` for split results
5. Leverage pre-computed `.len` field
6. Handle base conversions with standard charset constants

---

#### Character Module Summary

The character module excels at:
- ASCII character classification
- Case conversion
- Input validation
- Text processing primitives

**Key Takeaways**:
1. All functions are O(1) and extremely fast
2. Use type-safe functions instead of magic numbers
3. Check ASCII validity for extended characters
4. Combine with string functions for powerful text processing
5. Functions are stateless and can be freely composed
6. Ideal for parsing, validation, and normalization

---

#### Math Module Summary

The math module excels at:
- Overflow-safe absolute values
- Handling edge cases (INT_MIN, INT_MAX)
- Type-safe mathematical operations
- Distance and difference calculations

**Key Takeaways**:
1. Returns unsigned types to avoid overflow
2. Handles `I32_MIN` and `I64_MIN` correctly
3. Use appropriate size (`abs_i` vs `abs_l`)
4. Promote to larger types before subtraction
5. Extremely fast (1-4 CPU cycles)
6. Perfect for distance metrics and comparisons

---

### Choosing the Right Tools

| Module | Best For | Avoid When |
|--------|----------|------------|
| **Buffer** | Binary data, arrays, protocols | Need null-termination, text processing |
| **List** | Dynamic collections, frequent insertions | Need random access, cache-sensitive |
| **String** | Text manipulation, parsing, formatting | Binary data, fixed formats |
| **Character** | Single-char tests, validation, case | Unicode/UTF-8, complex text |
| **Math** | Absolute values, distances | Need full math library |

---

### Data Structure Comparison

| Feature | Buffer | List | String |
|---------|--------|------|--------|
| **Random Access** | O(1) | O(n) | O(1) |
| **Insert at Head** | O(n) | O(1) | O(n) |
| **Insert at End** | O(1)* | O(n) | O(1)* |
| **Memory Layout** | Contiguous | Fragmented | Contiguous |
| **Null-Terminated** | No | No | Yes |
| **Best Use Case** | Binary data | Collections | Text |

*Amortized with growth strategy

---

### Common Integration Patterns

#### Pattern 1: Text File Processing
```c
// Read → String → Character validation → Parse → List
t_dbuf file = read_file(path);
t_dstr text = dstr_buf(&file);
text = normalize_text(text);  // Uses character functions
t_lst records = parse_records(text);  // Uses string functions
```

#### Pattern 2: Binary Protocol Parsing
```c
// Buffer → Extract → Validate → Convert
t_dbuf packet = receive_packet();
t_cbuf header = cbuf(packet.data, HEADER_SIZE);
if (validate_header(header))
    process_payload(buf_shift(packet, HEADER_SIZE));
```

#### Pattern 3: Dynamic String Building
```c
// String → Character transformation → Buffer output
t_dstr result = dstr_s(1024);
for (each item)
{
    t_dstr formatted = format_item(item);  // String functions
    formatted = filter_text(formatted);     // Character functions
    result = str_insertc(result, cstr_d(formatted), result.len);
    free_dstr(&formatted);
}
```

#### Pattern 4: Data Collection and Analysis
```c
// List → Extract values → Math operations → Statistics
t_lst data = collect_measurements();
t_i32 sum = 0;
t_u32 max_deviation = 0;

t_node *curr = data.nodes;
while (curr)
{
    t_i32 value = *(t_i32 *)curr->content;
    sum += value;
    t_u32 dev = abs_i(value - average);
    if (dev > max_deviation)
        max_deviation = dev;
    curr = curr->next;
}
```

---

### Design Philosophy

**Libft** follows these principles:

1. **Type Safety**: Custom types (`t_i32`, `t_bool`) prevent common errors
2. **Ownership Clarity**: Functions that consume inputs are clearly documented
3. **Zero-Copy Where Possible**: Use views (`t_cbuf`, `t_cstr`) to avoid allocation
4. **Predictable Behavior**: No hidden allocations or surprising side effects
5. **Composability**: Modules work together seamlessly
6. **Performance**: O(1) operations where possible, efficient algorithms
7. **Safety**: Handle edge cases (overflow, NULL, empty) gracefully

---

### Best Practices Summary

1. **Memory Management**
   - Free resources promptly
   - Always reassign after consuming operations
   - Check for allocation failures
   - Use appropriate deletion callbacks for lists

2. **Type Selection**
   - Use constant types for views (`t_cbuf`, `t_cstr`)
   - Use dynamic types for ownership (`t_dbuf`, `t_dstr`)
   - Use character functions for single-char operations
   - Use appropriate integer sizes (`abs_i` vs `abs_l`)

3. **Performance**
   - Leverage O(1) operations (buffer access, character checks)
   - Avoid O(n²) patterns (repeated `get()` on lists)
   - Pre-allocate when size is known
   - Use growth strategies appropriately (`x2_` vs `E_`)

4. **Safety**
   - Validate inputs with character functions
   - Check NULL returns
   - Handle overflow with appropriate types
   - Document ownership and memory requirements

5. **Integration**
   - Combine modules for complex operations
   - Use character functions with strings
   - Use math functions for string parsing validation
   - Build processing pipelines efficiently

---

### When to Use Each Module

**Use Buffers** for:
- Network protocols
- File I/O
- Binary data manipulation
- Building dynamic arrays
- Interfacing with C APIs

**Use Lists** for:
- Unknown collection sizes
- Frequent head insertions
- Functional transformations
- Flexible ownership models
- Sequential processing

**Use Strings** for:
- Text parsing and generation
- User input handling
- File format processing
- Number conversions
- String searching and manipulation

**Use Character Functions** for:
- Input validation
- Case normalization
- Identifier checking
- Text filtering
- Single-character classification

**Use Math Functions** for:
- Distance calculations
- Difference computations
- Overflow-safe absolute values
- Comparison metrics
- Range validations

---

### Conclusion

The **Libft** library transforms C programming from low-level memory manipulation into a high-level, safe, and efficient development experience. With five specialized modules working in harmony, you can build complex applications while maintaining:

- **Safety**: Type-safe operations with edge case handling
- **Performance**: O(1) operations and efficient algorithms
- **Clarity**: Clear ownership models and predictable behavior
- **Flexibility**: Multiple data structures for different needs
- **Composability**: Modules integrate seamlessly

Whether you're building parsers, data processors, network tools, or general applications, libft provides the foundation for robust C programming.

---

*Last Updated: January 2, 2026*  
*Comprehensive documentation for the libft Buffer, List, String, Character, and Math modules*  
*Part of the libft library for 42 School projects*
