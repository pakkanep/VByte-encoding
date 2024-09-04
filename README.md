# VByte Encoding and Decoding

This program implements a generalized version of Variable Byte (VByte) encoding and decoding. It allows setting the size of the payload per block at runtime and supports encoding of sorted input by storing differences between consecutive numbers.

The project is still in progress and my intention is to optimize the code and add more features like:
  - The executable should read from the standard input, if no file is given.
  - Location-based random access for VByte encoded data.

## Features

- **Payload Size Control:** Supports the `-k <k>` command-line argument to set the block payload size to `k`. For example, `-k 7` would set the block size to 7 bits for the payload and 1 stop bit.
- **Sorted Input Optimization:** The `-s` command-line flag indicates that the input is sorted. When enabled, the program stores the differences between subsequent numbers instead of the numbers themselves, optimizing storage space.

## Input Format

The input is a binary stream consisting of 64-bit unsigned integers.

- The **first integer** in the input, `n`, indicates the number of additional integers in the stream.
- The following `n` integers are the data to be encoded.

## Output Format

- The program outputs the number of blocks used to encode the input to `stderr`.
- The program repeats the input sequence to `stdout`.

## Constraints

- The number of integers `n` is much less than \(10^8\).
- The payload size `k` must be less than 56.

## Example

**Input:**

- `k = 4`
- Binary input stream: `2, 7, 500` (in 64-bit binary format)

**Output:**

- Number of blocks used to encode: `4`
- Original input sequence: `7, 500`

## Usage

Compile the program and run it with the desired flags:

```bash
./vbyte_encoder -s -k 4 < input_file


