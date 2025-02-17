#include <arpa/inet.h>
#include <cerrno>
#include <cstdint>
#include <iostream>
#include <vector>

int findPattern(const uint32_t numBytes, const uint8_t data[])
{
    if ((data == nullptr) || (sizeof(data) < sizeof(uint32_t)))
    {
        return -2;
    }

    const uint32_t PATTERN = 0xFE'6B'28'40;

    for (size_t arrIdx = 0; arrIdx < numBytes - sizeof(uint32_t); arrIdx++)
    {
        for (size_t bitIdx = 0; bitIdx < sizeof(uint32_t) * 8; bitIdx++)
        {
            uint32_t window = ((data[arrIdx] >> bitIdx) & (( 1 << (32 - bitIdx)) - 1)) | (data[arrIdx + 1] & ((1 << bitIdx) - 1)) << (32 - bitIdx);
            if (window == PATTERN)
            {
                return arrIdx * 32 + bitIdx;
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

        if (errno != 0 || (*endptr != '\n' && *endptr '\0') || x > UINT8_MAX)
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