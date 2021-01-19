//** Leave everything as it is.
//** Don't change the order of the inputs or namespaces.

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

#include <math.h>
#include "FFE_Engine.hpp"

namespace EllipticCurveCryptography
{    
        //** Elliptic Curve over a finite field of order P:
        //** y^2 mod P = x^3 + ax + b mod P        
        template<int OrderFFE_EC> class EllipticCurve
        {
            public:
                // this curve is defined over the finite field (Galois field) Fp, this is the 
                // typedef of elements in it
                typedef FFE<OrderFFE_EC> ffe_element;		
                
                //** Any point on elliptic curve is formed 
			    //** from two elements that are within Fp 
                //** field (Galois Field). The points are 
				//** created once we declare an instance of 
				//** Elliptic Curve itself.                
                class EllipticCurvePoint
                {
                    friend class EllipticCurve<OrderFFE_EC>;
                    typedef FFE<OrderFFE_EC> ffe_element;
                    ffe_element xCoordValue_;	
                    ffe_element yCoordValue_;	
                    EllipticCurve *ellipticCurve_;
                    
                    // core of the doubling multiplier algorithm (see below)
                    // multiplies acc by m as a series of "2*accumulatorContainer's"
                    void DoublingMultiplierAlgorithm(int multiplier, EllipticCurvePoint& accumulatorContainer)
                    {        
                        if (multiplier > 0)
                        {       
                            EllipticCurvePoint doublingValue = accumulatorContainer; 
                            for (int counter=0; counter < multiplier; ++counter)
                            {
                                doublingValue += doublingValue;     // doubling step                          
                            }
                            accumulatorContainer = doublingValue;
                        }        
                    }
					
					//** Implementation of doubling multiplier algorithm.
					//** The process stands on multiplying 
					//** intermediateResultAccumulator for 
					//** storing the intermediate results with inputScalar. 
					//** This is done through expansion in multipliple 
					//** by 2 between the first of the binary represtantion of inputScalar.
                    EllipticCurvePoint MultiplyUsingScalar(int inputScalar, const EllipticCurvePoint& intermediateResultAccumulator)
                    {
                        EllipticCurvePoint accumulatorContainer = intermediateResultAccumulator;
                        EllipticCurvePoint outputResult = EllipticCurvePoint(0,0,*ellipticCurve_);
                        int i = 0, j = 0;
                        int iS = inputScalar;
                        
                        while(iS)
                        {
                            if (iS&1)
                            {
                                
								//** Setting up the bit.
								//** The computation is done by following the formula:
								//** accumulatorContainer = 2^(i-j)*accumulatorContainer
                                DoublingMultiplierAlgorithm(i-j,accumulatorContainer);
                                outputResult += accumulatorContainer;           
								
								//** last setting for the bit
                                j = i;
                            }
                            iS >>= 1;
                            ++i;
                        }
                        return outputResult;
                    }
					
                    //** the function deals with 
					//** adding two points on the curve		

					//** xCoord1, yCoord1, xCoord2=x2, yCoord2=y2
                    void ECTwoPointsAddition(ffe_element xCoord1, ffe_element yCoord1, ffe_element xCoord2, ffe_element yCoord2, ffe_element & xCoordR, ffe_element & yCoordR) const
                    {
                         //** dealing with sensitives cases 
						 //** for implying addition identity
                        if (xCoord1==0 && yCoord1==0) 
                        {
                            xCoordR = xCoord2;		
                            yCoordR = yCoord2;
                            return;
                        }
                        if (xCoord2==0 && yCoord2==0)
                        {
                            xCoordR = xCoord1;
                            yCoordR = yCoord1;
                            return;
                        }
                        if (yCoord1==-yCoord2) 
                        {
                            xCoordR = yCoordR = 0;
                            return;
                        }
                                                
                        //** deal with the additions
                        ffe_element s;                                                
                        if (xCoord1 == xCoord2 && yCoord1 == yCoord2)
                        {
                            //** computing 2*P                          
                            s = (3*(xCoord1.i()*xCoord1.i()) + ellipticCurve_->a()) / (2*yCoord1);
                            xCoordR = ((s*s) - 2*xCoord1);                            
                        }
                        else
                        {   
                            //** computing P+Q                            
                            s = (yCoord1 - yCoord2) / (xCoord1 - xCoord2);
                            xCoordR = ((s*s) - xCoord1 - xCoord2);
                        }
                        
                        if (s!=0)
                        {
                            yCoordR = (-yCoord1 + s*(xCoord1 - xCoordR));
                        }
                        else
                        {
                            xCoordR = yCoordR = 0;
                        }           
                    }
                    
                    EllipticCurvePoint(int xPoint, int yPoint)
                    : xCoordValue_(xPoint),
                      yCoordValue_(yPoint),
                      ellipticCurve_(0)
                    {}
                                  
                    EllipticCurvePoint(int xPoint, int yPoint, EllipticCurve<OrderFFE_EC> & EllipticCurve)
                     : xCoordValue_(xPoint),
                       yCoordValue_(yPoint),
                       ellipticCurve_(&EllipticCurve)
                    {}
                    
                    EllipticCurvePoint(const ffe_element& xPoint, const ffe_element& yPoint, EllipticCurve<OrderFFE_EC> & EllipticCurve)
                     : xCoordValue_(xPoint),
                       yCoordValue_(yPoint),
                       ellipticCurve_(&EllipticCurve)
                    {}
                    
                public:                    
                    static EllipticCurvePoint ONE;
                    
                    //** constructor
                    EllipticCurvePoint(const EllipticCurvePoint& rhsPoint)
                    {
                        xCoordValue_ = rhsPoint.xCoordValue_;
                        yCoordValue_ = rhsPoint.yCoordValue_;
                        ellipticCurve_ = rhsPoint.ellipticCurve_;
                    }
					
                    //** the assignment process
                    EllipticCurvePoint& operator=(const EllipticCurvePoint& rhsPoint)
                    {
                        xCoordValue_ = rhsPoint.xCoordValue_;
                        yCoordValue_ = rhsPoint.yCoordValue_;
                        ellipticCurve_ = rhsPoint.ellipticCurve_;
                        return *this;
                    }
					
                    //** access x component as element of Fp
                    ffe_element GetX() const { return xCoordValue_; }
					
                    //** access y component as element of Fp
                    ffe_element GetY() const { return yCoordValue_; }
					
                    //** calculate the order of this point by brute-force additions                    
                    unsigned int ComputingOrderBruteForceAddition(unsigned int maximum_period = ~0) const	//** order()
                    {
                        EllipticCurvePoint ecPoint = *this;
                        unsigned int order = 0;
                        while(ecPoint.xCoordValue_ != 0 && ecPoint.yCoordValue_ != 0)
                        {
                            ++order;
                            ecPoint += *this;
                            if (order > maximum_period) break;
                        }
                        return order;
                    }
					
                    //** negation operator (-) that gives the inverse of a point
                    EllipticCurvePoint operator-()
                    {
                        return EllipticCurvePoint(xCoordValue_,-yCoordValue_);
                    }    
					
                    //** equal (==) operator
                    friend bool operator==(const EllipticCurvePoint& lhsPoint, const EllipticCurvePoint& rhsPoint)
                    {
                        return (lhsPoint.ec_ == rhsPoint.ec_) && (lhsPoint.x_ == rhsPoint.x_) && (lhsPoint.y_ == rhsPoint.y_);
                    }
					
                    //** different (!=) operator
                    friend bool operator!=(const EllipticCurvePoint& lhsPoint, const EllipticCurvePoint& rhsPoint)
                    {
                        return (lhsPoint.ec_ != rhsPoint.ec_) || (lhsPoint.x_ != rhsPoint.x_) || (lhsPoint.y_ != rhsPoint.y_);
                    }    
					
                    //** Implementation of a + b operator
                    friend EllipticCurvePoint operator+(const EllipticCurvePoint& lhsPoint, const EllipticCurvePoint& rhsPoint)
                    {       
                        ffe_element xResult, yResult;
                        lhsPoint.ECTwoPointsAddition(lhsPoint.xCoordValue_,lhsPoint.yCoordValue_,rhsPoint.xCoordValue_,rhsPoint.yCoordValue_,xResult,yResult);
                        return EllipticCurvePoint(xResult,yResult,*lhsPoint.ellipticCurve_);    
                    }
					
                    //** multiplying with scalar * int
                    friend  EllipticCurvePoint operator*(int scalar, const EllipticCurvePoint& rhsPoint)
                    {
                        return EllipticCurvePoint(rhsPoint).operator*=(scalar);
                    }
					
                    //** Implementation of += operator
                    EllipticCurvePoint& operator+=(const EllipticCurvePoint& rhsPoint)
                    {   
                        ECTwoPointsAddition(xCoordValue_,yCoordValue_,rhsPoint.xCoordValue_,rhsPoint.yCoordValue_,xCoordValue_,yCoordValue_);
                        return *this;  
                    }
					
                    //** Implementation of *= int operator
                    EllipticCurvePoint& operator*=(int scalar)
                    {
                        return (*this = MultiplyUsingScalar(scalar,*this));
                    }   
					
                    //** display and print the point using ostream
                    friend ostream& operator <<(ostream& os, const EllipticCurvePoint& p)
                    {
                        return (os << "(" << p.xCoordValue_ << ", " << p.yCoordValue_ << ")");
                    }
                };
                
                
                //** performing the elliptic curve implementation
                typedef EllipticCurve<OrderFFE_EC> this_t;
                typedef class EllipticCurve<OrderFFE_EC>::EllipticCurvePoint point_t;                
                
                //** the Weierstrass equation as y^2 = x^3 + ax + b
                EllipticCurve(int CoefA, int CoefB)
                : ECParameterA(CoefA),
                  ECParameterB(CoefB),
                  tableOfPoints(),
                  tableFilledComputated(false)
                {                    
                }
				
				//** compute all the points (from the group of elements) for 
				//** Weierstrass equation. Note the fact that if we are 
				//** having a high order for the curve, the computation process
				//** will take some time
                void CalculatePoints()
                {
                    int x_val[OrderFFE_EC];
                    int y_val[OrderFFE_EC];
                    for (int counter = 0; counter < OrderFFE_EC; ++counter)
                    {
                        int nsq = counter*counter;
                        x_val[counter] = ((counter*nsq) + ECParameterA.i() * counter + ECParameterB.i()) % OrderFFE_EC;
                        y_val[counter] = nsq % OrderFFE_EC;                        
                    }
                    
                    for (int counter1 = 0; counter1 < OrderFFE_EC; ++counter1)
                    {
                        for (int counter2 = 0; counter2 < OrderFFE_EC; ++counter2)
                        {
                            if (x_val[counter1] == y_val[counter2])
                            {
                                tableOfPoints.push_back(EllipticCurvePoint(counter1,counter2,*this));
                            }
                        }
                    }
                    
                    tableFilledComputated = true;
                }				
                
				//** obtain the point (from the group of elements) for the curve
                EllipticCurvePoint operator[](int n)
                {
                    if ( !tableFilledComputated )
                    {
                        CalculatePoints();
                    }
                    
                    return tableOfPoints[n];
                }				
                
				//** the number og the elements in the group
                size_t Size() const { return tableOfPoints.size(); }				
                
				//** the degree of the point for the elliptic curve
                int Degree() const { return OrderFFE_EC; }
				
                //** the "a" parameter, as an element of Fp
                FFE<OrderFFE_EC> a() const { return ECParameterA; }
				
                //** the "b" paramter, as an element of Fp
                FFE<OrderFFE_EC> b() const { return ECParameterB; }
                
                //** print and show the elliptic curve in a readable format using ostream  human readable form
                template<int ECT>
                friend ostream& operator <<(ostream& os, const EllipticCurve<ECT>& EllipticCurve);     
				
                //** print and display all the elements of the elliptic curve group
                ostream&  PrintTable(ostream &os, int columns=4);
                
                private:
                    typedef std::vector<EllipticCurvePoint>  TableWithPoints;
                    
					//** table with the points
                    TableWithPoints tableOfPoints;   		 
                    
					//** first parameter of the elliptic curve equation
					FFE<OrderFFE_EC> ECParameterA;         	
                    
					//** second parameter of the elliptic curve equation
					FFE<OrderFFE_EC> ECParameterB;

					//** boolean value to show if the table has been computed
                    bool tableFilledComputated;          			
        };
        
        template<int ECT>
            typename EllipticCurve<ECT>::EllipticCurvePoint EllipticCurve<ECT>::EllipticCurvePoint::ONE(0,0);
                               
        template<int ECT>
        ostream& operator <<(ostream& os, const EllipticCurve<ECT>& EllipticCurve)
        {
            os << "y^2 mod " << ECT << " = (x^3" << showpos;
            if ( EllipticCurve.ECParameterA != 0 )
            {
                os << EllipticCurve.ECParameterA << "x";                
            }
            
            if ( EllipticCurve.ECParameterB.i() != 0 )
            {
                os << EllipticCurve.ECParameterB; 
            }
            
            os << noshowpos << ") mod " << ECT;
            return os;
        }
        
        template<int P>
        ostream& EllipticCurve<P>::PrintTable(ostream &os, int columns)
        {
            if (tableFilledComputated)
            {
                int col = 0;
                typename EllipticCurve<P>::TableWithPoints::iterator iter = tableOfPoints.begin();
                for ( ; iter!=tableOfPoints.end(); ++iter )
                {
                    os << "(" << (*iter).xCoordValue_.i() << ", " << (*iter).yCoordValue_.i() << ") ";
                    if ( ++col > columns )
                    {
                        os << "\n";
                        col = 0;
                    }
                }
            }
            else
            {
                os << "EllipticCurve, F_" << P;
            }
            return os;
        }                        
}

namespace utils
{    
    float   frand()
    {
        static float norm = 1.0f / (float)RAND_MAX;
        return (float)rand()*norm;
    }
    
    int irand(int min, int max)
    {
        return min+(int)(frand()*(float)(max-min));
    }
}

using namespace EllipticCurveCryptography;
using namespace utils;

int main(int argc, char *argv[])
{
    typedef EllipticCurve<163> elliptic_curve;
    elliptic_curve myEllipticCurve(1,1);
    
    cout << "Basic Example of using Elliptic Curve Cryptography using C++20. Apress, 2020\n\n";
    
	//** display some informations about the 
	//** elliptic curve and display some of the properties
    cout << "Equation of the elliptic curve: " << myEllipticCurve << "\n";
	
	//** compute the points for the elliptic 
	//** curve for equation from the above
    myEllipticCurve.CalculatePoints();
    
    cout << "\nList of the points (x,Y) for the curve (i.e. the group elements):\n";
    myEllipticCurve.PrintTable(cout,5);
    cout << "\n\n";
    
    elliptic_curve::EllipticCurvePoint P = myEllipticCurve[2];
    cout << "Randomly - Point P  = " << P << ", 2P = " << (P+P) << "\n";    
    
	elliptic_curve::EllipticCurvePoint Q = myEllipticCurve[3];
    cout << "Randomly - Point Q = " << Q << ", P+Q = " << (P+Q) << "\n"; 
    
	elliptic_curve::EllipticCurvePoint R = P;
    R += Q;
    cout << "P += Q = " << R << "\n";
    
	R = P;
    R += R;
    cout << "P += P = 2P = " << R << "\n";
    
    cout << "\nEncryption of the message using elliptic curve principles\n\n";
    
    //** as an example we will use Menes-Vanstone scheme that is
	//** based on elliptic curve for message encryption
    elliptic_curve::EllipticCurvePoint G = myEllipticCurve[0];
    while( (G.GetY() == 0 || G.GetX() == 0) || (G.ComputingOrderBruteForceAddition()<2) )
    {
        int n = (int)(frand()*myEllipticCurve.Size());
        G = myEllipticCurve[n];
    }
    
    cout << "G = " << G << ", order(G) is " << G.ComputingOrderBruteForceAddition() << "\n";
    
    //** Suppose that Alice wish to communicate with Bob
	//** Alice and its public key
    int a = irand(1,myEllipticCurve.Degree()-1);
	//** generating the public key
    elliptic_curve::EllipticCurvePoint Pa = a*G;  
    cout << "Alice - Public key (Pa) = " << a << "*" << G << " = " << Pa << endl;    
        
    //** Bob and is public key
    int b = irand(1,myEllipticCurve.Degree()-1);
	//** the public key
    elliptic_curve::EllipticCurvePoint Pb = b*G;       
    cout << "Bob - Public key (Pb) = " << b << "*" << G << " = " << Pb << endl;    
    
    //** Oscar - the eavesdropper and attacker
    int o = irand(1,myEllipticCurve.Degree()-1);;
    elliptic_curve::EllipticCurvePoint Po = o*G;
    cout << "Oscar - Public key (Po) = " << o << "*" << G << " = " << Po << endl;    

    cout << "\n\n";
    
    //** Alice proceed with the encryption
	//** for her message and send it to Bob.
	//** To achieve this, the first step is 
	//** to split the message into multiple
	//** parts which are encoded using Galois 
	//** field (Fp), which is also the domain 
	//** elliptic curve.	
    int m1 = 19;
    int m2 = 72;
    
    cout << "The clear text message send by Alice to Bob: (" << m1 << ", " << m2 << ")\n";
    
    //** proceed with encryption using the key of Bob
    elliptic_curve::EllipticCurvePoint Pk = a*Pb;
    elliptic_curve::ffe_element c1(m1*Pk.GetX());
    elliptic_curve::ffe_element c2(m2*Pk.GetY());
    
    //** the message that is encrypted is composed from:
	//** Pa - Alice public key
	//** c1,c2
    cout << "The message encrypted from Alice for Bob is represented as {Pa,c1,c2} and its content is = {" << Pa << ", " << c1 << ", " << c2 << "}\n\n";
    
    //** Bob compute the decryption for the message
	//** received from Alice, using her public key
	//** and the session value (integer b)
    Pk = b*Pa;
    elliptic_curve::ffe_element m1d  = c1/Pk.GetX();
    elliptic_curve::ffe_element m2d = c2/Pk.GetY();
    
    cout << "\tThe message decrypted by Bob from Alice is = (" << m1d << ", " << m2d << ")" << endl;
    
    //** Oscar will intercept the message and 
	//** and he/she will try to decrypt it 
	//** using his/her key
    Pk = o*Pa;
    m1d = c1/Pk.GetX();
    m2d = c2/Pk.GetY();

    cout << "\nOscar decrypt the message from Alice = (" << m1d << ", " << m2d << ")" << endl;
    
    cout << endl;
    
}
