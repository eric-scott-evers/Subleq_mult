#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 1024 // Adjust as needed
#define INPUT_PORT 10
#define OUTPUT_PORT 12

int memory[MEMORY_SIZE];

int read_input(int port) {
if (port == INPUT_PORT) {
return getchar(); // Read from stdin
} else {
fprintf(stderr, "Error: Invalid input port %d\n", port);
return 0; // Or handle error appropriately
}
}

void write_output(int port, int value) {
if (port == OUTPUT_PORT) {
putchar(value); // Write to stdout
} else {
fprintf(stderr, "Error: Invalid output port %d\n", port);
}
}

void execute_msubleq_mult(int *M) {
int pc = 0; // Program counter
int a, b, c, d, val_a, val_d, result;
while (pc < MEMORY_SIZE) {
a = M[pc];
b = M[pc + 1];
c = M[pc + 2];
d = M[pc + 3];
// Load A
if (a < 0) {
val_a = read_input(abs(a));
} else {
val_a = M[a];
}
// Load D
if (d < 0) {

val_d = read_input(abs(d));

} else {

val_d = M[d];

}

// Calculation

result = val_d * val_a - (b < 0 ? 0 : M[b] * (c < 0 ? c : M[c]));

// Output or Memory Write

if (b < 0) {

write_output(abs(b), result & 0xFF); // Low byte

write_output(abs(b) + 1, (result >> 8) & 0xFF); // High byte

} else {

M[b] = result & 0xFF; // Low byte to memory

M[b + 1] = (result >> 8) & 0xFF; // High byte to memory

}

// Conditional Branch

if (result <= 0) {

pc = c;

} else {

pc += 4; // Move to next instruction

}

}

}

int main() {

// Example MSubleq-Mult program (echo program)

int M[] = {

-10, -12, 0, 1, // Read, Write, Jump, D

0, 0, 0, 0, // Unused

0, 0, 0, 0, // Unused

0, 0, 0, 0, // Unused

0, 0, 0, 0, // Unused

0, 0, 0, 0, // Unused

0, 0, 0, 0, // Unused

0, 0, 0, 0, // Unused

};

// Copy the example program into memory

for (int i=0; i < sizeof(M)/sizeof(M[0]); i++){

memory[i] = M[i];

}

execute_msubleq_mult(memory);

return 0;

}

