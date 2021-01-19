#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

enum ColorTypes { 
	Blue, 
	NotBlue } ;

//** create a sequence container 
typedef std::vector<ColorTypes> backpack;

backpack initializeBackpack(unsigned blue_balls, unsigned differentBalls)
{
    backpack backpackOfBalls ;
    for (unsigned i=0; i<blue_balls; ++i)
        backpackOfBalls.emplace_back(Blue) ;

    for (unsigned i=0; i<differentBalls; ++i)
        backpackOfBalls.emplace_back(NotBlue);

    return backpackOfBalls ;
}

void randomize(backpack & backpackOfBalls)
{
	//** Mersenne Twister - pseudo-random generator 
	//** on 32-bit number using the state size of 19937 bits/
	//** std:random_device() will help us to generate a
	//** non-deterministic random numbers
    static std::mt19937 engine((std::random_device()()));
	
	//** we will rearrange the elements in the following range [first, second] as
	//** follows fist = backpackOfBalls.begin() and second = backpackOfBalls.end()
	//** using "engine" declared above as a uniform random number generator
    std::shuffle(backpackOfBalls.begin(), backpackOfBalls.end(), engine);
}


int main()
{
	//** constants initializations
    const unsigned theTotalOfSamples = 1000000;
    const unsigned blue_balls = 4;
    const unsigned differentBalls = 12;

    unsigned theFirstIsBlue = 0;
    unsigned bothAreBlue = 0;
    unsigned theSecondIsBlue = 0;

    auto backpackOfBalls = initializeBackpack(blue_balls, differentBalls) ;

    for (unsigned i=0; i<theTotalOfSamples; ++i)
    {
        randomize(backpackOfBalls);

        if (backpackOfBalls[0] == Blue)
            ++theFirstIsBlue;

        if (backpackOfBalls[1] == Blue)
            ++theSecondIsBlue;

        if (backpackOfBalls[0] == Blue && backpackOfBalls[1] == Blue)
            ++bothAreBlue;
    }

    float probabilityOfFirstBallToBeBlue = 
        static_cast<float>(theFirstIsBlue) / theTotalOfSamples;
		
    float probabilityForBothBallsToBeBlue = 
        static_cast<float>(bothAreBlue) / theTotalOfSamples;
		
    float probabilityForSecondBallToBeRed = 
        static_cast<float>(theSecondIsBlue) / theTotalOfSamples;

    std::cout << "Probability for the first ball to be blue: " 
              << probabilityOfFirstBallToBeBlue * 100.0 << "%\n" ;
			  
    std::cout << "Probability for the second ball to be blue: " 
              << probabilityForSecondBallToBeRed * 100.0 << "%\n" ;
			  
    std::cout << "Probability for both balls to be blue: " 
              << probabilityForBothBallsToBeBlue * 100.0 << "%\n" ;
}