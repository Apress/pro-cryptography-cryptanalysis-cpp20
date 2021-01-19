#include <iostream>
#include "math.h"

using namespace std;

void encrypt(double message[100], double public_B[100][100], double error_vals[100], int dimension, double output_encrypted_text[100]);
void decrypt(int dimension, double encrypted_message[100], double private_basis[100][100], double unimodular_matrix[100][100], double output_message[100]);
double matrix_determinant(double square_matrix[100][100], int dimension);
void matrix_inverse(double matrix[100][100], int dimension, double output_inverse[100][100]);
void matrix_multiplication(double matrix1[100][100], double matrix2[100][100], double output[100][100], int dimension) ;
void matrix_addition(double matrix1[100][100], double matrix2[100][100], double output_sum[100][100], int dimension);
void get_cofactor(double matrix[100][100], double aux[100][100], int p, int q, int n); 
void adjoint_matrix(double matrix[100][100], double adjoint[100][100], int dimension);
bool inverse_matrix(double matrix[100][100], double inv_matrix[100][100], int dimension);
void vector_to_matrix(double v[100], int dimension, double output_matrix[100][100]);
void matrix_to_vector(double matrix[100][100], double output_v[100], int dimension);
void print_matrix(double matrix[100][100], int n, string message);
void print_vector(double vect[100], int n, string message);
void print_message(string message);

int main()
{  
    int message_length = 2;

    double b[100][100] = {{17.0, 0.0}, {0.0, 19.0}}; // the private basis -> b
    double b_inverse[100][100];
    
    inverse_matrix(b, b_inverse, message_length);    

    double A[100][100] = {{2.0, 3.0}, {3.0, 5.0}}; // the private unimodular matrix -> A
    double A_inverse[100][100];
    inverse_matrix(A, A_inverse, message_length);    

    double B[100][100]; // the public key -> B
    matrix_multiplication(A, b, B, message_length);    

    // Encryption
    double enc_message[100]; // stores the encryption of the message -> c
    double message[100] = {2, -5}; // the message -> m
    double error_vals[100] = {1, -1}; // the error values -> e

    print_vector(message, message_length, "message");
    encrypt(message, B, error_vals, message_length, enc_message);
    print_vector(enc_message, message_length, "encrypted message");

    // Decryption
    double recovered_message[100];
    decrypt(message_length, enc_message, b, A, recovered_message);
    print_vector(recovered_message, message_length, "recovered message");    
}

// Auxiliary function that prints a matrix on the console
void print_matrix(double matrix[100][100], int n, string message)
{
    cout<<endl<<"***"<<message<<"***"<<endl;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++ )
            cout<<matrix[i][j]<<"    ";
        
        cout<<endl;
    }

    cout<<endl;
}

// Auxiliary function that prints a vector on the console
void print_vector(double vect[100], int n, string message)
{
    cout<<endl<<"***"<<message<<"***"<<endl;

    for(int i = 0; i < n; i++)
    {
         cout<<vect[i]<<"    ";       
    }

    cout<<endl;
}

// Auxiliary function that prints a string message on the console
void print_message(string message)
{
    cout<<endl<<"***"<<message<<"***"<<endl;
}

void encrypt(double message[100], double public_B[100][100], double error_vals[100], int dimension, double output_encrypted_text[100])
{
    // c=m∙B+e
    double aux_message[100][100], aux_enc_message[100][100], aux_error_vals[100][100];
    vector_to_matrix(message, dimension, aux_message);

    // Compute m∙B -> aux_enc_message
    matrix_multiplication(aux_message, public_B, aux_enc_message, dimension);
    vector_to_matrix(error_vals, dimension, aux_error_vals);
    
    // Compute m∙B+e -> output_encrypted_text
    matrix_addition(aux_enc_message, aux_error_vals, aux_enc_message, dimension); 
    matrix_to_vector(aux_enc_message, output_encrypted_text, dimension);     
}

void decrypt(int dimension, double encrypted_message[100], double private_basis[100][100], double unimodular_matrix[100][100], double output_message[100])
{
    // (1) Compute c * (b^(-1))
    // (2) Remove e * (b^(-1))
    // (3) Compute m * A * (A^(-1))
    double aux_enc_message[100][100], aux_message[100][100];
    double recovered_message[100][100];

    // Compute the inverse of the basis -> b_inverse
    double b_inverse[100][100];    
    inverse_matrix(private_basis, b_inverse, dimension); 
    
    // Compute the inverse of the unimodular matrix -> A_inverse
    double A_inverse[100][100];
    inverse_matrix(unimodular_matrix, A_inverse, dimension); 
    
    // (1) Compute c * (b^(-1)) -> aux_enc_message
    vector_to_matrix(encrypted_message, dimension, aux_enc_message);
    matrix_multiplication(aux_enc_message, b_inverse, aux_message, dimension);
    
    // (2) Remove e * (b^(-1)) from aux_enc_message
    // Basically, the value aux_message[i][j] is rounded to the neareast integer
    for (int i=0; i<2; i++) 
    {
        for (int j=0; j<2; j++) 
            aux_message[i][j] = round(aux_message[i][j]);            
    }

    // (3) Compute m * A * (A^(-1))
    matrix_multiplication(aux_message, A_inverse, recovered_message, dimension);
    matrix_to_vector(recovered_message, output_message, dimension); 
}

// Computes the matrix multiplication between two matrices
void matrix_multiplication(double matrix1[100][100], double matrix2[100][100], double output[100][100], int dimension) 
{      
    for (int i = 0; i < dimension; i++) 
    { 
        for (int j = 0; j < dimension; j++) 
        { 
            output[i][j] = 0; 
            for (int k = 0; k < dimension; k++) 
                output[i][j] += matrix1[i][k] *  matrix2[k][j]; 
        } 
    } 
} 

// Computes the matrix sum between two matrices
void matrix_addition(double matrix1[100][100], double matrix2[100][100], double output_sum[100][100], int dimension)
{
    for(int i = 0; i < dimension; ++i)
        for(int j = 0; j < dimension; ++j)
            output_sum[i][j] = matrix1[i][j] + matrix2[i][j];
}

// Computes the cofactor of the element matrix[p][q]
void get_cofactor(double matrix[100][100], double aux[100][100], int p, int q, int n) 
{ 
    int i = 0, j = 0;   
     
    for (int row = 0; row < n; row++) 
    { 
        for (int col = 0; col < n; col++) 
        {            
            if (row != p && col != q) 
            { 
                aux[i][j++] = matrix[row][col]; 

                if (j == n - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
}

// computes the determinant of a square matrix
double matrix_determinant(double square_matrix[100][100], int dimension) 
{
   double matrix_det = 0.0;
   double aux_matrix[100][100];    

   if (dimension == 1)      
      return square_matrix[0][0];
   
   if (dimension == 2)      
      return ((square_matrix[0][0] * square_matrix[1][1]) - (square_matrix[1][0] * square_matrix[0][1]));
   else 
   {
      for (int k = 0; k < dimension; k++) {
         int aux_i = 0;
         for (int i = 1; i < dimension; i++) {
            int aux_j = 0;
            for (int j = 0; j < dimension; j++) {
               if (j == k)
               continue;
               aux_matrix[aux_i][aux_j] = square_matrix[i][j];
               aux_j++;
            }
            aux_i++;
         }
         matrix_det = matrix_det + (pow(-1.0, k) * square_matrix[0][k] * matrix_determinant( aux_matrix, dimension - 1 ));
      }
   }   
   return matrix_det; 
}

// Computes the adjoint of a matrix
void adjoint_matrix(double matrix[100][100], double adjoint[100][100], int dimension) 
{ 
    if (dimension == 1) 
    { 
        adjoint[0][0] = 1; 
        return; 
    }  
    
    int sign = 1;
    double aux[100][100]; 
  
    for (int i=0; i<dimension; i++) 
    { 
        for (int j=0; j<dimension; j++) 
        {            
            get_cofactor(matrix, aux, i, j, dimension);    
            sign = ((i + j) % 2 == 0) ? 1 : -1; 
            adjoint[j][i] = (sign)*(matrix_determinant(aux, dimension - 1)); 
        } 
    } 
} 

// Computes the inverse of a matrix
bool inverse_matrix(double matrix[100][100], double inv_matrix[100][100], int dimension) 
{     
    
    double det = matrix_determinant(matrix, dimension); 
    if (det == 0) 
    {         
        return false; 
    }     
    
    double adj[100][100]; 
    adjoint_matrix(matrix, adj, dimension);   
     
    for (int i=0; i<dimension; i++) 
        for (int j=0; j<dimension; j++)
        {
            if(adj[i][j] / det == -0)
                adj[i][j] = 0.0; 

            inv_matrix[i][j] = adj[i][j] / det; 
        }   
  
    return true; 
}

// This function "converts" a vector (seen as a matrix with 1 line and *dimension* columns) into a matrix
// The obtained matrix has on the first line the elements of the vector 
// The remaning lines (*dimension* - 1) contanis 0
// This "conversion" is useful in the operations with matrices (addition, multiplication)
void vector_to_matrix(double v[100], int dimension, double output_matrix[100][100])
{
    for(int i = 0; i < dimension; i++)
    {
        output_matrix[0][i] = v[i];
    }

    for(int i = 1; i < dimension; i++)
        for (int j = 0; j < dimension; j++)
        {
            output_matrix[i][j] = 0;
        }
}

// This function "converts" a matrix into a vector
// All lines of the matrix has values of 0, except for the first line
// The first line of the matrix becomes the vector 
void matrix_to_vector(double matrix[100][100], double output_v[100], int dimension)
{
    for(int i = 0; i < dimension; i++)
    {
        output_v[i] = matrix[0][i];
    }
}