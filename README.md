# MatrixMultiplication
<p>Program for multiplying large matrices using the C++11 standard.</p>

#### To compile this program in the Linux terminal, use the following command:
`g++ -std=c++11 -pthread -O3 -o App App.cpp`
<ul>
   <li>-std=c++11 : Specifies the use of the C++11 standard, which introduces modern features and improvements over previous C++ standards.</li>
   <li>-pthread : Enables multi-threading, allowing the program to run more efficiently when working with large matrices.</li>
   <li>-O3 : This is the highest level of optimization in GCC, which enables all optimizations that do not involve a space-speed tradeoff. It aggressively optimizes the code to improve performance, making it 
    especially useful for computationally intensive tasks like multiplying large matrices.</li>
</ul>

In addition to the usual multiplication of two matrices, I perform multiplication of a regular matrix by a transposed matrix, because it can lead to performance improvements. When one matrix is transposed, data is accessed in a way that may improve cache efficiency, especially when dealing with large matrices. Accessing elements in a transposed matrix aligns with the memory layout better, reducing cache misses and speeding up the multiplication process. This technique is commonly used in optimizing matrix operations in high-performance computing.
