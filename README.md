*This project has been created as part of the 42 curriculum by dtorregr.*

---

## Description

**Printf-reimagened** is a custom implementation of the standard C library's `printf` function. This project replicates the core functionality of the standard output formatting function, allowing for formatted string printing with support for multiple data types and format specifiers.

### Goal

The primary objective of this project is to:
- Understand the inner workings of variadic functions in C
- Implement format string parsing and interpretation
- Handle type conversion and formatting for various data types
- Demonstrate mastery of C fundamentals including pointers, memory management, and low-level I/O operations

### Overview

This implementation supports the following format specifiers:
- `%c` - Character printing
- `%s` - String printing
- `%p` - Pointer address printing (hexadecimal notation)
- `%d` - Signed decimal integer printing
- `%i` - Signed decimal integer printing (same as %d)
- `%u` - Unsigned decimal integer printing
- `%x` - Unsigned hexadecimal integer printing (lowercase)
- `%X` - Unsigned hexadecimal integer printing (uppercase)
- `%%` - Literal percent character

The function returns the total number of characters printed, maintaining compatibility with the behavior of the standard `printf` function.

---

## Instructions

### Compilation

To compile the project and generate the static library `libftprintf.a`:

```bash
make
```

### Cleaning

To remove object files:

```bash
make clean
```

To remove both object files and the library:

```bash
make fclean
```

To rebuild the project from scratch:

```bash
make re
```

### Project Structure

The project is organized into modular components:

- **ft_printf.c** - Main function implementation and format string parsing logic
- **chars_printer.c** - Character and string printing functions
- **digits_printer.c** - Signed and unsigned decimal integer printing
- **hex_printer.c** - Hexadecimal conversion and printing
- **ft_printf.h** - Header file with function declarations
- **Makefile** - Build automation

### Usage Example

To use the `ft_printf` function in your own code:

```c
#include "ft_printf.h"

int main(void)
{
    int count;
    
    count = ft_printf("Hello %s!\n", "World");
    ft_printf("Returned: %d characters\n", count);
    
    ft_printf("Number: %d, Hex: %x\n", 255, 255);
    ft_printf("Pointer: %p\n", &count);
    
    return (0);
}
```

Compile with:

```bash
gcc your_file.c -L. -lftprintf -o your_program
```

---

## Algorithm and Data Structure Explanation

### Parsing Strategy

The `ft_printf` function employs a **linear sequential scanning algorithm** to process the format string character by character:

1. **Character-by-character iteration**: The algorithm iterates through the input string with a pointer (`i`), examining each character.
2. **Format specifier detection**: When a `%` character is encountered followed by a valid format specifier, the parser delegates to the appropriate printing function.
3. **Direct output**: Non-format characters are written directly to standard output using the `write()` system call.

**Justification**: This approach is optimal for this use case because:
- Linear time complexity O(n) is achieved, where n is the string length
- Single-pass processing minimizes memory overhead
- Early detection of format specifiers allows for immediate delegation to specialized handlers
- No need for complex state machines or lookahead mechanisms

### Variadic Function Implementation

The implementation uses the `<stdarg.h>` library with the following pattern:

```c
va_list args;
va_start(args, str);
// ... retrieve arguments with va_arg(args, type) ...
va_end(args);
```

**Justification**: The standard variadic approach is used because:
- It is portable across different C implementations
- It provides type-safe (at compile time) access to variadic arguments
- It naturally aligns with the function's expected behavior matching standard `printf`

### Format Specifier Dispatching

The `parse_and_print()` function uses a **series of conditional checks** to dispatch to the appropriate printer:

```c
if (c == 'c')
    return (print_char(va_arg(var, int)));
else if (c == 's')
    return (print_string(va_arg(var, char *)));
// ... additional specifiers ...
```

**Justification**: 
- Direct conditional dispatching is simple and efficient for a limited set of specifiers
- Average case complexity is O(1) with typically 2-3 comparisons
- More readable and maintainable than switch statements or function pointer tables for this scope
- Avoids unnecessary overhead for a small set of handlers

### Data Type Handling

#### Character and String Output
- **chars_printer.c** handles `%c` and `%s` specifiers
- Direct `write()` system calls for minimal overhead
- Return value represents characters written

#### Decimal Conversion
- **digits_printer.c** implements decimal conversion for both signed (`%d`, `%i`) and unsigned (`%u`) integers
- Uses the classic **division-by-base algorithm** to extract digits in reverse order
- Negative numbers are handled with sign detection and conversion to absolute value
- Buffer reversal technique is employed for correct digit ordering

**Algorithm Detail**:
```
1. Handle sign for negative numbers
2. Initialize accumulator for reversed digits
3. Repeatedly: digit = number % 10; accumulate digit; number /= 10
4. Reverse accumulated digits
5. Output each digit character
```

#### Hexadecimal Conversion
- **hex_printer.c** implements `%x` and `%X` specifiers
- Uses the **division-by-16 algorithm** with direct character mapping
- Support for both lowercase and uppercase output through the `upper` parameter
- Digit-to-character mapping: 0-9 → '0'-'9', 10-15 → 'a'-'f' or 'A'-'F'

#### Pointer Printing
- Pointers are cast to `unsigned long` for architecture independence
- Printed with the `0x` prefix followed by hexadecimal representation
- Ensures compatibility with 32-bit and 64-bit systems

### Return Value Semantics

Each specialized printer function returns the number of characters written. The main `ft_printf` function accumulates these counts and returns the total, exactly matching the behavior of the standard library function.

---

## Resources

### References and Documentation
- [Linux man pages - write(2) system call](https://man7.org/linux/man-pages/man2/write.2.html)
- [Linux man pages - printf(3) standard library](https://man7.org/linux/man-pages/man3/printf.3.html)
- [Linux man pages - stdarg(3) variadic arguments](https://man7.org/linux/man-pages/man3/stdarg.3.html)

### Learning and Collaboration
- Discussions with peers and colleagues at 42 School regarding variadic function behavior and format string parsing

### AI Usage

AI was used for explaining variadic arguments (`stdarg.h`) functionality and concepts during the development process. Specifically, AI assistance was utilized to:
- Clarify how `va_start()`, `va_arg()`, and `va_end()` macros work internally
- Explain the relationship between function parameters and the argument stack
- Understand type promotion rules when using `va_arg()`
- Provide conceptual background on why certain casting patterns are necessary

All core implementation, algorithm design, and debugging were completed independently.

---

## Technical Choices

### Why the `write()` System Call?

The project uses the `write()` system call instead of `putchar()` or buffered I/O because:
- Direct system call access provides fine-grained control over output
- Avoids buffering complications
- Aligns with low-level C programming practices emphasized in systems programming
- Returns the number of bytes written, which is required for accurate return value calculation

### Why Separate Printer Modules?

The code is organized into separate source files (`chars_printer.c`, `digits_printer.c`, `hex_printer.c`) for:
- **Modularity**: Each concern is isolated
- **Reusability**: Printer functions can be individually tested and debugged
- **Maintainability**: Changes to one format specifier don't affect others
- **Build clarity**: The Makefile makes dependencies explicit

### Modular Compilation

The Makefile compiles each source file into an object file, then links them into a static library. This approach:
- Follows standard C project conventions
- Allows for incremental compilation (only changed files recompile)
- Produces a reusable library archive
- Demonstrates professional build system practices

---

## Testing

The project includes a commented-out test suite in `ft_printf.c` that compares output from the custom implementation against the standard library's `printf`. To enable testing:

1. Uncomment the `main()` function in `ft_printf.c`
2. Rebuild with `make re`
3. Run the executable to see side-by-side comparisons

---

## Notes

- This implementation does not support all format specifiers of the full `printf` function (e.g., width, precision, flags)
- The project is designed for educational purposes to understand C fundamentals
- Performance is optimized for clarity and correctness over edge-case handling
- Compliance with 42 Norm coding standards is maintained throughout
