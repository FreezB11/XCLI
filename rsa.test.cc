#include "src/rsa.h"

int main(){
    GEN_RSA_KEY("private.pem", "public.pem");
    return 0;
}