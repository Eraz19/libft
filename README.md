# Libft Documentation

- [Overview](#overview)
- [Core Modules](#core-modules)
  - [Buffer Module](#buffer-module)
  - [String Module](#string-module)
  - [List Module](#list-module)
  - [Character Module](#character-module)
  - [Math Module](#math-module)
  - [Printf Module](#printf-module)
  - [Get Next Line Module](#get-next-line-module)
- [Memory Ownership Philosophy](#memory-ownership-philosophy)
  - [Core Principle](#core-principle)
  - [Ownership Transfer](#ownership-transfer)
  - [Common Pitfalls](#common-pitfalls)
- [Compilation and Usage](#compilation-and-usage)
  - [Building the Library](#building-the-library)
  - [Testing](#testing)
  - [Including Headers](#including-headers)
  - [Module-Specific Headers](#module-specific-headers)
  - [Linking with Your Project](#linking-with-your-project)
- [Conclusion](#conclusion)

---

# Overview

**Libft** is a comprehensive C standard library implementation for 42 School projects. It provides essential data structures and utilities with a focus on performance, safety, and ease of use.

**Core Modules**:
- **Buffer Module**: Flexible raw memory buffer management
- **List Module**: Singly-linked list with size tracking
- **String Module**: Advanced string manipulation
- **Character Module**: Character classification and transformation
- **Math Module**: Mathematical utilities
- **Printf Module**: Formatted output functions
- **Get Next Line Module**: Line-by-line file reading

Each module code can be navigated like this:

- Types and function prototypes are in `libft/includes/libft_<module>.h`
- Implementations are in `libft/srcs/<module>/**/*.c`

**IMPORTANT**: For each function, detailed documentation is provided in the header files, including descriptions, parameters, return values, examples, error handling, and memory management guidelines.

# Core Modules

## Buffer Module

The **Buffer Module** provides a flexible and efficient system for managing raw memory buffers in C. It implements two complementary buffer types for different use cases.

**Key Features**:
- **Constant Buffers (`t_cbuf`)**: Immutable views into existing memory
- **Dynamic Buffers (`t_dbuf`)**: Growable, heap-allocated buffers
- **Growth Strategies**: Exact (`E`) or exponential (`x2`) allocation modes
- **Type-Agnostic**: Work with any binary data
- **Zero-Copy Operations**: Efficient buffer slicing

This module is designed for scenarios requiring binary data manipulation, dynamic array management, and efficient memory operations without the constraints of null-terminated strings.

## String Module

The **String Module** provides an advanced string manipulation system built on top of the buffer module. It implements two complementary string types that combine the power of C strings with modern safety and convenience features.

**Key Features**:
- **Constant Strings (`t_cstr`)**: Immutable string views with length tracking
- **Dynamic Strings (`t_dstr`)**: Growable, heap-allocated strings
- **Automatic Length Tracking**: No need for strlen() calls
- **Type Conversions**: Convert between integers, longs, and strings with any base
- **Rich API**: Split, trim, find, compare, and more
- **Null-Terminated**: Compatible with standard C string functions

This module is designed for efficient string manipulation while maintaining safety and avoiding common C string pitfalls like buffer overflows.

## List Module

The **List Module** provides a singly-linked list implementation with a comprehensive API for managing dynamic collections in C. It implements a wrapper structure that tracks both the head node and list size for efficient operations.

**Key Features**:
- **Size Tracking**: O(1) size queries without traversal
- **Type-Agnostic**: Store any data type via `void*` pointers
- **Flexible Insertion**: Insert at any position in the list
- **Functional Iteration**: `foreach` and `map` operations
- **Safe Memory Management**: Customizable deletion callbacks

This module is ideal for dynamic collections where insertion order matters and random access is not frequently required.

## Character Module

The **Character Module** provides a complete set of character classification and case conversion utilities. These functions are type-safe wrappers around standard C library character functions, using libft's custom type system.

**Key Features**:
- **Type-Safe**: Uses `t_i32` and `t_bool` custom types
- **Complete Coverage**: All standard character classification functions
- **Case Conversion**: Upper and lowercase transformations
- **ASCII Validation**: Check character encoding validity
- **Consistent API**: Uniform return types and behavior

These functions are essential building blocks for string processing, parsing, and validation operations.

## Math Module

The **Math Module** provides essential mathematical utility functions, starting with robust absolute value implementations. These functions are designed to handle edge cases safely and return appropriate unsigned types.

**Key Features**:
- **Overflow Safe**: Correctly handles minimum integer values
- **Type Conversion**: Returns unsigned types to avoid overflow
- **Multiple Sizes**: Supports both 32-bit and 64-bit integers
- **Predictable**: No undefined behavior for edge cases

## Printf Module

The **Printf Module** implements a custom formatted output function similar to the standard `printf`. It supports a wide range of format specifiers and provides enhanced safety and flexibility.

**Key Features**:
- **Custom Format Specifiers**: Extended functionality
- **Type Safety**: Uses libft's custom types
- **Buffer Management**: Efficient output handling
- **Error Handling**: Robust against format string issues

This module is ideal for applications requiring formatted output with enhanced capabilities beyond the standard library.

## Get Next Line Module

The **Get Next Line Module** provides efficient line-by-line reading from file descriptors. Unlike the standard implementation, it requires explicit reader state management, giving you full control over memory and supporting advanced use cases.

**Key Features**:
- **Line-by-Line Reading**: Efficiently reads until newline or EOF
- **Explicit State Management**: Caller controls the reader list lifetime
- **Multiple FDs**: Supports concurrent reads from different file descriptors
- **Thread-Safe Potential**: Each thread can maintain its own reader state
- **No Memory Leaks**: Clean up readers at your discretion

**Usage Pattern**:
```c
t_readers readers = {0};  // Initialize reader list
t_dstr line;

while ((line = get_next_line(fd, &readers)).s != NULL)
{
    // Process line
    free_dstr(&line);
}
close(fd);
free_lst(&readers, free_reader_content);  // Clean up all readers
```

This design allows reopening files, managing multiple file descriptors, and explicit resource cleanup.

# Memory Ownership Philosophy

Libft uses a **move semantics** approach for dynamic data structures, where functions that modify data often take ownership of the original and return a new instance. This design prevents use-after-free bugs and makes memory management explicit.

## Core Principle

**Functions that modify dynamic structures consume the input and return a new value:**

```c
// ✓ CORRECT: Always reassign when ownership transfers
str = str_insert(&str, &insert_str, 0);
buf = buf_insert(&buf, &insert_buf, 0, x2);
```

The original `str` or `buf` is consumed (potentially freed and reallocated). You **must** reassign the return value to continue using the structure.

## Ownership Transfer

**When a function takes a pointer to a dynamic structure (`t_dstr*`, `t_dbuf*`), it may transfer ownership:**

- The function may free the original memory
- The function returns a new instance (possibly with the same pointer, possibly different)
- **You must capture and use the return value**

**Constant structures (`t_cstr`, `t_cbuf`) never transfer ownership** — they're just views into existing memory.

## Common Pitfalls

### ❌ WRONG: Ignoring the return value

```c
t_dstr str = dstr_s(10);
str_insert(&str, &other, 0);  // BUG: Return value ignored!
// str might now point to freed memory
```

### ✓ CORRECT: Always reassign

```c
t_dstr str = dstr_s(10);
str = str_insert(&str, &other, 0);  // ✓ Reassigned
```

### ❌ WRONG: Using the structure after transfer

```c
t_dstr str = dstr_s(10);
t_dstr new_str = str_insert(&str, &other, 0);
// str is now invalid — don't use it!
```

### ✓ CORRECT: Only use the returned value

```c
t_dstr str = dstr_s(10);
str = str_insert(&str, &other, 0);
// Only use 'str' from now on
```

### Key Rules

1. **Always reassign**: `str = str_insert(&str, ...)`
2. **Never reuse after transfer**: The old value is invalid
3. **Check return values**: NULL indicates allocation failure
4. **Free when done**: Call `free_dstr()`, `free_dbuf()`, etc.

This ownership model makes memory management predictable and prevents entire classes of bugs common in C programming.

# Compilation and Usage

This section explains how to build the libft library, include it in your projects, and link against specific modules.

## Building the Library

```bash
make          # Compile library
make clean    # Remove objects
make fclean   # Remove everything
make re       # Rebuild from scratch
```

## Testing

To run the comprehensive test suite for libft:

```bash
make test
```

## Including Headers

To use libft in your code, include the main header:

```c
#include "libft.h"
```

This single header provides access to **all modules**.

When compiling, specify the include directory:

```bash
gcc -I/path/to/libft/includes your_file.c -L/path/to/libft -lft
```

## Module-Specific Headers

For fine-grained control, include individual module headers:

```c
#include "libft_types.h"    // Type definitions (t_i32, t_bool, etc.)
#include "libft_buffer.h"   // Buffer module
#include "libft_list.h"     // List module
#include "libft_string.h"   // String module
#include "libft_char.h"     // Character module
#include "libft_math.h"     // Math module
#include "libft_printf.h"   // Printf module
#include "libft_gnl.h"      // Get Next Line module
```

**Dependencies**: All modules require `libft_types.h`. String, Printf, and GNL modules also require `libft_buffer.h`.

## Linking with Your Project

After building `libft.a`, link it with your project:

```bash
gcc -o my_program my_program.c -L/path/to/libft -lft
```

- `-L` specifies the library directory
- `-lft` links against `libft.a`

# Conclusion

The **Libft** library transforms C programming from low-level memory manipulation into a safer, more efficient development experience. With seven specialized modules working in harmony, you can build complex applications while maintaining:

- **Safety**: Explicit ownership prevents use-after-free bugs
- **Performance**: O(1) operations and efficient algorithms
- **Clarity**: Predictable memory management and clear API contracts
- **Flexibility**: Multiple data structures for different use cases
- **Composability**: Modules integrate seamlessly

Whether you're building parsers, data processors, network tools, or general applications, libft provides a solid foundation for robust C programming with modern safety guarantees.
