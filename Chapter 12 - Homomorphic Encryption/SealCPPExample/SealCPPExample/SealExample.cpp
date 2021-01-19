#pragma once

#include "seal/seal.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <numeric>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace seal;

void seal_example_bfv()
{
    EncryptionParameters BFV_parameters(scheme_type::BFV);
    
    size_t polynomial_degree = 4096;
    BFV_parameters.set_poly_modulus_degree(polynomial_degree);
    BFV_parameters.set_coeff_modulus(CoeffModulus::BFVDefault(polynomial_degree));
    BFV_parameters.set_plain_modulus(1024);
    
    auto seal_context = SEALContext::Create(BFV_parameters);
        
    KeyGenerator keygen(seal_context);
    PublicKey encryption_key = keygen.public_key();
    SecretKey decryption_key = keygen.secret_key();    
    Encryptor bfv_encrypt(seal_context, encryption_key);
    Evaluator bfv_evaluate(seal_context);
    Decryptor bfv_decrypt(seal_context, decryption_key);

        
    int value_x = 3;
    Plaintext x_plaintext(to_string(value_x));
    cout << "The value x = " + to_string(value_x) + " is expressed as a plaintext polynomial 0x" + x_plaintext.to_string() + "." << endl;
   
    Ciphertext x_ciphertext;
    cout << "Encrypting x_plaintext to x_ciphertext..." << endl;
    bfv_encrypt.encrypt(x_plaintext, x_ciphertext);
    
    cout << "    - the size of the x_ciphertext (freshly encrypted) is : " << x_ciphertext.size() << endl;
    cout << "    - the noise budget for x_ciphertext is : " << bfv_decrypt.invariant_noise_budget(x_ciphertext) << " bits"
        << endl;

    Plaintext value_x_decrypted;
    cout << "    - decryption of x_encrypted: ";
    bfv_decrypt.decrypt(x_ciphertext, value_x_decrypted);
    cout << "0x" << value_x_decrypted.to_string() << endl;    
    
    cout << "Computing (x^2+2)..." << endl;
    Ciphertext square_x_plus_two;
    bfv_evaluate.square(x_ciphertext, square_x_plus_two);
    Plaintext plain_value_two("2");
    bfv_evaluate.add_plain_inplace(square_x_plus_two, plain_value_two);

    cout << "    - the size of the square_x_plus_two is: " << square_x_plus_two.size() << endl;
    cout << "    - the noise budget for square_x_plus_two is: " << bfv_decrypt.invariant_noise_budget(square_x_plus_two) << " bits"
        << endl;

    Plaintext decrypted_result;
    cout << "    - decryption of square_x_plus_two: ";
    bfv_decrypt.decrypt(square_x_plus_two, decrypted_result);
    cout << "0x" << decrypted_result.to_string() << endl;

    
    cout << "Computing (x+1)^2..." << endl;
    Ciphertext x_plus_one_square;
    Plaintext plain_value_one("1");
    bfv_evaluate.add_plain(x_ciphertext, plain_value_one, x_plus_one_square);
    bfv_evaluate.square_inplace(x_plus_one_square);
    cout << "    - the size of x_plus_one_square is: " << x_plus_one_square.size() << endl;
    cout << "    - the noise budget in x_plus_one_square is: " << bfv_decrypt.invariant_noise_budget(x_plus_one_square) << " bits"
        << endl;
    cout << "    - decryption of x_plus_one_square: ";
    bfv_decrypt.decrypt(x_plus_one_square, decrypted_result);
    cout << "0x" << decrypted_result.to_string() << endl;

    
    cout << "Compute [3(x^2+2)(x+1)^2]." << endl;
    Ciphertext enc_result;
    Plaintext plain_value_three("3");
    bfv_evaluate.multiply_plain_inplace(square_x_plus_two, plain_value_three);
    bfv_evaluate.multiply(square_x_plus_two, x_plus_one_square, enc_result);
    cout << "    - the size of encrypted_result: " << enc_result.size() << endl;
    cout << "    - the noise budget for encrypted_result: " << bfv_decrypt.invariant_noise_budget(enc_result) << " bits"
        << endl;
    cout << "NOTE: If the noise budget is zero, the decryption can be incorrect." << endl;
    cout << "    - decryption of enc_result: ";
    bfv_decrypt.decrypt(enc_result, decrypted_result);
    cout << "0x" << decrypted_result.to_string() << endl;    
}

int main()
{    
    seal_example_bfv();
    return 0;
}