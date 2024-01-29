#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int flag;
int count_of_Process = 1;
bool safeState(vector<int> availableVector, const vector<int> requestVector, int m);
bool safeState(vector<int> availableVector, const vector<int> requestVector, int m)
{
   count_of_Process++;
   cout << "The Available Vector is..." << endl;
   cout << "   A B C D" << endl;
   cout << count_of_Process << ": ";
   for (int i = 0; i < m; ++i)
   {
      availableVector[i] = availableVector[i] - requestVector[i];
      cout << availableVector[i] << " ";
   }
   cout << endl;

   for (int i = 0; i < m; i++)
   {

      if (availableVector[i] >= 0)
         flag = 1;
      else
      {
         flag = 0;

         return flag;
      }
   }
   return flag;
}
vector<int> addprocess(vector<int> availableVector, const vector<int> maxVector, int m);

vector<int> addprocess(vector<int> availableVector, const vector<int> maxVector, int m)
{
   for (int i = 0; i < m; i++)
      availableVector[i] = availableVector[i] + maxVector[i];

   return availableVector;
}

int main()
{
   ifstream inputFile("matrix_input.txt");

   if (!inputFile.is_open())
   {
      cout << "Error opening file." << endl;
      return 1;
   }

   int n, m;
   inputFile >> n >> m;
   vector<vector<int>> allocation(n, vector<int>(m)); // 2D allocation vector
   vector<vector<int>> Max(n, vector<int>(m));        // 2D max matrix vector
   vector<vector<int>> Need(n, vector<int>(m));       // 2d need matrix vector
   vector<int> availableVector(m);
   vector<int> requestVector(m);
   vector<int> result(m);
   cout << "There are " << n << " processes in the system" << endl;
   cout << "There are " << m << " resource types" << endl;

   cout << "The Allocation Matrix is..." << endl;
   cout << "   A B C D" << endl;
   for (int i = 0; i < n; ++i)
   {
      cout << i << ": ";
      for (int j = 0; j < m; ++j)
      {
         inputFile >> allocation[i][j];
         cout << allocation[i][j] << " ";
      }
      cout << endl;
   }
   cout << "The Max Matrix is..." << endl;
   cout << "   A B C D" << endl;
   for (int i = 0; i < n; ++i)
   {
      cout << i << ": ";
      for (int j = 0; j < m; ++j)
      {
         inputFile >> Max[i][j];
         cout << Max[i][j] << " ";
      }
      cout << endl;
   }
   cout << "The Need Matrix is..." << endl;
   cout << "   A B C D" << endl;
   for (int i = 0; i < n; ++i)
   {
      cout << i << ": ";
      for (int j = 0; j < m; ++j)
      {
         Need[i][j] = Max[i][j] - allocation[i][j];
         cout << Need[i][j] << " ";
      }
      cout << endl;
   }

   cout << "The Available Vector is..." << endl;
   cout << "   A B C D" << endl;
   cout << count_of_Process << ": ";
   for (int i = 0; i < m; ++i)
   {
      inputFile >> availableVector[i];
      cout << availableVector[i] << " ";
   }
   cout << endl;

   cout << "The Request Vector is..." << endl;
   cout << "   A B C D" << endl;
   cout << count_of_Process << ": ";
   for (int i = 0; i < m; ++i)
   {
      inputFile >> requestVector[i];
      cout << requestVector[i] << " ";
   }
   cout << endl;

   safeState(availableVector, requestVector, m);
   if (flag)
      cout << "THE REQUEST CAN BE GRANTED!" << endl;
   else
      cout << "THE REQUEST CAN'T BE GRANTED!" << endl;

   for (int i = 0; i < m; i++)
   {
      availableVector = addprocess(availableVector, Max[i], m);
      safeState(availableVector, Need[i], m);

      if (flag)
         cout << "THE REQUEST CAN BE GRANTED!" << endl;

      else
      {
         cout << "THE REQUEST CAN'T BE GRANTED!" << endl;
         break;
      }
   }
   if (flag)
      cout << "THE SYSTEM IS IN A SAFE STATE!";
   else
      cout << "THE SYSTEM IS IN A VULNERABLE STATE!";

   return 0;
}
