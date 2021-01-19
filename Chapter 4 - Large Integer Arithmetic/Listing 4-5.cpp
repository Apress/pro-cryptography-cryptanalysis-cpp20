void multiplyUsingOneDigit (int BigOne1[], int BigOne2[], int number) {
	int	k, carryOverflow;
	int N;
	int BASE;

	//** there is nothing related to
	//** extra overflow to be added at this moment
	carryOverflow = 0;

	//** for each digit, starting with least significant...

	for (k=0; k<N; k++){
	//** multiply the digit by number,
	//** putting the result in BigOne2
		BigOne2[k] = number * BigOne1[k];

		//** adding extra any overflow that is taking
		//** place starting with the last digit
		BigOne2[k] += carryOverflow;

		//** product is too big to fit in a digit
		if (BigOne2[k] >= BASE) {
			//** handle the overflow
			carryOverflow = B[k] / BASE;
			BigOne2[k] %= BASE;
		}
else
			//** no overflow
			carryOverflow = 0;
	}
	if (carryOverflow)
		printf ("During the multiplication we experienced an overflow!\n");
}
