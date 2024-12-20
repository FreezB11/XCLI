#include <iostream>

//output its bits

int main(){

    char inp = 'A';
    char out = 0;
    for (int i = 0; i <= 7; ++i){
        
        std::cout << ((inp >> i) & 1);
        out |= (((inp >> i) & 1) << i);
    }
    std::cout << std::endl;
    std::cout << out << std::endl;
    
    
    return 0;
}