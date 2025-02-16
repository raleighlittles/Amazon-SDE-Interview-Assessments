# Problem Statement

Write a function that takes a serialized set of orders in the defined format in memory and converts them to an OrderBatch data structure (defined later in the question).

# Background

The serialized input data will have the following format:

![order structure diagram](./order_conversions_diagram.svg)

(The gray element is the header field, set to 0xFACE 64206d)

Note: Payload Len is the number of bytes in the serialized input _excluding_ the first 10 bytes (i.e. 0xFACE and the Payload Len)

# Provided data types

```cpp
struct OrderBatch {
    uint32_t order_count; /* The number of valid orders pointed to by the 'orders' field */
    uint64_t batch_id;
    struct Order* orders;
}
```

```cpp
struct Order {
    uint16_t quantity;
    uint64_t order_id;
    uint8_t part_number[16];
    char email_address[32]; /* NULL terminated string */
}
```

```cpp
typedef enum
{
    STATUS_SUCCESS, /* Conversion performed successfully, 'out' updated */
    STATUS_INSUFFICIENT_OUTPUT_BUFFER, /* Unable to deserialize the input data due to the preallocated output buffer being too small */
    STATUS_NULL_INPUT /* 'serialized_data' or 'batch' is a null pointer */
} FuncStatus_t;
```

# Function signature

```cpp
FuncStatus_t deserialize_order(const size_t data_len, const uint8_t serialized_data[], const size_t max_order_count, struct OrderBatch* OrderBatch);
```

# Input parameters

| Parameter type | Parameter name    | Description                                                                                     |
|----------------|-------------------|-------------------------------------------------------------------------------------------------|
| `size_t`       | `data_len`        | The number of bytes in `serialized_data` to process during the deserialization                  |
| `uint8_t []`   | `serialized_data` | The data to deserialize into an OrderBatch data structure                                       |
| `size_t`       | `order_count`     | The maximum number of "Struct Order" entries that can be stored in the `batch` output parameter |


# Output parameter

| Parameter type       | Parameter name | Description                                                                                                                                                                                        |
|----------------------|----------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `struct OrderBatch*` | `batch`        | A pointer to a pre-allocated "OrderBatch" struct where the deserialized data from 'serialized_data' is put. There is "max_order_count" number of pre-allocated "struct Order" entities in "batch". |

# Return value
`FuncStatus_t` - the status of the deserialization effort. See enum description above.

# Example

## Input

```
data_len: 138
max_order_count: 2
serialized_data:
CE FA 80 00 00 00 00 00 00 00 02 00 00 00 05 00 00 00 00 00 00 00 0A 00 01 00 00
00 00 00 00 00 20 10 00 00 00 00 00 00 00 00 00 00 00 00 00 00 6A 6F 68 6E 40 65
78 61 6D 70 6C 65 2E 63 6F 6D 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 14
00 03 00 00 00 00 00 00 00 11 22 33 00 00 00 00 00 00 00 00 00 00 00 00 00 62 6F
62 40 65 78 61 6D 70 6C 65 2E 63 6F 6D 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00

```

## Outputs

```
OrderBatch batch = {
    .order_count = 2,
    .batch_id = 5,
    .orders = orders
};
Order orders[] = {
    {
        .quantity = 10,
        .order_id = 1,
        .part_number = {0x20, 0x10},
        .email_address = "john@example.com"
    },
    {
        .quantity = 20,
        .order_id = 3,
        .part_number = {0x11, 0x22, 0x33},
        .email_address = "bob@example.com"
    }
};
```

## Explanation

Your parser will read the initial 0xFACE bytes, followed by payload length which is 128 bytes long.
This is the number of bytes of serialized data excluding the 0xFACE (2 bytes) and the payload length (8 bytes).
The order_count and batch_id  have values 2 and 5. This is followed by bytes for Order 1 followed by Order 2.

