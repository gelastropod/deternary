# Documentation

### 1. Introduction

Welcome to Deternary! This is a ternary computing machine based on the Geometry Dash platformer level with the same name by X Future. Here, "ternary" means base-3, unlike the traditional "binary" you are probably familiar with, which means base-2.  
A "Trit" is a value which is either 0, 1, or 2, basically representing a singular base-3 digit. A "Trite" is a series of 3 Trits, represented here as 0, and all the lowercase alphabets (giving a total of 27 different values).

#### How the machine works
This machine has 6 different buffers, namely the **Accumulator**, **Instruction Pointer**, **Instruction Register**, **Address Register**, **Data Register**, and **Stack Pointer**, and each buffer stores 9 Trits (3 Trites). It also has **Input** and **Output** buffers, each storing 1 Trite. There is also the **Z** and **F** flags storing 1 Trit each. There is a **Memory** bank forming the entirety of the right side of your screen. Lastly, there is a **Testing System**. There is also a **Stack**. Here,

- The **Accumulator** contains the value which the machine will perform arithmetic operations on. There is a 9-Trit display, as well as a 3-Trite display to the right of it.
- The **Instruction Pointer** contains the index in which the machine is currently reading from the **Memory**. There is a cursor on the **Memory** pointing to wherever it indicates. Under most instructions (with a few exceptions) the **Instruction Pointer** is incremented by 1 after the instruction is completed. When the machine is not currently running, this can be freely modified.
- The **Instruction Register** contains the actual data which the **Instruction Pointer** is currently pointing to. The operation of specific instructions will be given in the next sub-section. When the machine is not currently running, this can be freely modified, and together with the **Instruction Pointer** allow creation and writing of programs into the **Memory**.
- The **Address Register** contains the pointer to the value in the **Memory** which the machine is currently reading or writing from.
- The **Data Register** contains the value in the **Memory** which the **Address Register** is currently pointing to.
- The **Stack Pointer** points to the top of the stack. It essentially serves as a display of the current size of the stack.
- The **Input** allows the user to freely input values to be read by the machine (which will pause whenever an *IN* instruction is reached, and not during test mode). During test mode, the **Input** cannot be modified and is instead automatically set by the **Testing System**.
- The **Output** displays the value previously outputted by the machine. During test mode, the **Testing System** compares this value with the true correct value to determine if the current test is passed.
- The **Z** flag is set to 0 if the **Accumulator** is 0, otherwise it will be set to 1.
- The **F** flag is set to 1 if an overflow occured, 2 is an underflow occured, and 0 otherwise.
- The **Memory** bank stores the data, as well as the program, in the same place. To the left of each cell is an index indicator, which is composed of 2 Trites, which means that the **Memory** has a total of 27 * 27 = 729 memory cells.
- The **Testing System** is how you progress in this game. Only in test mode, there is a test set number displayed which is composed of 3 Trites, and below that are 15 `.`s, that turn into `#`s if the current test is passed. Once all 15 tests in the test set have been passed, the entire test set is passed and the test set number is incremented by 1, moving on to the next test set. However, if the program gives a wrong answer for any of the 15 tests in a test set, the counter is immediately reset turning all `#`s into `.`s and resetting the current progress. This is to ensure the correctness of the program.
- The **Stack** stores up to 19683 values. It allows the value at the top to be pushed/poped.

All values are stored as 3 Trites, ranging from 0 to 19682. Note that these integers are unsigned, meaning no negative values exist. If a value goes above 19682 after an operation, an overflow is triggered (setting **F** to 1) and the value is rolled around back to 0. A similar thing occurs with values going below 0, triggering an underflow (and setting **F** to 2).

### 2. Instructions

The instructions are listed below (credits to the original document by X Future):
- Instruction 0 - *NONE*: Do nothing.
- Instruction 1 - *IN*: Read the value from the input device into the accumulator.
- Instruction 2 - *OUT*: Write the value in the accumulator to the output device.
- Instruction 3 - *LOAD*: Take the lower two trites as an address, load the value from that address in the memory to the accumulator.
- Instruction 4 - *SET*: Take the lower two trites as an address, set the value at that address to the accumulator value.
- Instruction 5 - *ADDN*: Add the lower two trites of the instruction to the accumulator. Those aren’t addresses this time. Just data.
- Instruction 6 - *SUBN*: Subtract the lower two trites from the accumulator.
- Instruction 7 - *MULTN*: Multiply the accumulator by the lower two trites.
- Instruction 8 - *DIVN*: Divide the accumulator by the lower two trites. **(round down to an integer)**
- Instruction 9 - *ULOAD*: Oh boy. Take the data that’s at the instruction address as a pointer to another location, then take **that location** as the one that it has to load the value from. Caught that? Basically, use the data at the address the instruction is pointing at *as the address to load data from*, not *as data, like in other commands.*
- Instruction 10 - *USET*: Instead of loading data from where that address was pointing at, put the accumulator value there.
- Instruction 11 - *ADD*: Add the value at the address to the accumulator.
- Instruction 12 - *SUB*: Subtract the value at the address from the accumulator.
- Instruction 13 - *MULT*: Multiply the accumulator by the value at the address.
- Instruction 14 - *DIV*: Divide the accumulator by the value at the address. **(round down to an integer)**
- Instruction 15 - *JUMP*: Instruction pointer will jump to this address.
- Instruction 16 - *JUMPZ*: JUMP, if the Z flag is 0.
- Instruction 17 - *JUMPNZ*: JUMP, if the Z flag is 1.
- Instruction 18 - *JUMPOF*: JUMP, if the F flag is 1 (so, overflow).
- Instruction 19 - *JUMPUF*: JUMP, if the F flag is 2 (so, underflow).
- Instruction 20 - *COMP*: Set the Z and F flags in the ALU as if you performed SUB with the same address, without changing the value in the accumulator.
- Instruction 21 - *PUSH*: Push the accumulator value into the stack. Adds 1 to the stack pointer. Will be ignored if the stack is full.
- Instruction 22 - *POP*: Retrieve the most recent value from the stack. Subtracts 1 from the stack pointer. Will be ignored if the stack is empty.
- Instruction 23 - *CALL*: Push the **current** address to the stack, then jump to the address in the instruction. (you can make procedures with this) Will also be ignored if the stack is full.
- Instruction 24 - *RETURN*: Pop a value from the stack, take it as an address and jump to the address after it. (so, kinda like returning from a procedure) You get the drill by now.
- Instruction 25 - *SWAP*: Swap the accumulator value with the top of the stack. You can use this to return values from procedures, like SWAP -> PUSH -> RET will put the address that the machine has to return to to the top of stack and put the value that needs to be returned below it, to be POP'ed later in the main code.
- Instruction 26 - *HALT*: Stop the machine.

### 3. Controls

Use the left and right arrows to move the cursor (indicated by the `^` or `>` symbols). Use the `a` and `d` keys to modify the value which the cursor is currently pointing to, and use the `w` key to toggle testing mode. Use the up arrow to toggle the running of the machine. Finally, use the `o` key to view the options screen. There, the `Process Speed` indicates the delay between the running of instructions of the machine, and `Run Helper` and `Start Index` allow the **Instruction Pointer** to be reset back to the `Start Index` once the *HALT* instruction is reached, and until either a wrong answer is given or the current test is completed.

# Tasks

### 1. Introductory

- #### Task 0: Cat
You are given an integer $X$. Output $X$.  
Constraints:
- $0\le X\le 19682$  

Input format:
```
$X$
```
Output format:
```
$X$
```