# ft_ls - @42Born2Code

My own implementation of the famous Unix command: ls, using the C programming language.

### Requirements
To be able to build and run this program you'll need a macbook, because I didn't make it portable for other systems. Sorry :(. As for software Requirements, you'll need:
- GNU make
- GCC

No specific versions, just update them to the latest version if you still can't build the program.

### Building the program

1. Download/Clone the source code
2. `cd` into the root directory
3. Run `make`

### Running the program

It's pretty simple, instead of calling `ls`, call `./ft_ls` from the root directory of the source code after building it.

#### Supported flags

- Long listing display: -l
- Display recursively: -R
- Display all files: -a
- Reverse sort: -r
- Sort by modification date: -t
- Display user ID and group ID: -n
- Suppress owner: -g
- Display one entry per line: -1
- Column display: -C (Set by default)
- Sort by creation date: -U
- Sort by last access date: -a
- Sort by last status change date: -c
- Show every entry except for current and previous directories: -A
- Sort by file size: -S
- Colorized output: -G (Only works in long listing display)

### Notes

- You can find the project instructions by [clicking here][1]
- The `master` branch has the original code, the `norme` branch has the normed version of it.
- No need to mention the odd spacing in files, I'm using a tab size of 4.
- It's not fast and there are a lot of memory leaks, I'll come back and fix those later.
- I know comments would have been super useful, this is kind of a big code base, but I'm trying to go fast in my school program, I'll make sure to add them later.
- There are probably better ways to implement it, but we are limited by a set of functions at my school (just to make it harder and give us a deeper understanding of what's happening in the back), please, review the [project instructions][1] before you explain how `X` or `Y` would have been a better way to do it ;)

## Sponsors

<a href="https://app.codesponsor.io/link/Fo4iMpT8bBWXwb54Lj7DPwqL/R4meau/ft_ls" rel="nofollow"><img src="https://app.codesponsor.io/embed/Fo4iMpT8bBWXwb54Lj7DPwqL/R4meau/ft_ls.svg" style="width: 888px; height: 68px;" alt="Sponsor" /></a>

Enjoy!

[1]: https://github.com/R4meau/ft_ls/blob/master/ft_ls.en.pdf
