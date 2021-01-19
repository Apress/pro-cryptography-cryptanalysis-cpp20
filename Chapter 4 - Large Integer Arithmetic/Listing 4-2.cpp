void increment (int BigNo [])
{
	int	i;
	int N;
	int BASE;

	//* start indexing with least significant digit

	i = 0;
	while (i < N)
{

		//* increment the digit
		BigNo[i]++;

		//** if it overflows
		if (BigNo[i] == BASE)
{

			//** make it zero and move the index to next
			BigNo[i] = 0;
			i++;
		}
else
			//** else, we are done!
			break;
	}
}
