# custom-cpu-assembler
This is and assembler for my custom assembly language.
It just generates the hex code that the emulator can understand from its assembly language.
Here we dont need to provide the program lenght since the assembler does that for us.
We can also add labels and comments for better readability.


# instruction format
The instructions are written in four parts each.

Instruction Input1 Input2 Output

Example:

add r1 5 r2

This would add 5 to r1 and store the result to r2.


# instruction set
The assembly language has the following instructions:

add, sub, or, nor, and, nand, xor, xnor, shr, biz, bnz, bic, bnc, brk


# registers
r0 - zero register (it always contains zero)

r1-r6 - general use registers

r7-r9 - address registers


# comments
Comments start with ';', everything after a ';' is ignored.

Examples:

; This is a comment


# getting specific bytes
To get the low byte of an number, definition or a label we put ".Low" at the end of it,
we can also put ".Mid" to get the middle byte, or ".High" to get the high byte.


# definitions
Definitions are line constant variables, they have a name and a value.
Every time the assembler comes across a definition name it replaces it with the definitions value.

Example:

#define a 10

This would replace every "a" in the code with an 10

Definitions can be any unsigned 24-bit intager and we can use ".Low", ".Mid" and ".High" with theur names to get their specific bytes.


# labels
Labels can be used instead of manually writing addresses.
They are defined by typing their name ending with a ":".

Example:

add 0 0 r1

loop:

; Setting the exit address

add exit.Low 0 r7

add exit.Mid 0 r8

add exit.High 0 r9

; Comparing r1 and 10

sub r1 10 r0

; Branching if they are the same

biz 0 0 r0

; Increment r1 by 1

add r1 1 r1

; Setting the loop address

add loop.Low 0 r7

add loop.Mid 0 r8

add loop.High 0 r9

; Branching

bnc 0 0 r0


exit:

; Halting the CPU

brk 0 0 r0


This code will loop while r1 != 10 and will increment r1 by 1 every time it loops, and when r1 reaches 10 it will halt the CPU.

# example program
Here is the same example program form the emulators README written it this assembly:

add 5 3 r1

add 243 0 r7

add 13 0 r8

add 0 0 r9

sub r1 2 ram

brk 0 0 r0
