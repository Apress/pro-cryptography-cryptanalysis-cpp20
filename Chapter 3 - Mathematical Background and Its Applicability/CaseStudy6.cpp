#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
   const int processes = 15000;
   short int no_of_birthdays[365];
   int processesWithSuccess;
   bool IsSharedBirthday;

   //** we will time(NULL) as seed to be used for the 
   //** pseudo-random number generator srand()
   srand(time(NULL));

   for (int no_of_people = 2; no_of_people < 45; ++no_of_people) 
   {
      processesWithSuccess = 0;
      for (int i = 0; i < processes; ++i) 
	  {
		 //** all birthdays will be set to 0
         for (int j = 0; j < 365; no_of_birthdays[j++] = 0);
         IsSharedBirthday = false;
         for (int j = 0; j < no_of_people; ++j) 
		 {
            //** if our given birthday is shared (this means that is assigned for more than one person)
            //** this will be a shared birthday and we will need to stop verifying. 
            if (++no_of_birthdays[rand() % 365] > 1)
			{
               IsSharedBirthday = true;
               break;
            }
         }
         if (IsSharedBirthday) ++processesWithSuccess;
      }

      cout << "The probability for " << no_of_people << " people from the same room to share the same birthday is \t"
           << ( float(processesWithSuccess) / float(processes) ) << endl;
   }
   return 0;
}