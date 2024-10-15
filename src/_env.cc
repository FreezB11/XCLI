/* this made so that anything that has to read can be 
    implemneted here
    @author: HSAY
    @date:   OCT_15
*/
#include <iostream>
#include <fstream>
#include <string>

/*
    ofstream -> creates and writes
    ifstream -> read from file
    fstream  -> combination of ofstream and ifstream
*/


bool get_ip(const char* filename){
    std::fstream test;
    test.open(filename);
    std::string fc;
    std::getline(test,fc);
    std::cout << fc << std::endl;
    return true;    
}

#ifdef TESTRUN

int main(){
    get_ip(".env");
    return 0;
}


#endif