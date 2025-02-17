#include <arpa/inet.h>
#include <cerrno>
#include <cstdint>
#include <iostream>
#include <vector>

int findPattern(const uint32_t numBytes, const uint8_t data[])
{
    if (data == nullptr)
    {
        return -2;
    }

    const uint32_t PATTERN = 0xFE'6B'28'40;

    for (size_t arrIdx = 0; arrIdx < (sizeof(data) / sizeof(data[0])) - 3; arrIdx++)
    {
        for (size_t bitIdx = 0; bitIdx < 8; bitIdx++)
        {
            uint32_t window = (
                (data[arrIdx] >> bitIdx) |
                (data[arrIdx + 1] << (8 - bitIdx)) |
                (data[arrIdx + 2] << (16 - bitIdx)) |
                (data[arrIdx + 3] << (24 - bitIdx))
            ) & 0xFFFFFFFF;

            // Debug
            //std::cout << "[Elem #" << arrIdx << "]" << " [Bit #" << bitIdx << "] (Overall #" << (arrIdx * 8 + bitIdx) << ") Window: " << std::hex << window << std::dec << std::endl;

            if (ntohl(window) == PATTERN)
            {
                return arrIdx * 8 + bitIdx;
            }
        }
    }

    // Pattern not found
    return -1;

}


int main(void)
{
    std::vector<uint8_t> search_vec;

    size_t octets_read = 0;

    for (std::string cur_line; std::getline(std::cin, cur_line);)
    {
        errno = 0;
        char *endptr;
        long x = std::strtol(cur_line.c_str(), &endptr, 0);

        if (errno != 0 || (*endptr != '\n' && *endptr != '\0') || x > UINT8_MAX)
        {
            std::cerr << "Malformed test input!" << std::endl;
            return -1;
        }

        // Special case - break!
        if (x < 0)
        {
            octets_read = -x - 1;
            break;
        }
        
        search_vec.push_back(static_cast<uint8_t>(x));
        octets_read += 1;
    } // end for

    const uint8_t* search_ptr = (search_vec.size() == 0) ? nullptr: &search_vec[0];
    const int result = findPattern(static_cast<uint32_t>(octets_read), search_ptr);
    std::cout << result << std::endl;

} // end main()