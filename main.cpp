#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int rpt[4], currentIndex = 0, num[4], inp[4];

void gameRule() {
  cout << "Tutorial :" << endl;
  cout << "\nEvery single time you have to guess a number.\n" << endl;
  cout << "B means there is no such a digit in this number." << endl;
  cout << "Y means that this number has such a figure, but it is not in its "
          "place."
       << endl;
  cout << "G means that this number has such a figure, and it stands in its "
          "place.\n"
       << endl;
  cout << "Example: Target number is 4589     Your: 4589  GGGG" << endl;
  cout << "                                   Your: 9854  YYYY" << endl;
  cout << "                                   Your: 0237  BBBB" << endl;
  cout << "                                   Your: 9584  YYGG" << endl;
  cout << "                                   Your: 4895  YYYG" << endl;
  cout << "\nPress [ENTER] to continue.";
  cin.get();
}

bool isUnique(int n) {
  for (int i = 0; i <= currentIndex; i++)
    if (n == rpt[i])
      return false;
  return true;
}

void generateNumber() {
  num[0] = rand() % 10;
  rpt[currentIndex++] = num[0];
  for (int i = 1; i < 4; i++) {
    num[i] = rand() % 10;
    while (isUnique(num[i]) == 0)
      num[i] = rand() % 10;
    rpt[currentIndex++] = num[i];
  }
  currentIndex = 0;
  cout << endl;
}

void splitNumber(int num) {
  for (int i = 3; i >= 0; i--) {
    inp[i] = num % 10;
    num /= 10;
  }
}

bool check() {
  int gl = 0, yl = 0;
  for (int i = 0; i < 4; i++) {
    if (num[i] == inp[i])
      gl++;
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j)
        continue;
      else {
        if (num[i] == inp[j])
          yl++;
      }
    }
  }
  for (int i = 1; i <= 4 - (gl + yl); i++)
    cout << "B";
  for (int i = 1; i <= yl; i++)
    cout << "Y";
  for (int i = 1; i <= gl; i++)
    cout << "G";
  cout << endl;
  if (gl == 4)
    return true;
  return false;
}

int main() {
  srand(time(0));
  gameRule();
  while (true) {
    system("clear");
    generateNumber();
    int isCorrect = 0, userGuess;
    for (int i = 0; i < 4; i++)
      cout << num[i];
    cout << endl;
    while (isCorrect == 0) {
      cout << "Enter your guess : ";
      cin >> userGuess;
      splitNumber(userGuess);
      isCorrect = check();
    }
    cout << "\nCongrats you guessed the number.\n" << endl;
    char choice;
    cout << "Do you want to play again (Y/N) : ";
    cin >> choice;
    choice = tolower(choice);
    while (choice != 'n' && choice != 'y') {
      cout << "Not clear...Enter again(Y/N) : ";
      cin >> choice;
      choice = tolower(choice);
    }
    if (choice == 'n')
      break;
    else if (choice == 'y')
      continue;
  }
  system("clear");
  cout << "Thanks for playing." << endl;
  return 0;
}