#include "__base__.hpp"

#include "verification.hpp"

void check_array()
{
   array<int> a = {1,2,3};
   check(a[0] == 1);
   check(a[1] == 2);
   check(a[2] == 3);
   check(a.length() == 3);

   check(a.idx_valid((usize)(-1)) == false);
   check(a.idx_valid(0));
   check(a.idx_valid(1));
   check(a.idx_valid(2));
   check(a.idx_valid((usize)(3)) == false);


   array<int> b = {1,2,3};
   check(a==a);
   check(b==b);
   check(a==b);

   b[2] = 100;
   check(a != b);
   b.drop();
   check(b.length() == 0);

   a.resize(256);
   check(a.length() == 256);
   check(a[0] == 1);
   check(a[1] == 2);
   check(a[2] == 3);

   a[255] = 300;
   check(a[255] == 300);


   a.resize(1);
   check(a.length() == 1);
   check(a[0] == 1);

   a.drop();
   check(a.length() == 0);
}


void check_vector()
{
   vec<int> a = {5, 2, 3};
   check(a.length() == 3);
   check(a[0] == 5);
   check(a[1] == 2);
   check(a[2] == 3);
   a.sort();
   check(a[0] == 2);
   check(a[1] == 3);
   check(a[2] == 5);
   a.drop();

   usize nb_repetition = 256;

   int j = 0;
   repeat(i, nb_repetition)
   {
      check(nb_time == nb_repetition);
      check((int)i == j);
      j++;
   }

   j = nb_repetition;
   repeat_reverse(i, j)
   {
      check(nb_time == nb_repetition);
      j--;
      check((int)i == j);
   }


   vec<int> A = {5, 2, 3};
   vec<int> B = {5, 2, 3};
   check(A==A);
   check(B==B);
   check(A==B);
   A[1] = 42;
   check(A!=B);

   A.push(42);
   check(A.length()==4);
   check(A.peek()==42);

   check(B.pop()==3);
   check(B.length()==2);

   A.drop();
   B.drop();
   check(A.length() == 0);
   check(B.length() == 0);
}

void low_level_verification()
{
   printf_test_begin("array <T>");
   check_array();
   printf_test_end();

   printf_test_begin("vector<T>");
   check_vector();
   printf_test_end();
}
