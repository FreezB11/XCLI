#include <iostream>

//output its bits
// template <int T>
// class bits
// {
// private:
//     char bit;
// public:
//     bits(/* args */){

//     }
//     ~bits(){

//     }
// };
#include <bitset>

int main(){

    char inp = 'A';
    std::bitset<8> test = 'a'-65;
    std::cout << test << std::endl;
    char out = 0;
    for (int i = 0; i <= 7; ++i){
        
        // std::cout << ((inp >> i) & 1);
        out |= (((inp >> i) & 1) << i);
    }
    // std::cout << std::endl;
    // std::cout << out << std::endl;
    // std::cout << 'a' - 'A' << std::endl;
    
    return 0;
}