void transformIntToBigInt(int BigNo[], int number)
{
	int	k;
	int bitSign;
	int BASE;

	//** start indexing with 0 position
	k = 0;

	//** if we still have something left
//** within the number, continue
	while (number) {
		//** insert the digit that is least significant
//** into BigNo[k] number
		BigNo[k++] = number % bitSign;

		//** we don't need the least significant bit
		number /= BASE;
	}

	//** complete the remain of the array with zeroes
	while (k < N)
		BigNo[k++] = 0;
}
