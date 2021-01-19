void multiply (int BigInt1[], int BigInt2[], int BigInt3[])
{
	int length_of_integer;
	int	x, y, P[length_of_integer];	

	//** C will store the sum of
	//** partial products.  It's initially 0.
	transformIntToBigInt(BigInt3, 0);

	//* for each digit in BigInt1
	for (x=0; x<length_of_integer; x++)
	{
		//** multiply BigInt2 by digit [x]
		multiplyOneDigit(BigInt2, P, BigInt1[x]);

		//** left shifting the partial product with i bytes
		leftShifting(P, x);

		//** add the output result to the current sum
		addResult(BigInt3, P, BigInt3);
	}
}
