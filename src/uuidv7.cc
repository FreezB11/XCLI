#include "xcli.h"
#include <random>
#include <chrono>
#include <cstdio>

UUID *gen_uuid(){

    char uuid[37];
    // generate the uuid
    using namespace std::chrono;

    // Get the current timestamp in milliseconds (48 bits)
    uint64_t timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    // Random generator
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(0, (1ULL << 62) - 1);

    uint64_t random_bits = dis(gen);

    // Construct the UUIDv7 components
    uint64_t time_high = (timestamp & 0xFFFFFFFFFFFF) << 16;  // First 48 bits for timestamp
    uint64_t version = 0x7000;  // Version 7 (0111)
    uint64_t variant = 0x8000000000000000;  // Variant (10xx)

    uint64_t uuid_high = time_high | version | ((random_bits >> 48) & 0x0FFF);  // 48-bit timestamp + 4-bit version + 12-bit random
    uint64_t uuid_low = (random_bits & 0x3FFFFFFFFFFFFFFF) | variant;  // 62-bit random + 2-bit variant

    // Format UUID into char array (8-4-4-4-12)
    std::snprintf(uuid, 37, "%08lx-%04lx-%04lx-%04lx-%012lx",
                  (uuid_high >> 32),
                  (uuid_high >> 16) & 0xFFFF,
                  uuid_high & 0xFFFF,
                  (uuid_low >> 48) & 0xFFFF,
                  uuid_low & 0xFFFFFFFFFFFF);


    return &uuid;
}