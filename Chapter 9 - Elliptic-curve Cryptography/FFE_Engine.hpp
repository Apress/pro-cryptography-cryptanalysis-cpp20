namespace EllipticCurveCryptography
{
        //** basic functions for 
		//** Finite Field Elements (FFE)
        namespace HelperFunctionFFE
        {            
            //** Computing Extended GCD gives g = a*u + b*v
            int ExtendedGreatestCommonDivisor(int a, int b, int& u, int &v)
            { 
                u = 1; 
                v = 0; 
                int g = a; 
                int u1 = 0;
                int v1 = 1; 
                int g1 = b; 
                while (g1 != 0) 
                { 
					//** division using integers
                    int q = g/g1;  
                    int t1 = u - q*u1; 
                    int t2 = v - q*v1; 
                    int t3 = g - q*g1; 
                    u = u1; v = v1; g = g1; 
                    u1 = t1; v1 = t2; g1 = t3; 
                } 
                
                return g;
            }
            
			//** providing solution and solving
			//** the linear congruence equation
			//** x * z == 1 (mod n) for z
            int InverseModular(int x, int n) 
            {              
				//** "%" represents the remainder 
				//** function, 0 <= x % n < |n|
                x = x % n;  
                int u,v,g,z;
                g = ExtendedGreatestCommonDivisor(x, n, u,v);
                if (g != 1) 
                {                     
					//** x and n has to be primes 
					//** in order to exist an x^-1 mod n
                    z = 0; 
                } 
                else 
                { 
                    z = u % n;
                } 
                return z;
            }
        }        
        
		//** represents the element from a Galois field
		//** we will use a specific behaviour for the 
		//** modular function in which (-n) mod m will
		//** return a negative number.
		//** The implementation is done in such way that 
		//** it will offer a support for the basic
		//** arithmetic operations, such as:
		//** + (addition), - (subtraction), / (division)
		//** and scalar multiplication.
		//** The P served as an argument represents the 
		//** order for the field.
        template<int P>
        class FFE
        {
            int i_;
            
            void assign(int i)
            {
                i_ = i;
                if ( i<0 )
                {                    
                    //** The correction behaviour is important.
					//** Using (-i) mod p we will make sure
					//** that the behaviour is the proper one.
                    i_ = (i%P) + 2*P;
                }

                i_ %= P;
            }
            
            public:
                //** the constructor
                FFE()
                 : i_(0)
                {}
				
                //** another constructor
                explicit FFE(int i)
                {
                    assign(i);
                }
				
                //** copying the constructor
                FFE(const FFE<P>& rhs) 
                 : i_(rhs.i_)               
                {
                }
                
                //** providing access to 
				//** the raw integer
                int i() const { return i_; }   
				
                //** implementation for negation operator
                FFE operator-() const
                {
                    return FFE(-i_);
                }                                
				
                //** assignation with an integer
                FFE& operator=(int i)
                {
                    assign(i);
                    return *this;
                }
				
                //** assignation from field element
                FFE<P>& operator=(const FFE<P>& rhs)
                {
                    i_ = rhs.i_;
                    return *this;
                }
				
                //** implementation of "*=" operator
                FFE<P>& operator*=(const FFE<P>& rhs)
                {
                    i_ = (i_*rhs.i_) % P;
                    return *this;           
                }
				
                //** implementation of "==" operator
                friend bool operator==(const FFE<P>& lhs, const FFE<P>& rhs)
                {
                    return (lhs.i_ == rhs.i_);
                }
				
                //** implementation of "==" operator
                friend bool operator==(const FFE<P>& lhs, int rhs)
                {
                    return (lhs.i_ == rhs);
                }
				
                //** implementation of "!=" operator
                friend bool operator!=(const FFE<P>& lhs, int rhs)
                {
                    return (lhs.i_ != rhs);
                }  
				
                // implementation of "a/b" operator
                friend FFE<P> operator/(const FFE<P>& lhs, const FFE<P>& rhs)
                {
                    return FFE<P>( lhs.i_ * HelperFunctionFFE::InverseModular(rhs.i_,P));
                }
				
				//** implementation of "a+b" operator
                friend FFE<P> operator+(const FFE<P>& lhs, const FFE<P>& rhs)
                {
                    return FFE<P>( lhs.i_ + rhs.i_);
                }
				
                //** implementation of "a-b" operator
                friend FFE<P> operator-(const FFE<P>& lhs, const FFE<P>& rhs)
                {
                    return FFE<P>(lhs.i_ - rhs.i_);
                }
				
                // implementation of "a + int" operator
                friend FFE<P> operator+(const FFE<P>& lhs, int i)
                {
                    return FFE<P>( lhs.i_+i);
                }
				
                //** implementation of "int + a" operator
                friend FFE<P> operator+(int i, const FFE<P>& rhs)
                {
                    return FFE<P>( rhs.i_+i);
                }
				
                //** implementation of "int * a" operator
                friend FFE<P> operator*(int n, const FFE<P>& rhs)
                {
                    return FFE<P>( n*rhs.i_);
                }    
				
                //** implementation of "a * b"
                friend FFE<P> operator*(const FFE<P>& lhs, const FFE<P>& rhs)
                {
                    return FFE<P>( lhs.i_ * rhs.i_);
                }
				
                //** the operator ostream for 
				//** showing and displaying in 
				//** readable format
                template<int T>
                friend ostream& operator<<(ostream& os, const FFE<T>& g)
                {
                    return os << g.i_;
                }
        };
}

    
