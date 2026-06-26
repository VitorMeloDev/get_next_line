*This project has been created as part of the 42 curriculum by vfreitass.*

# Get Next Line

## Description

**Get Next Line** is a project from the 42 curriculum whose goal is to implement a function capable of reading a file descriptor one line at a time.

Unlike standard file reading functions, `get_next_line()` must preserve the unread part of the file between calls, allowing the user to repeatedly call the function until the end of the file is reached.

The project introduces important concepts of low-level programming in C, including:

* File descriptors
* Dynamic memory allocation
* Static variables
* Buffer management
* String manipulation
* Memory leak prevention

The function prototype is:

```c
char *get_next_line(int fd);
```

It returns:

* A dynamically allocated string containing the next line (including `\n` when present).
* `NULL` when the end of the file is reached or an error occurs.

---

# Project Structure

```
.
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
└── README.md
```

---

# Algorithm

The implementation is based on a persistent buffer stored in a **static variable**.

The algorithm follows these steps:

1. Read data from the file descriptor using `read()` into a temporary buffer of size `BUFFER_SIZE`.
2. Append the newly read data to the static buffer.
3. Continue reading until either:

   * a newline (`\n`) is found, or
   * `read()` reaches the end of the file.
4. Extract the first complete line from the accumulated buffer.
5. Save the remaining characters for the next call.
6. Return the extracted line.
7. Repeat until no data remains.

Using a static variable allows the function to preserve unread data between consecutive calls without exposing any internal state to the caller.

This design works independently of the chosen `BUFFER_SIZE`, making the function behave correctly whether the buffer size is very small (e.g. `1`) or very large (e.g. `10000`).

---

# Instructions

A simple test can be performed using the following `main.c` and a sample text file.

## Test File

Create a file named:

```text
Tomb Raider
```

with the following content:

```text
What will, the next Tomb Raider be like?,
Although the game has not been fully revealed yet, developers have shared a few interesting details about its direction.
The next Tomb Raider is being developed by Crystal Dynamics using Unreal Engine 5. This is significant because Unreal Engine 5 offers powerful tools for creating detailed environments, advanced lighting, and larger worlds than many previous generations of games.
One of the biggest questions concerns Lara Croft herself.
```

---

## Test Program

Create a file named `main.c`:

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("Tomb Raider", O_RDONLY);
	if (fd < 0)
		return (1);
	str = get_next_line(fd);
	printf(" - 1: %s\n", str);
	free(str);
	str = get_next_line(fd);
	printf(" - 2: %s\n", str);
	free(str);
	str = get_next_line(fd);
	printf(" - 3: %s\n", str);
	free(str);
	str = get_next_line(fd);
	printf(" - 4: %s\n", str);
	free(str);
	close(fd);
	return (0);
}
```

---

## Compilation

Compile using a buffer size of 42:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
main.c get_next_line.c get_next_line_utils.c -o gnl
```

For debugging with GDB or Valgrind:

```bash
cc -Wall -Wextra -Werror -g -D BUFFER_SIZE=42 \
main.c get_next_line.c get_next_line_utils.c -o gnl
```

---

## Running

```bash
./gnl
```

Expected output:

```text
 - 1: What will, the next Tomb Raider be like?,

 - 2: Although the game has not been fully revealed yet, developers have shared a few interesting details about its direction.

 - 3: The next Tomb Raider is being developed by Crystal Dynamics using Unreal Engine 5. This is significant because Unreal Engine 5 offers powerful tools for creating detailed environments, advanced lighting, and larger worlds than many previous generations of games.

 - 4: One of the biggest questions concerns Lara Croft herself.
```

---

## Memory Check

To verify memory safety:

```bash
valgrind --leak-check=full ./gnl
```

Expected result after reading the entire file:

```text
All heap blocks were freed -- no leaks are possible
```

---


# Resources

### Documentation

* The Linux Programming Interface — Michael Kerrisk
* Advanced Programming in the UNIX Environment — W. Richard Stevens
* Linux manual page

### AI Usage

Artificial Intelligence was used as a learning assistant throughout the project.

Its usage included:

* Explaining concepts related to file descriptors and static variables.
* Reviewing memory management decisions.
* Helping interpret Valgrind reports.
* Discussing algorithm design and debugging strategies.
* Reviewing documentation and improving the README.

All implementation, debugging, testing, and final code decisions were performed manually.
