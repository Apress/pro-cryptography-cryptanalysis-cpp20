void addition(int BigNo1[], int BigNo2[], int BigNo3[])
{
	int	j, overflowCarry, sum;
	int carry, N, BASE;

	//** There is no need to carry yet
	carry = 0;

	//** move from the least to the most significant digit
	for (j=0; j<N; j++)
	{
		//** the digit from j'th position of BigNo3[]
		//** represents the sum of j'th digits of
		//** BigNo1[] and BigNo2[] plus the overvflow carry
		sum = BigNo1[j] + BigNo2[j] + overflowCarry;

		//** if the sum will go out of the base then
		//** we will find ourself in an overflow situation
		if (sum >= BASE)
		{
			carry = 1;

			//** adjust in such way that
//** the sum will fit within a digit
			sum -= BASE;
		}
		else
			//** otherwise no carryOverflow
			carry = 0;

		//** add the result in the same sum variable
		BigNo3[j] = sum;
	}

	//** if we are getting to the
	//** end we can expect an overflow
	if (carry)
		printf ("There is an overflow in the addition!\n");
}
