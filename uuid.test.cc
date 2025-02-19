#include "src/xcli.h"

int main() {
    char uuid[37] = {0};  // UUID buffer (36 characters + null terminator)
    generate_uuidv7(uuid);
    std::cout << "UUIDv7: " << uuid << std::endl;
    return 0;
}