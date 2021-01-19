#include <format>
#include <iostream>
 
//** let’s define a wrapper for class AESCryptography
template<class AESCryptography>
struct Encryption {
    AESCryptography value;
};
 
template<class AESCryptography, class CharAESCryptography>

struct 
std::formatter<Encryption<AESCryptography>,	      
	CharAESCryptography>: 
std::formatter<AESCryptography, CharAESCryptography> 
{    
    template<class FormatContext>
    auto format(Encryption<AESCryptography> 
		encAESCrypto, FormatContext& theFormatContext) 
    {
        return std::formatter<AESCryptography, 
		CharAESCryptography>::format
			(encAESCrypto.value, theFormatContext);
    }
};
 
int main() 
{
    Encryption<int> encrypted = { 32 };
    std::cout << std::format("{:#x}", encrypted);
}
