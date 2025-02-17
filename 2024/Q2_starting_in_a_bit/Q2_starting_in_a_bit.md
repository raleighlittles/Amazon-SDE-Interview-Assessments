# Problem statement

Given a byte array in network byte order, write an algorithm to find the starting **bit** position of the first occurrence of the 32-bit, big-endian pattern (0xFE6B2840) in the byte array.

The pattern may or may not be byte aligned in the output.

The function `htonl()` and `ntohl()` are provided in the C library to convert the endian order from host to network order, and from network to host order respectively:

```c
uint32_t htonl(uint32_t hostlong);
uint32_t ntohl(uint32_t netlong);
```

Note: network byte order is big-endian, host byte order is little-endian.

# Signature of function to implement

```cpp
int findPattern(const uint32_t numBytes, const uint8_t data[])
```

# Description of function parameters

| Parameter type | Parameter name | Description                                   |
|----------------|----------------|-----------------------------------------------|
| `uint32_t`     | `numBytes`     | The number of bytes in the array named `data` |
| `uint8_t[]`    | `data`         | The byte stream of data to search             |

## Return

`-1` if the given pattern (0xFE6B2840) is not found.
`-2` if the input data is null or if the size of `data` is insufficient to find the pattern (0xFE6B2840).

Otherwise, the pattern is found. Return the starting bit position of the pattern.

# Example 1 - Byte Aligned

Inputs:

* `numBytes` = 8
* `data`: `[0x00, 0x01, 0xFE, 0x6B, 0x28, 0x40, 0x02, 0x03]`

Return: "16". Each element in the array is 8 bits, and the pattern appears in the third element directly, which is at index 16 (8 + 8).

# Example 2 - Non-byte aligned

Inputs:

* `numBytes` = 8
* `data` = `[0x00, 0x03, 0xFC, 0xD6, 0x50, 0x80, 0x04, 0x06]`