#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

int** a;
int** b;
int** c;
int** bt;
int num_threads;
int matrix_size ;

int** allocateMatrix() 
{
   int** matrix = new int*[matrix_size];
   for (int i = 0; i < matrix_size; ++i) 
   {
      matrix[i] = new int[matrix_size];
   }
   return matrix;
}

void deallocateMatrix(int** matrix) 
{
   for (int i = 0; i < matrix_size; ++i) 
   {
      delete[] matrix[i];
   }
   delete[] matrix;
}

void multiply(int tid,int num_threads)
{
   int lb = (matrix_size/num_threads)*tid;
   int ub = lb+(matrix_size/num_threads)-1;
   if (tid == num_threads-1)
      ub = matrix_size-1;
   for(int i = 0;i < matrix_size;++i)
   {
      for(int j = 0;j < matrix_size;++j)
      {
         for(int k = 0;k < matrix_size;++k)
         {
            c[i][j] += a[i][k] * b[k][j];
         }
      }
   }
}

void multiplyTransposed(int tid,int num_threads)
{
   int lb = (matrix_size/num_threads)*tid;
   int ub = lb+(matrix_size/num_threads)-1;
   if (tid == num_threads-1)
      ub = matrix_size-1;
   for(int i = lb;i <= ub;++i)
   {
      for(int j = 0;j < matrix_size;++j)
      {
         for(int k = 0;k < matrix_size;++k)
         {
            c[i][j] += a[i][k]*bt[j][k];
         }
      }
   }
}

int main() 
{
   cout << "Give number of threads (1,2,4...) : ";
   cin >> num_threads;
   cout << "Give N : ";
   cin >> matrix_size;
   a = allocateMatrix();
   b = allocateMatrix();
   c = allocateMatrix();
   bt = allocateMatrix();
   for(int i = 0;i < matrix_size;++i)
   {
      for(int j = 0;j < matrix_size;++j)
      {
         a[i][j] = rand() % 100;
         b[i][j] = rand() % 100;
         c[i][j] = 0;
      }
   }
   
   for(int i = 0;i < matrix_size;++i)
   {
      for(int j = 0;j < matrix_size;++j)
      {
         bt[i][j] = b[j][i];
      }
   }
   
   auto start = chrono::high_resolution_clock::now();
   thread threads_m[num_threads];
   for(int i = 0;i < num_threads;++i)
   {
      threads_m[i] = thread(multiply,i,num_threads);
   }
   for(int i = 0;i < num_threads;++i)
   {
      threads_m[i].join();
   }
   auto end = chrono::high_resolution_clock::now();
   chrono::duration<double, milli> parTime = end - start;
   cout << "Multiplication : " << parTime.count() << " ms" << std::endl;
   
   start = chrono::high_resolution_clock::now();
   thread threads_mt[num_threads];
   for(int i = 0;i < num_threads;++i)
   {
      threads_mt[i] = thread(multiplyTransposed,i,num_threads);
   }
   for(int i = 0;i < num_threads;++i)
   {
      threads_mt[i].join();
   }
   end = chrono::high_resolution_clock::now();
   parTime = end - start;
   cout << "Multiplication(Transposed) : " << parTime.count() << " ms" << std::endl;
   
   
   deallocateMatrix(a);
   deallocateMatrix(b);
   deallocateMatrix(c);
   deallocateMatrix(bt);
   
   return 0;
}