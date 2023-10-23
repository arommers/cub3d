<img src="https://i.imgur.com/HG66CCx.png?raw=true" alt="CODAM" style="max-width: 50%;">

# Libft
The libft project is a custom C library, providing a comprehensive set of standard C functions for tasks like string manipulation, memory allocation, and linked list handling.  

All the functions we've created in this repo are linked and packaged up into a static library called libft.a.  
Think of it as a handy toolbox for essential C utilities. We can link this library to our other projects and tap into this treasure trove of helpful functions.
Libft is a solid foundation to build upon, for many of our future projects.  

Our own trusty sidekick for coding in C!

---
### Key Concepts:
- Algorithms and data structures
- String handling functions (strlen, strcpy, strcat, etc.)
- Memory management functions (malloc, free, memset, etc.)
- Character manipulation functions (isalpha, isdigit, tolower, etc.)
- Additional utility functions for various common tasks (ft_split, str_trim, itoa, etc)
- Linked list operations for dynamic data structures
- Makefile construction
---

### Usage*:

- **Clone the repository:**

  Either use the following command in your terminal: `git clone https://github.com/arommers/libft.git`  
  Or Click the green "Code" button in the upper right corner to download the zip file and then unzip it.

- **Compile the library using the cmd** &nbsp;&nbsp;`make`
- **Include Header Files:**
  
  In your C source file (.c), include the necessary header files from libft. This allows your code to access the function declarations.  
  For example, if you want to use ft_strlen, include libft.h at the beginning of your file: `#include libft`
  
- **Link the Library:**
  
  When compiling your program, you need to tell the compiler to include the libft library.  
  This is done using the -L flag (to specify the library directory) and -l flag (to specify the library name).  
  Assuming your libft.a is located in a directory named lib within your project directory, you would compile like this:
  
  `gcc -o <your_program> <your_program.c> -L./lib -lft`
  
  Here, <your_program> is the name of your executable, <your_program.c> is your source file, and -L./lib specifies the library directory as ./lib, while -lft specifies that it should link with libft.a.

- **Compile and Run:**
  
  Now, compile your program as usual. The compiler will use the functions from libft.a while building your program.
  When you run your program, it will have access to all the functions from libft.

**As of now the instruction only partain to creating the static library on MacOS. Use on linux or windows systems at your own risk ;)*

---

## The Library

Our Libft library is divided into three sections according to intructions in the subject file:

- Recreated/reimplemented Standard C Functions:  
  These functions replicate the behavior of their standard C library (libc) counterparts.
- Custom/extended and Alternative C Functions:  
  This section introduces functions that either enhance the standard C library's capabilities or provide different ways to achieve existing functionality.
- Linked List and Struct Operations:  
  In this section, you'll discover functions and data structures designed for effective management of linked lists and structured data.

### Reimplemented Libc Functions
In this section, you will find a set of functions, that are recreations of their standard C library (libc) counterparts. These custom functions mirror the behavior of their libc counterparts, following the same prototypes and adhering to the specifications outlined in their respective man pages. The only difference is their naming, as they are prefixed with 'ft_' (42, a coy reference to the school system).

For example, strlen is replicated as ft_strlen.

|                                   *                                                |                                         *                              |                                            *                                  |                                       *                             |    
|-----------------------------------------------------------------------------------|-----------------------------------------------------------------------|------------------------------------------------------------------------------|------------------------------------------------------------------------|
| [ft_isalpha](https://github.com/arommers/libft/blob/master/src/ft_isalpha.c)| [ft_memset](https://github.com/arommers/libft/blob/master/src/ft_memset.c)|[ft_toupper](https://github.com/arommers/libft/blob/master/src/ft_toupper.c)|[ft_memcmp](https://github.com/arommers/libft/blob/master/src/ft_memcmp.c)|
| [ft_isdigit](https://github.com/arommers/libft/blob/master/src/ft_isdigit.c)| [ft_bzero](https://github.com/arommers/libft/blob/master/src/ft_bzero.c)|[ft_tolower](https://github.com/arommers/libft/blob/master/src/ft_tolower.c)|[ft_strnstr](https://github.com/arommers/libft/blob/master/src/ft_strnstr.c)|
| [ft_isalnum](https://github.com/arommers/libft/blob/master/src/ft_isalnum.c)| [ft_memcpy](https://github.com/arommers/libft/blob/master/src/ft_memcpy.c)|[ft_strchr](https://github.com/arommers/libft/blob/master/src/ft_strchr.c)|[ft_atoi](https://github.com/arommers/libft/blob/master/src/ft_atoi.c)|
| [ft_isascii](https://github.com/arommers/libft/blob/master/src/ft_isascii.c)| [ft_memmove](https://github.com/arommers/libft/blob/master/src/ft_memmove.c)|[ft_strrchr](https://github.com/arommers/libft/blob/master/src/ft_strrchr.c)|[ft_calloc](https://github.com/arommers/libft/blob/master/src/ft_calloc.c)|
| [ft_isprint](https://github.com/arommers/libft/blob/master/src/ft_isprint.c)| [ft_strlcpy](https://github.com/arommers/libft/blob/master/src/ft_strlcpy.c)|[ft_strncmp](https://github.com/arommers/libft/blob/master/src/ft_strncmp.c)|[ft_strdup](https://github.com/arommers/libft/blob/master/src/ft_strdup.c)|
| [ft_strlen](https://github.com/arommers/libft/blob/master/src/ft_strlen.c)| [ft_strlcat](https://github.com/arommers/libft/blob/master/src/ft_strlcat.c)|[ft_memchr](https://github.com/arommers/libft/blob/master/src/ft_memchr.c)

The process of re-implementing these functions served as an introductory exercise in C programming, encompassing fundamental concepts such as algorithmic logic, data structures, memory allocation, and pointer manipulation.  

---
### Custom Libc Functions*
In this second section, we created a set of functions that either expand upon the capabilities of the standard C library (libc) or offer alternative implementations of existing functionality. These functions may address specialized requirements not covered by the standard library, or they might present optimized approaches to common tasks. This exercise encourages a deeper exploration of C programming, reinforcing proficiency in algorithmic design, data structure utilization, memory management, and advanced pointer manipulation.

|                                        *                                             |                                *                                |
|--------------------------------------------------------------------------------------|-----------------------------------------------------------------|
|[ft_subst](https://github.com/arommers/libft/blob/master/src/ft_substr.c)|[ft_strjoin](https://github.com/arommers/libft/blob/master/src/ft_strjoin.c)|
|[ft_strtrim](https://github.com/arommers/libft/blob/master/src/ft_strtrim.c)|[ft_split](https://github.com/arommers/libft/blob/master/src/ft_split.c)|
|[ft_itoa](https://github.com/arommers/libft/blob/master/src/ft_itoa.c)|[ft_strmapi](https://github.com/arommers/libft/blob/master/src/ft_strmapi.c)|
|[ft_putchar_fd](https://github.com/arommers/libft/blob/master/src/ft_putchar_fd.c)|[ft_putstr_fd](https://github.com/arommers/libft/blob/master/src/ft_putstr_fd.c)|
|[ft_putendl_fd](https://github.com/arommers/libft/blob/master/src/ft_putendl_fd.c)|[ft_putnbr_fd](https://github.com/arommers/libft/blob/master/src/ft_putnbr_fd.c)|

**For the requirements of the implementation of each custom function, please take a look at the link to the included subject file below.*

---

### Linked List and Struct Functions
This section of the libft library encompasses a collection of functions and data structures tailored for efficient linked list handling and structured data organization. Included are essential operations for creating, manipulating, and traversing linked lists, as well as utility functions for managing custom data structures using structs.
|                                        *                                             |                                *                                |
|--------------------------------------------------------------------------------------|-----------------------------------------------------------------|
|[ft_lstnew](https://github.com/arommers/libft/blob/master/src/ft_lstnew.c)|[ft_lstadd_front](https://github.com/arommers/libft/blob/master/src/ft_lstadd_front.c)|
|[ft_lstsize](https://github.com/arommers/libft/blob/master/src/ft_lstsize.c)|[ft_lstlast](https://github.com/arommers/libft/blob/master/src/ft_lstlast.c)|
|[ft_lstadd_back](https://github.com/arommers/libft/blob/master/src/ft_lstadd_back.c)|[ft_lstdelone](https://github.com/arommers/libft/blob/master/src/ft_lstdelone.c)|
|[ft_lstclear](https://github.com/arommers/libft/blob/master/src/ft_lstclear.c)|[ft_lstiter](https://github.com/arommers/libft/blob/master/src/ft_lstiter.c)|
|[ft_lstmap](https://github.com/arommers/libft/blob/master/src/ft_lstmap.c)|

---

### Remarks

Creating the static library libft marked my very first steps in the world of coding. It was both fun and challenging, albeit with occasional inaccuracies and often, less-than-efficient code.

Admittedly, as I wrote most of these functions, my grasp of the involved concepts was, at best, rudimentary. Yet, revisiting them now provides a pleasant reminder of those initial struggles, and my constant ongoing growth and improvement.

This is precisely why I've chosen not to update functions that might, to a discerning eye, display certain glaring faults. They stand as valuable markers of my progress in this coding journey.

---

### Sources
- [Subject File](https://cdn.intra.42.fr/pdf/pdf/95631/en.subject.pdf)
