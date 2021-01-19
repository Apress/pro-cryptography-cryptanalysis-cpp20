void leftShifting (int BigInt1[], int number) {
	int i;
	int N;

	//** moving starting from left to right,
	//** we will move anything with left n spaces
	for (i=N-1; i>= number; i--)
		BigInt1[i] = BigInt1[i- number];

	//** complete the last n digits with zeros
	while (i >= 0) BigInt1[i--] = 0;
}
