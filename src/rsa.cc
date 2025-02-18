#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <iostream>
#include <fstream>

void GEN_RSA_KEY(const std::string& privKeyFile, const std::string pubKeyFile, int keysize = 2048){
    // Generate RSA key pair
    RSA* rsa = RSA_new();
    BIGNUM* bne = BN_new();
    if(!BN_set_word(bne, RSA_F4)){
        std::cerr << "Error while setting RSA_F4" << std::endl;
        return;
    }
    if(!RSA_generate_key_ex(rsa, keysize, bne, NULL)){
        std::cerr << "Error while generating RSA key" << std::endl;
        return;
    }
    // Save private key
    FILE* privFile = fopen(privKeyFile.c_str(), "wb");
    if(!privFile){
        std::cerr << "Error while opening private key file" << std::endl;
        return;
    }
    PEM_write_RSAPrivateKey(privFile, rsa, NULL, NULL, 0, NULL, NULL);
    fclose(privFile);

    // Save public key
    FILE* pubFile = fopen(pubKeyFile.c_str(), "wb");
    if(!pubFile){
        std::cerr << "Error while opening public key file" << std::endl;
        return;
    }
    PEM_write_RSAPublicKey(pubFile, rsa);
    fclose(pubFile);
    std::cout << "RSA key pair generated successfully" << std::endl;

    RSA_free(rsa);
    BN_free(bne);    
}