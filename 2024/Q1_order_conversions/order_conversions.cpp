#include <cstdint>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <array>
#include <iostream>

typedef enum
{
    STATUS_SUCCESS,
    STATUS_INSUFFICIENT_OUTPUT_BUFFER,
    STATUS_NULL_INPUT
} FuncStatus_t;

struct OrderBatch
{
    uint32_t order_count;
    uint32_t batch_id;
    struct Order *orders;
};

struct Order
{
    uint16_t quantity;
    uint64_t order_id;
    uint8_t part_number[16];
    char email_address[32]; /* NULL terminated string */
};

/// BEGIN: HELPER FUNCTIONS

uint16_t arrToLe16_unsigned(const uint8_t arr[])
{
    return (arr[1] << 8) | (arr[0]);
}

uint32_t arrToLe32_unsigned(const uint8_t arr[])
{
    const uint32_t num = static_cast<uint32_t>(arr[3]) << 24 |
                         static_cast<uint32_t>(arr[2]) << 16 |
                         static_cast<uint32_t>(arr[1]) << 8 |
                         static_cast<uint32_t>(arr[0]);

    return num;
}

uint64_t arrToLe64_unsigned(const uint8_t arr[], unsigned int length = 8)
{
    uint64_t num = 0;
    for (unsigned int i = 0; i < length; i++)
    {
        num |= static_cast<uint64_t>(arr[i]) << (i * 8);
    }
    return num;
}

void setPartNum(const uint8_t arr[], uint8_t partNumberArrOut[])
{
    const uint8_t partNumberLenBytes = 16;

    for (size_t i = 0; i < partNumberLenBytes; i++)
    {
        partNumberArrOut[i] = arr[i];
    }
}

void setEmailAddr(const uint8_t arr[], char emailAddrOut[])
{
    const uint8_t emailAddrLenBytes = 32;

    for (size_t i = 0; i < emailAddrLenBytes; i++)
    {
        emailAddrOut[i] = arr[i];
    }
}

void decodeOrderField(const uint8_t arr[], struct Order *orderStructOut)
{
    const uint8_t orderQuantityBytes[] = {arr[0], arr[1]};
    const uint16_t orderQuantity = arrToLe16_unsigned(orderQuantityBytes);
    orderStructOut->quantity = orderQuantity;

    const uint64_t orderId = arrToLe64_unsigned(&arr[2]);
    orderStructOut->order_id = orderId;

    setPartNum(&arr[10], orderStructOut->part_number);
    setEmailAddr(&arr[26], orderStructOut->email_address);
}

FuncStatus_t deserialize_order(const size_t data_len, const uint8_t serialized_data[], const size_t max_order_count, struct OrderBatch *batch)
{
    if ((batch == nullptr) || (serialized_data == nullptr))
    {
        return FuncStatus_t::STATUS_NULL_INPUT;
    }

    batch->order_count = max_order_count;

    const unsigned int HEADER_BYTE_0 = 0xCE; // 206d
    const unsigned int HEADER_BYTE_1 = 0xFA; // 250d

    if ((serialized_data[0] != HEADER_BYTE_0) || (serialized_data[1] != HEADER_BYTE_1))
    {
        std::cout << "Error! Header bytes do not match" << std::endl;
        return FuncStatus_t::STATUS_NULL_INPUT;
    }

    // TODO: How do I check the condition for when to use the "STATUS_INSUFFICIENT_OUTPUT_BUFFER" ?

    const uint8_t orderCountBytes[] = {serialized_data[10], serialized_data[11], serialized_data[12], serialized_data[13]};
    const uint32_t orderCount = arrToLe32_unsigned(orderCountBytes);
    // batch->order_count = orderCount;

    const uint64_t batchId = arrToLe64_unsigned(&serialized_data[14], 8);
    // batch->batch_id = batchId;

    const uint8_t orderSizeBytes = 58;

    for (size_t orderIdx = 0; orderIdx < orderCount; orderIdx++)
    {
        // There's 22 bytes in between the beginning and where the order data actually starts:
        // 2 + 8 + 4 + 8
        // (header) + (payload len) + (order count) + (batch id)
        decodeOrderField(&serialized_data[22 + (orderIdx * orderSizeBytes)], &batch->orders[orderIdx]);
    }

    return FuncStatus_t::STATUS_SUCCESS;
}

// -------------------------------------------------------- Main function provided by testing utility. Do not modify below this line. --------------------------------------------------------

int main()
{
    char line[1024];
    int64_t data_len = 0;
    int64_t order_count = 0;
    uint8_t *data = NULL;
    struct OrderBatch order_batch = {0};
    FuncStatus_t ret_status = STATUS_SUCCESS;

    fgets(line, 1024, stdin);
    if (2 != sscanf(line, "%ld %ld", &data_len, &order_count))
    {
        printf("Error: Error occurred at line %d of test code.\n", __LINE__);
        return 1;
    }

    if (0 < data_len)
    {
        data = (uint8_t *)malloc(data_len * sizeof(uint8_t));
        if (NULL == data)
        {
            printf("Error: Error occurred at line %d of test code.\n", __LINE__);
            return 1;
        }
        for (int64_t i = 0; i < data_len; i++)
        {
            fgets(line, 1024, stdin);

            if (1 != sscanf(line, "%hhx", &data[i]))
            {
                printf("Error: Error occurred at line %d of test code.\n", __LINE__);
                return 1;
            }
        } // end for
        order_batch.orders = (struct Order *)malloc(order_count * sizeof(struct Order));
        memset(order_batch.orders, 0, order_count * sizeof(struct Order));
    } // end if

    if (-1 == data_len)
    {
        // Insufficient data buffer
        uint8_t data[138] = {0xCE, 0xFA, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x0A, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00, 0x6A, 0x6F, 0x68, 0x6E, 0x40, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65, 0x2E, 0x63, 0x6F, 0x6D, 0x00, 0x00, 0x00, 0x00,
                             0x00,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14,
                             0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22,
                             0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0x6F, 0x62, 0x40,
                             0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C,
                             0x65, 0x2E, 0x63, 0x6F, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00};

        order_batch.orders = (struct Order *)malloc(sizeof(struct Order));
        order_count = 1;
        ret_status = deserialize_order((size_t)138, data, order_count, &order_batch);
        free(order_batch.orders);
        order_batch.orders = NULL;
    }
    else if (-2 == data_len)
    {
        // serialized buffer null
        order_batch.orders = (struct Order *)malloc(sizeof(struct Order));
        order_count = 1;
        ret_status = deserialize_order((size_t)138, NULL, order_count, &order_batch);
        free(order_batch.orders);
        order_batch.orders = NULL;
    }
    else if (-3 == data_len)
    {
        // Insufficient Data Buffer
        uint8_t data[138] = {0xCE, 0xFA, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        order_count = 1;
        ret_status = deserialize_order((size_t)138, data, order_count, &order_batch);
    }
    else
    {
        ret_status = deserialize_order((size_t)data_len, data, order_count, &order_batch);
    }

    if (STATUS_SUCCESS == ret_status)
    {
        printf("%d\n%hu %lu\n", ret_status, order_batch.order_count, order_batch.batch_id);
    }
    else
    {
        printf("%d\n", ret_status);
    }

    if (NULL != data)
    {
        free(data);
    }

    if (NULL != order_batch.orders)
    {
        for (int64_t i = 0; i < order_count; i++)
        {
            struct Order *order = &order_batch.orders[i];
            printf("%hu %lu\n", order->quantity, order->order_id);

            for (uint8_t j = 0; j < 16; ++j)
            {
                printf("%x", order->part_number[j]);
            }
            printf("\n%.32s\n", order->email_address);
        } // end for

        free(order_batch.orders);
    }

    return 0;
}
