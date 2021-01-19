#ifndef CRYPTOCIPHERFRACTALS_H_
#define CRYPTOCIPHERFRACTALS_H_

#include <climits>
#include <assert.h>
#include <math.h>

class CryptoFractalCipher
{
	// point C = (x, y) - the representation in the xOy system of point C
	double c_xCoordinatePoint, c_yCoordinatePoint;
	
	// point Z = (x,y) - the representation in the xOy system of point Z
	double z_xCoordinatePoint, z_yCoordinatePoint; //Zx,Zy;
	
	// get the sign of a double number
	inline double getSign(double number)
	{
		// in case that d is less than 0, return -1.0, making the number negative
		// contrary make the number positive
	    if (number<0) 
			return(-1.0);
	    else 
			return(1.0);
	};

	// Value 'yValue' will be projected over an integer matrix or grid.
	// We have choose this for achieving the scaling goal and performing tests.
	// The projection process is a matter of personal choice, any other idea or 
	// solution can be implemented by reader.
	inline unsigned int PerformProjectionFor_Y(double yValue)
    {   
		unsigned long q;
    	const double scale=(32768.0/2.0);
    	const double offset=(32768.0);
    	
		// do the projection as a positive integerproject to positive integer
    	q=(yValue*scale)+offset;  
		
		//getting the LSB (least significant bit)
    	q&=1; 		
    	return q;
    }

	// Value 'xValue' will be projected over an integer matrix or grid.
	// We have choose this for achieving the scaling goal and performing tests.
	// The projection process is a matter of personal choice, any other idea or 
	// solution can be implemented by reader.
	inline unsigned int PerformProjectionFor_X(double xValue)   
    {
		// used for storing the decomposition value
		double decompositionValue;
		
		// power value (exponent)
        int n;
		
		// with frexp() we will decompose the double point (xValue) as 
		// argument into a normalized fraction and an integral power
        decompositionValue = frexp (xValue , &n);
		
		// with ldexp() we will return the result of multiplying 'decompositionValue' 
		// (the significand) with 2 and raised to the power '51' (exponent)
        decompositionValue = ldexp(decompositionValue,51);
		
		// Test if the difference between 'decompositionValue' and 
		// floor(decompositionValue) is less than 0.5
		// if yes return '1', otherwise '0'.
		// With floor() we round 'decompositionValue', returning the largest 
		// integral value that is not greater than 'decompositionValue'
        return (((decompositionValue-floor(decompositionValue))<0.5)?1:0);
    }

	inline void identifyFirstRoot()
	{
	    /* Zn*Zn=Z(n+1)-c */
		z_xCoordinatePoint=z_xCoordinatePoint-c_xCoordinatePoint;
		z_yCoordinatePoint=z_yCoordinatePoint-c_yCoordinatePoint;

		// r represents the length of the vector from the origin to the point
		// r = |z| = sqrt(x*x+y*y)
		double r;
		
		// the new point z = (x,y)
		double z_xNewPointValue, z_yNewPointValue;		//NewZx, NewZy
		r=sqrt(z_xCoordinatePoint*z_xCoordinatePoint+z_yCoordinatePoint*z_yCoordinatePoint);		
		
		// the below code sequence represents the implementation of the algorithm presented in [17], from page 361 to 362.
		// case 1: z>0
		if (z_xCoordinatePoint>0)
		{
			z_xNewPointValue=sqrt(0.5*(z_xCoordinatePoint+r));
			z_yNewPointValue=z_yCoordinatePoint/(2*z_xNewPointValue);
		}
		
		// for cases when z<0 and z=0
		else
		{
			// case 2: z<0
			if (z_xCoordinatePoint<0)
			{
				z_yNewPointValue=getSign(z_yCoordinatePoint)*sqrt(0.5*(-z_xCoordinatePoint+r));
				z_xNewPointValue=z_yCoordinatePoint/(2*z_yNewPointValue);
			}
			
			//case 3: z=0
			else
			{
				z_xNewPointValue=sqrt(0.5*fabs(z_yCoordinatePoint));
				if (z_xNewPointValue>0) z_yNewPointValue=z_yCoordinatePoint/(2*z_xNewPointValue);
				else z_yNewPointValue=0;
			}
		};
		// end of the implementation 
		
		// the values for x and y coordinates
	    z_xCoordinatePoint=z_xNewPointValue;
		z_yCoordinatePoint=z_yNewPointValue;
	};

public:
	// gets the encrypted value
	unsigned int getEncryptedMessageA(unsigned int plainValue);
	unsigned int getDecryptedMessageB(unsigned int encryptedValue);	
	unsigned int getEncryptedMessageC(unsigned int stream);			
	unsigned int getDecryptedMessageD(unsigned int stream); 		
	
	// gets the single bit
	unsigned int bitCodeEncryptedMessageA(unsigned int plainValue); 
	unsigned int bitCodeDecryptedMessageB(unsigned int encryptedValue);
	unsigned int bitCodeEncryptedMessageC(unsigned int stream);		
    unsigned int bitCodeDecryptedMessageD(unsigned int stream);

	// constructor
	CryptoFractalCipher(double cx,double cy);
	
	// destructor
	virtual ~CryptoFractalCipher();
};
#endif