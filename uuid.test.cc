#include "src/xcli.h"

int main(){
    UUID *uuid = gen_uuid();
    std::cout << *uuid << std::endl;
    return 0;
}