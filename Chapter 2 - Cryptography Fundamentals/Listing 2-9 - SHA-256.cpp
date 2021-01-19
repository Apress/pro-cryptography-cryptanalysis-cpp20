//** Listing 2-9 - Source code for implementation of SHA256
#include <iostream>
#include <sstream>
#include <bitset>
#include <vector>
#include <iomanip>
#include <cstring>

using namespace std;
vector<unsigned long> binaryConversion(const string);
vector<unsigned long> addPadOf512Bits(const vector<unsigned long>);
vector<unsigned long> resizingTheBlock(vector<unsigned long>);
string computingTheHash(const vector<unsigned long>);

string displayAsHex(unsigned long);
void outputTheBlockState(vector<unsigned long>);
string displayAsBinary(unsigned long);
const bool displayBlockStateAddOne = 0;        
const bool displayDistanceFrom512Bit = 0;	  
const bool displayResultsOfPadding = false;	  
const bool displayWorkVariablesForT = 0;		  
const bool displayT1Computation = false;		  
const bool displayT2Computation = false;		  
const bool displayTheHashSegments = false;		  
const bool displayWt = false;	

//** definite in acord cu specificatiile NIST
#define ROTRIGHT(word,bits) (((word) >> (bits)) | ((word) << (32-(bits))))
#define SSIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SSIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))
#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

//** conform cu ultimele actualizari facute de catre NIST
//** BSIG0 este inlocuit cu EP0 si BSIG1 cu EP0 in implementarea noastra

#define BSIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define BSIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))

int main(int argc, char* argv[])
{
	string theMessage = "";
	bool testing = 0;

	switch (argc) {
	    case 1:
	        cout << "The is no input string found. The test will be run using random first three letters abc.\n";
			theMessage = "abc";
			testing = true;
	        break;
	    case 2:	        
	    	if (strlen(argv[1]) > 55)
	    	{
	    		cout << "The string provided is biger than 55 characters length. Enter a shorter string"
	    			 << " or message!\n";
	    		return 0;
	    	}
	        theMessage = argv[1];
	        break;
	    default:
	        cout << "There are too many items in the command line.";
	        exit(-1);
	        break;
	}
	

	vector<unsigned long> theBlocksArray;
	
	theBlocksArray = binaryConversion(theMessage);
	
	theBlocksArray = addPadOf512Bits(theBlocksArray);
	
	theBlocksArray = resizingTheBlock(theBlocksArray);
	
	string myHash = computingTheHash(theBlocksArray);

	if (testing)
	{
		const string theCorrectHashForABC = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";
		if (theCorrectHashForABC.compare(myHash) != 0) {
			cout << "\tThe test has failed!\n";
			return(1);
		}
		else {
			cout << "\tThe test has passed!\n";
			return(0);
		}
	}
	
	cout << myHash << endl;
	return 0;
}

vector<unsigned long> resizingTheBlock(vector<unsigned long> inputOf8BitAsciiValues)
{
	vector<unsigned long> outputOf32BitWordsCombinedAsAsciiValues(16);

	for(int i = 0; i < 64; i = i + 4)
	{
		bitset<32> temporary32BitSection(0);
		
		temporary32BitSection = (unsigned long) inputOf8BitAsciiValues[i] << 24;
		temporary32BitSection |= (unsigned long) inputOf8BitAsciiValues[i + 1] << 16;
		temporary32BitSection |= (unsigned long) inputOf8BitAsciiValues[i + 2] << 8;
		temporary32BitSection |= (unsigned long) inputOf8BitAsciiValues[i + 3];

		outputOf32BitWordsCombinedAsAsciiValues[i/4] = temporary32BitSection.to_ulong();
	}

	return outputOf32BitWordsCombinedAsAsciiValues;
}

void outputTheBlockState(vector<unsigned long> vectorOfCurrentBlocks)
{
	cout << "---- The current State of the Block ----\n"; 
	for (int i = 0; i < vectorOfCurrentBlocks.size(); i++)
	{
		cout << "block[" << i << "] binary: " << displayAsBinary(vectorOfCurrentBlocks[i])
			<< "     hex y: 0x" << displayAsHex(vectorOfCurrentBlocks[i]) << endl;
	}
}

string displayAsHex(unsigned long input32BitBlock)
{
	bitset<32> theBitSet(input32BitBlock);
	unsigned number = theBitSet.to_ulong();

	stringstream theStringStream;
	theStringStream << std::hex << std::setw(8) << std::setfill('0') << number;
	string temporary;
	theStringStream >> temporary;

	return temporary;
}

string displayAsBinary(unsigned long input32OrLessBitBlock)
{
	bitset<8> theBitSet(input32OrLessBitBlock);
	return theBitSet.to_string();
}

vector<unsigned long> binaryConversion(const string inputOfAnyLength)
{
	vector<unsigned long> vectorBlockHoldingAsciiCharacters;	

	for (int i = 0; i < inputOfAnyLength.size(); ++i)
	{
		bitset<8> bitSetOf8Bits(inputOfAnyLength.c_str()[i]);
		vectorBlockHoldingAsciiCharacters.push_back(bitSetOf8Bits.to_ulong());
	}

	return vectorBlockHoldingAsciiCharacters;
}

vector<unsigned long> addPadOf512Bits(vector<unsigned long> vectorBlockHoldingAsciiCharacters)
{
	int lengthOfMessageInBits = vectorBlockHoldingAsciiCharacters.size() * 8;
	
	int zeroesToAdd = 447 - lengthOfMessageInBits;

	if(displayBlockStateAddOne)
		outputTheBlockState(vectorBlockHoldingAsciiCharacters);

	unsigned long t1Block = 0x80;
	vectorBlockHoldingAsciiCharacters.push_back(t1Block);

	if(displayBlockStateAddOne)
		outputTheBlockState(vectorBlockHoldingAsciiCharacters);
		outputTheBlockState(vectorBlockHoldingAsciiCharacters);

	zeroesToAdd = zeroesToAdd - 7;

	if (displayDistanceFrom512Bit)
	{
		cout << "lengthOfMessageInBits = " << lengthOfMessageInBits << endl;
		cout << "zeroesToAdd = " << zeroesToAdd + 7 << endl; // Plus 7 so this follows the paper.
	}

	if (displayDistanceFrom512Bit)
		cout << "adding " << zeroesToAdd / 8 << " empty eight bit blocks!\n";

	for(int i = 0; i < zeroesToAdd / 8; i++)
		vectorBlockHoldingAsciiCharacters.push_back(0x00000000);

	bitset<64> theBig64BlobBit(lengthOfMessageInBits);			
	if (displayDistanceFrom512Bit)
		cout << "l in a 64 bit binary blob: \n\t" << theBig64BlobBit << endl;
	
	string big_64bit_string = theBig64BlobBit.to_string();
	
	bitset<8> temp_string_holder1(big_64bit_string.substr(0,8));
	vectorBlockHoldingAsciiCharacters.push_back(temp_string_holder1.to_ulong());

	for(int i = 8; i < 63; i=i+8)
	{
		bitset<8> temporaryStringHolder2(big_64bit_string.substr(i,8));
		vectorBlockHoldingAsciiCharacters.push_back(temporaryStringHolder2.to_ulong());
	}

	if (displayResultsOfPadding)
	{
		cout << "Current 512 bit pre-processed hash in binary: \n";
			for(int i = 0; i < vectorBlockHoldingAsciiCharacters.size(); i=i+4)
				cout << i << ": " << displayAsBinary(vectorBlockHoldingAsciiCharacters[i]) << "     " 
				     << i + 1 << ": " << displayAsBinary(vectorBlockHoldingAsciiCharacters[i+1]) << "     " 
				     << i + 2 << ": " << displayAsBinary(vectorBlockHoldingAsciiCharacters[i+2]) << "     " 
				     << i + 3 << ": " << displayAsBinary(vectorBlockHoldingAsciiCharacters[i+3]) << endl;

		cout << "Current 512 bit pre-processed hash in hex: \n";
		for(int i = 0; i < vectorBlockHoldingAsciiCharacters.size(); i=i+4)
			cout << i << ": " << "0x" + displayAsHex(vectorBlockHoldingAsciiCharacters[i]) << "     " 
			     << i + 1 << ": " << "0x" + displayAsHex(vectorBlockHoldingAsciiCharacters[i+1]) << "     " 
			     << i + 2 << ": " << "0x" + displayAsHex(vectorBlockHoldingAsciiCharacters[i+2]) << "     " 
			     << i + 3 << ": " << "0x" + displayAsHex(vectorBlockHoldingAsciiCharacters[i+3]) << endl;	
	}
	return vectorBlockHoldingAsciiCharacters;
}

string computingTheHash(const vector<unsigned long> blockOf512BitPaddedMessage)
{
	unsigned long constantOf32BitWords[64] = {
		0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,
		0x923f82a4,0xab1c5ed5,0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,
		0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,0xe49b69c1,0xefbe4786,
		0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
		0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,
		0x06ca6351,0x14292967,0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,
		0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,0xa2bfe8a1,0xa81a664b,
		0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
		0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,
		0x5b9cca4f,0x682e6ff3,0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,
		0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
	};

	unsigned long static InitialHashValueFor32Bit_0 = 0x6a09e667;
	unsigned long static InitialHashValueFor32Bit_1 = 0xbb67ae85;
	unsigned long static InitialHashValueFor32Bit_2 = 0x3c6ef372;
	unsigned long static InitialHashValueFor32Bit_3 = 0xa54ff53a;
	unsigned long static InitialHashValueFor32Bit_4 = 0x510e527f;
	unsigned long static InitialHashValueFor32Bit_5 = 0x9b05688c;
	unsigned long static InitialHashValueFor32Bit_6 = 0x1f83d9ab;
	unsigned long static InitialHashValueFor32Bit_7 = 0x5be0cd19;

	unsigned long Word[64];

	for(int t = 0; t <= 15; t++)
	{
		Word[t] = blockOf512BitPaddedMessage[t] & 0xFFFFFFFF;

		if (displayWt)
			cout << "Word[" << t << "]: 0x" << displayAsHex(Word[t]) << endl;
	}

	for(int t = 16; t <= 63; t++)
	{
		Word[t] = SSIG1(Word[t-2]) + Word[t-7] + SSIG0(Word[t-15]) + Word[t-16];

		Word[t] = Word[t] & 0xFFFFFFFF;

		if (displayWt)
			cout << "Word[" << t << "]: " << Word[t];
	}

	unsigned long temporary_1;
	unsigned long temporary_2;
	unsigned long a = InitialHashValueFor32Bit_0;
	unsigned long b = InitialHashValueFor32Bit_1;
	unsigned long c = InitialHashValueFor32Bit_2;
	unsigned long d = InitialHashValueFor32Bit_3;
	unsigned long e = InitialHashValueFor32Bit_4;
	unsigned long f = InitialHashValueFor32Bit_5;
	unsigned long g = InitialHashValueFor32Bit_6;
	unsigned long h = InitialHashValueFor32Bit_7;

	if(displayWorkVariablesForT)
		cout << "         A        B        C        D        "
		     << "E        F        G        H        T1       T2\n";

	for( int t = 0; t < 64; t++)
	{
		temporary_1 = h + EP1(e) + CH(e,f,g) + constantOf32BitWords[t] + Word[t];
		if ((t == 20) & displayT1Computation)
		{
			cout << "h: 0x" << hex << h << "  dec:" << dec << h 
			     << "  sign:" << dec << (int)h << endl;
			cout << "EP1(e): 0x" << hex << EP1(e) << "  dec:" 
			     << dec << EP1(e) << "  sign:" << dec << (int)EP1(e) 
			     << endl;
			cout << "CH(e,f,g): 0x" << hex << CH(e,f,g) << "  dec:" 
			     << dec << CH(e,f,g) << "  sign:" << dec 
			     << (int)CH(e,f,g) << endl;
			cout << "constantOf32BitWords[t]: 0x" << hex << constantOf32BitWords[t] << "  dec:" << dec 
			     << constantOf32BitWords[t] << "  sign:" << dec << (int)constantOf32BitWords[t] << endl;
			cout << "Word[t]: 0x" << hex << Word[t] << "  dec:" << dec 
			     << Word[t] << "  sign:" << dec << (int)Word[t] << endl;
			cout << "temporary_1 = 0x" << hex << temporary_1 << "  dec:" << dec 
			     << temporary_1 << "  sign:" << dec << (int)temporary_1 << endl;
		}
		
		temporary_2 = EP0(a) + MAJ(a,b,c);

		if ((t == 20) & displayT2Computation)
		{
			cout << "a: 0x" << hex << a << "  dec:" << dec << a 
			     << "  sign:" << dec << (int)a << endl;
			cout << "b: 0x" << hex << b << "  dec:" << dec << b 
			     << "  sign:" << dec << (int)b << endl;
			cout << "c: 0x" << hex << c << "  dec:" << dec << c 
			     << "  sign:" << dec << (int)c << endl;
			cout << "EP0(a): 0x" << hex << EP0(a) << "  dec:" 
			     << dec << EP0(a) << "  sign:" << dec << (int)EP0(a) 
			     << endl;
			cout << "MAJ(a,b,c): 0x" << hex << MAJ(a,b,c) << "  dec:" 
			     << dec << MAJ(a,b,c) << "  sign:" << dec 
			     << (int)MAJ(a,b,c) << endl;
			cout << "temporary_2 = 0x" << hex << temporary_2 << "  dec:" << dec 
			     << temporary_2 << "  sign:" << dec << (int)temporary_2 << endl;
		}
		
		h = g;
		g = f;
		f = e;
		e = (d + temporary_1) & 0xFFFFFFFF; // Makes sure that we are still using 32 bits.
		d = c;
		c = b;
		b = a;
		a = (temporary_1 + temporary_2) & 0xFFFFFFFF; // Makes sure that we are still using 32 bits.

		if (displayWorkVariablesForT)
		{
			cout << "t= " << t << " ";
			cout << displayAsHex (a) << " " << displayAsHex (b) << " " 
			     << displayAsHex (c) << " " << displayAsHex (d) << " " 
			     << displayAsHex (e) << " " << displayAsHex (f) << " "
			     << displayAsHex (g) << " " << displayAsHex (h) << " " 
			     << endl;
		}
	}

	if(displayTheHashSegments)
	{
		cout << "InitialHashValueFor32Bit_0 = " << displayAsHex (InitialHashValueFor32Bit_0) << " + " << displayAsHex (a)
			 << " " << displayAsHex (InitialHashValueFor32Bit_0 + a) << endl;
		cout << "InitialHashValueFor32Bit_1 = " << displayAsHex (InitialHashValueFor32Bit_1) << " + " << displayAsHex (b)
			 << " " << displayAsHex (InitialHashValueFor32Bit_1 + b) << endl;
		cout << "InitialHashValueFor32Bit_2 = " << displayAsHex (InitialHashValueFor32Bit_2) << " + " << displayAsHex (c)
			 << " " << displayAsHex (InitialHashValueFor32Bit_2 + c) << endl;
		cout << "InitialHashValueFor32Bit_3 = " << displayAsHex (InitialHashValueFor32Bit_3) << " + " << displayAsHex (d)
			 << " " << displayAsHex (InitialHashValueFor32Bit_3 + d) << endl;
		cout << "InitialHashValueFor32Bit_4 = " << displayAsHex (InitialHashValueFor32Bit_4) << " + " << displayAsHex (e)
			 << " " << displayAsHex (InitialHashValueFor32Bit_4 + e) << endl;
		cout << "InitialHashValueFor32Bit_5 = " << displayAsHex (InitialHashValueFor32Bit_5) << " + " << displayAsHex (f)
			 << " " << displayAsHex (InitialHashValueFor32Bit_5 + f) << endl;
		cout << "InitialHashValueFor32Bit_6 = " << displayAsHex (InitialHashValueFor32Bit_6) << " + " << displayAsHex (g)
			 << " " << displayAsHex (InitialHashValueFor32Bit_6 + g) << endl;
		cout << "InitialHashValueFor32Bit_7 = " << displayAsHex (InitialHashValueFor32Bit_7) << " + " << displayAsHex (h)
			 << " " << displayAsHex (InitialHashValueFor32Bit_7 + h) << endl;
	}

	InitialHashValueFor32Bit_0 = (InitialHashValueFor32Bit_0 + a) & 0xFFFFFFFF;
	InitialHashValueFor32Bit_1 = (InitialHashValueFor32Bit_1 + b) & 0xFFFFFFFF;
	InitialHashValueFor32Bit_2 = (InitialHashValueFor32Bit_2 + c) & 0xFFFFFFFF;
	InitialHashValueFor32Bit_3 = (InitialHashValueFor32Bit_3 + d) & 0xFFFFFFFF;
	InitialHashValueFor32Bit_4 = (InitialHashValueFor32Bit_4 + e) & 0xFFFFFFFF;
	InitialHashValueFor32Bit_5 = (InitialHashValueFor32Bit_5 + f) & 0xFFFFFFFF;
	InitialHashValueFor32Bit_6 = (InitialHashValueFor32Bit_6 + g) & 0xFFFFFFFF;
	InitialHashValueFor32Bit_7 = (InitialHashValueFor32Bit_7 + h) & 0xFFFFFFFF;

	return displayAsHex(InitialHashValueFor32Bit_0) + displayAsHex(InitialHashValueFor32Bit_1) + displayAsHex(InitialHashValueFor32Bit_2) +
		   displayAsHex(InitialHashValueFor32Bit_3) + displayAsHex(InitialHashValueFor32Bit_4) + displayAsHex(InitialHashValueFor32Bit_5) +
		   displayAsHex(InitialHashValueFor32Bit_6) + displayAsHex(InitialHashValueFor32Bit_7);
}