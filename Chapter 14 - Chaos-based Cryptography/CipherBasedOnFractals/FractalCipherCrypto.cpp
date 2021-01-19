#include "FractalCipherCrypto.h"
#include <climits>
#include <assert.h>
#include <math.h>
#include <iostream>

using namespace std;

// implementing bitCodeEncryptedMessageA from FractalCipherCrypto.h file
unsigned int CryptoFractalCipher::bitCodeEncryptedMessageA(unsigned int bit_from_plaintext)
{
	// below we will create a cryptographic strem from the clear stream 
    int crypto_bit=0; 
    {
        identifyFirstRoot();

		// quadratic value
        unsigned long quadraticValue = PerformProjectionFor_X(z_yCoordinatePoint);        
		
		// Do the encoding process and provide the 
		// cryptographic stream from the clear stream
		// Variables used:
		//		- iV: the input value
		//		- oV: the output value
		//		- rV: the route value in the expansion of the fractal
        unsigned int iV, oV, rV;
        {   
			unsigned int result1, result2, result3;
            iV=(bit_from_plaintext) & 1;

			// obtained from the iteration of the quadratic value
            result1=quadraticValue;
			
			// input value
            result2=iV;
			
			// we will copy the bits if it is set in one operand but not both
            result3=result1^result2;
			
			// the final output value
            oV=result3;
            
			// the route value that need to be followed within the expansion of the fractal
			rV=result2;
        }
        crypto_bit=(oV);

        if ((rV) != 0)
        {   
			// use the route on the second root point
            z_xCoordinatePoint=-z_xCoordinatePoint;
            z_yCoordinatePoint=-z_yCoordinatePoint;
        }
    }
    return crypto_bit;
};

unsigned int CryptoFractalCipher::bitCodeDecryptedMessageB(unsigned int bit_from_encoding)
{
	// decode the clear value from the cryptographic stream
    int bit_from_plaintext=0;
    {
        identifyFirstRoot();
		
		// computing the quadratic value
        unsigned long quadraticValue = PerformProjectionFor_X(z_yCoordinatePoint);
        
		// decoding process for obtaining the clearstream from the cryptographic stream
		// Variables used:
		//		- iV: the input value
		//		- oV: the output value
		//		- rV: the route value in the expansion of the fractal 
        unsigned int iV, oV, rV;
        {   
			unsigned int result1,result2,result3;

            iV=(bit_from_encoding) & 1;
			
			// obtained from the iteration of the quadratic value
            result1=quadraticValue & 1;
			
			// input value
            result3=iV;
			
			// we will copy the bits if it is set in one operand but not both
            result2=result1^result3;
			
			// the output value
            oV=result2;
			
			// the route value that need to be followed within the expansion of the fractal
            rV=result2;
        }
        bit_from_plaintext=(oV);

        if ((rV) != 0)
        {   
			// use the route on the second root point
            z_xCoordinatePoint=-z_xCoordinatePoint;
            z_yCoordinatePoint=-z_yCoordinatePoint;
        }
    }
    return bit_from_plaintext;
};

unsigned int CryptoFractalCipher::bitCodeEncryptedMessageC(unsigned int bit_from_stream)
{	
	// generate the cryptographic stream from the clear stream
    int bit_from_coding=0;
    {
        identifyFirstRoot();

        unsigned long quadraticValueForY = PerformProjectionFor_X(z_yCoordinatePoint);
        unsigned long quadraticValueForX = PerformProjectionFor_X(z_xCoordinatePoint);

        // encoding process 
        unsigned int iV, oV, rV;

        {   unsigned int result1, result2, result3, result4;
            iV=(bit_from_stream);

			// from the iteration of the 'y' quadratic
            result1=quadraticValueForY;
			
			// from the iteration of the 'x' quadratic
            result2=quadraticValueForX;
			
			// we will copy the bits if it is set in one operand but not both
            result3=iV^result1; 
            result4=iV^result2;

			// the output value
            oV=result3;
            rV=result4; // branch in path to follow through IIM            
        }
        bit_from_coding=(oV);

        if ((rV) != 0)
        {   
			// use the route on the second root point
            z_xCoordinatePoint=-z_xCoordinatePoint;
            z_yCoordinatePoint=-z_yCoordinatePoint;
        }
    }
    return bit_from_coding;
};

unsigned int CryptoFractalCipher::bitCodeDecryptedMessageD(unsigned int bit_from_stream)
{	
	// generate the cryptographic stream from the clear stream
    int bit_from_coding = 0;
    {
        identifyFirstRoot();

        unsigned long quadraticValueForY = PerformProjectionFor_X(z_yCoordinatePoint);
        unsigned long quadraticValueForX = PerformProjectionFor_X(z_xCoordinatePoint);

        // encoding process
        unsigned int iV, oV, rV;
        {   
			unsigned int result1, result2, result3, result4;
            iV=(bit_from_stream) & 1;

			// from iterated quadratic y and x
            result1=quadraticValueForY;
            result2=quadraticValueForX;
			
			// we will copy the bits if it is set in one operand but not both
            result3=iV^result1;
            result4=result3^result2;
			
			// output value
            oV=result3;
			
			// the route value
            rV=result4;
        }
        bit_from_coding=(oV);

        if ((rV) != 0)
        {   //take branch to second root
            z_xCoordinatePoint=-z_xCoordinatePoint;
            z_yCoordinatePoint=-z_yCoordinatePoint;
        }
    }
    return bit_from_coding;
};

unsigned int CryptoFractalCipher::getEncryptedMessageA(unsigned int clearstream)
{
	// for creating the cryptographic stream from the clear stream
    int cryptographic_stream=0;

    for (int iterationIndex=0; iterationIndex<32; (iterationIndex++))
    {

        // encoding process for obtaining cryptographic stream from clear stream
        unsigned int iV,oV;
        iV=(clearstream>>iterationIndex) & 1;
        oV=bitCodeEncryptedMessageA(iV);
        cryptographic_stream+=((oV)<<iterationIndex);
    }
	
    return cryptographic_stream;
};

unsigned int CryptoFractalCipher::getDecryptedMessageB(unsigned int cryptstream)
{
	// for creating the clear stream from the cryptographic stream
    int clearstream=0;

    for (int iterationIndex=0; iterationIndex<32; (iterationIndex++))
    {
		// decoding process for obtaining the clear stream from the cryptographic stream        
        unsigned int iV, oV;

        iV=(cryptstream>>iterationIndex) & 1;
        oV=bitCodeDecryptedMessageB(iV);
        clearstream+=((oV)<<iterationIndex);
    }
    return clearstream;
};

unsigned int CryptoFractalCipher::getEncryptedMessageC(unsigned int stream)
{
	// construct the cryptographic stream from clear stream
	// cv - the code value
    int cV=0;

    for (int iterationIndex=0; iterationIndex<32; (iterationIndex++))
    {        
		// encoding process for generating the cryptographic stream from clear stream
        unsigned int iV,oV;
        iV=(stream>>iterationIndex) & 1;
        oV=bitCodeEncryptedMessageC(iV);
        cV+=((oV)<<iterationIndex);
    }
    return cV;
};

unsigned int CryptoFractalCipher::getDecryptedMessageD(unsigned int stream)
{
	// construct the cryptographic stream from clear stream
	// cv - the code value
    int cV=0;

    for (int iterationIndex=0; iterationIndex<32; (iterationIndex++))
    {
        // encoding process for generating the cryptographic stream from clear stream
        unsigned int iV, oV;
        iV=(stream>>iterationIndex) & 1;
        oV=bitCodeDecryptedMessageD(iV);
        cV+=((oV)<<iterationIndex);
    }
    return cV;
};

CryptoFractalCipher::CryptoFractalCipher(double cPoint_xValue,double cPoint_yValue)
{
    c_xCoordinatePoint=cPoint_xValue;
    c_yCoordinatePoint=cPoint_yValue;

    z_xCoordinatePoint=z_yCoordinatePoint=0;
    
	// use repeating digits as for encoding process using PI value with the goal to find a fixed point
    for(int index=0; index<32; index++)
		getEncryptedMessageA(3141592653);
}

// destructor implementation - only if it is necessary
CryptoFractalCipher::~CryptoFractalCipher()
{
}

int main(void)
{
	// CryptoKey_rValue and CryptoKey_iValue are represented as 
	// a point that is situated near the boundary of the Mandelbrot set 
	// the real value of a complex number (cryptographic key)
	double CryptoKey_rValue=-0.687;
	
	// the imaginary unit
	double CryptoKey_iValue=-0.312;	
	
	unsigned int Plaintext[50];
	unsigned int EncryptionA[50];
	unsigned int EncryptionB[50];
	unsigned int DecryptionOfAWithB[50];	
	unsigned int DecryptionOfBWithA[50];
	
	// generate randomly message
	for (int i=0;i<50;i++)
		Plaintext[i]=rand()%1000;
	
	// perform message encoding using getEncryptedMessageA for A 
	{
		CryptoFractalCipher CFC(CryptoKey_rValue, CryptoKey_iValue);
		for (int i=0;i<50;i++)
		   EncryptionA[i]=CFC.getEncryptedMessageA(Plaintext[i]);
	}
	
	// perform message encoding using getDecryptedMessageB for B
	{
		CryptoFractalCipher CFC(CryptoKey_rValue, CryptoKey_iValue);
		for (int i=0;i<50;i++)
		   EncryptionB[i]=CFC.getDecryptedMessageB(Plaintext[i]);
	}
	
	// perform message decoding A with B using getDecryptedMessageB for B
	{
		CryptoFractalCipher CFC(CryptoKey_rValue, CryptoKey_iValue);
		for (int i=0;i<50;i++)
		   DecryptionOfAWithB[i]=CFC.getDecryptedMessageB(EncryptionA[i]);
	}
	// perform message decoding B with A using getDecryptedMessageB for A
	{
		CryptoFractalCipher CFC(CryptoKey_rValue, CryptoKey_iValue);
		for (int i=0;i<50;i++)
		   DecryptionOfBWithA[i]=CFC.getEncryptedMessageA(EncryptionB[i]);
	}
	
	// display the output value and the results
	for (int i=0;i<50;i++)
	{
		 cout
		 <<i
		 <<")   (Plaintext Value="<<Plaintext[i]
		 <<")   (Encryption -> First Method (A) = "<<EncryptionA[i]
		 <<")   (Encryption -> Second Method (B) = "<<EncryptionB[i]
		 <<")   (Decryption -> A with B = "<<DecryptionOfAWithB[i]
		 <<")   (Decryption -> B with A = "<<DecryptionOfBWithA[i]
		 <<")"<<endl;
	};
}