#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> name;
vector<string> add;
vector<int> num;
vector<int> pin;
vector<int> balance;

void fetchData() {
  ifstream fln("name.txt");
  ifstream fla("add.txt");
  ifstream flnum("num.txt");
  ifstream flp("pin.txt");
  ifstream flb("balance.txt");

  if (!fln || !fla || !flnum || !flp || !flb) {
    cerr << "Error opening one or more files." << endl;
    return;
  }

  string line;
  while (getline(fln, line)) {
    name.push_back(line);
  }

  while (getline(fla, line)) {
    add.push_back(line);
  }

  while (getline(flnum, line)) {
    num.push_back(stoi(line));
  }

  while (getline(flp, line)) {
    pin.push_back(stoi(line));
  }

  while (getline(flb, line)) {
    balance.push_back(stoi(line));
  }

  fln.close();
  fla.close();
  flnum.close();
  flp.close();
  flb.close();
}

bool checkPin(int in) {
  int ypin;
  cout << "Enter pin : ";
  cin >> ypin;
  return ypin == pin[in];
}

void isRegAcc(int accNum, int &in) {
  for (int i = 0; i < num.size(); i++) {
    if (accNum == num[i])
      in = i;
  }
  if (in == -1) {
    cout << "Not a registered account...";
  }
}

void transac(int accNum, int amnt, int sw, int racc = 0, string sname = " ",
             string rname = " ") {
  ofstream fl(to_string(accNum) + ".txt", ios::app);
  switch (sw) {
  case 1:
    fl << "Amount " << amnt << " has been deposited" << endl;
    break;
  case 2:
    fl << "Amount " << amnt << " has been withdrawn" << endl;
    break;
  case 3:
    fl << "Transferred amount " << amnt << " to   " << rname << " (" << racc
       << ")" << endl;
    ofstream fl2;
    fl2.open(to_string(racc) + ".txt", ios::app);
    fl2 << "Received amount    " << amnt << " from " << sname << " (" << accNum
        << ")" << endl;
    fl2.close();
    break;
  }
  fl.close();
}

void updateBal(int lineNumber, const string &newContent) {
  ifstream inFile("balance.txt");
  if (!inFile) {
    cerr << "Unable to open file for reading.\n";
    return;
  }
  vector<string> lines;
  string line;
  while (getline(inFile, line)) {
    lines.push_back(line);
  }
  inFile.close();
  if (lineNumber < 1 || lineNumber > lines.size()) {
    cerr << "Invalid line number.\n";
    return;
  }
  lines[lineNumber - 1] = newContent;
  ofstream outFile("balance.txt");
  for(int i=0; i<lines.size(); i++) {
    outFile<<lines[i]<<endl;
  }
}

void checkAmnt(int &amnt) {
  while (amnt < 0) {
    cout << "Enter valid amount : ";
    cin >> amnt;
  }
}

void deposite() {
  int accNum, in = -1, amnt;
  cout << "\nEnter account number : ";
  cin >> accNum;
  isRegAcc(accNum, in);
  if (in == -1)
    return;
  cout << "Account holder : " << name[in] << endl;
  cout << "\nCurrent balance : " << balance[in];
  cout << "\nAmount to be deposite : ";
  cin >> amnt;
  checkAmnt(amnt);
  balance[in] += amnt;
  cout << "\nAmount added succesfully." << endl;
  cout << "Current balance : " << balance[in];
  transac(accNum, amnt, 1);
  updateBal(in + 1, to_string(balance[in]));
}

void withdraw() {
  int accNum, in = -1, amnt;
  cout << "\nEnter account number : ";
  cin >> accNum;
  isRegAcc(accNum, in);
  if (in == -1)
    return;
  cout << "\nAccount holder : " << name[in];
  cout << "\nCurrent balance : " << balance[in] << endl;
  cout << "Amount to withdraw : ";
  cin >> amnt;
  checkAmnt(amnt);
  while (amnt > balance[in]) {
    cout << "Insufficient balance...Re-enter amount : ";
    cin >> amnt;
    checkAmnt(amnt);
  }
  if (checkPin(in)) {
    balance[in] -= amnt;
    cout << "\nMoney withdrawl successfull..." << endl;
    cout << "Current balance : " << balance[in];
    transac(accNum, amnt, 2);
    updateBal(in + 1, to_string(balance[in]));
  } else {
    cout << "\nIncorrect pin. Try again later...";
  }
}

void prTransac(int accNum) {
  ifstream fl(to_string(accNum) + ".txt");
  string txt;
  while (getline(fl, txt)) {
    cout << endl << txt;
  }
  fl.close();
}

void checkAcc() {
  int accNum, in = -1;
  cout << "\nEnter account number : ";
  cin >> accNum;
  isRegAcc(accNum, in);
  if (in == -1)
    return;
  cout << "\nAccount holder : " << name[in] << endl;
  cout << "Address : " << add[in] << endl;
  cout << "Account number : " << num[in] << endl;
  cout << "Current balance : " << balance[in];
  int ch;
  cout << "\n\nPress 1 to see recent transaction or 0 to exit : ";
  cin >> ch;
  while (ch != 1 && ch != 0) {
    cout << "Not clear...Re-enter : ";
    cin >> ch;
  }
  if (ch == 1)
    prTransac(accNum);
}

bool preNumCheck(int gnum) {
  for (int i = 1; i < num.size(); i++) {
    if (gnum == num[i])
      return false;
  }
  return true;
}

void saveNewUser(string hname, string hadd, int gnum, int npin, int amnt) {
  ofstream fln("name.txt", ios::app);
  ofstream fla("add.txt", ios::app);
  ofstream flnum("num.txt", ios::app);
  ofstream flp("pin.txt", ios::app);
  ofstream flb("balance.txt", ios::app);

  if (!fln || !fla || !flnum || !flp || !flb) {
    cerr << "Error opening one or more files." << endl;
    return;
  }

  fln << hname << endl;
  fla << hadd << endl;
  flnum << gnum << endl;
  flp << npin << endl;
  flb << amnt << endl;

  fln.close();
  fla.close();
  flnum.close();
  flp.close();
  flb.close();
}

void openAcc() {
  string hname, hadd;
  int amnt, gnum, npin;
  cout << "Name : ";
  getline(cin, hname);
  cout << "Address : ";
  getline(cin, hadd);
  cout << "Enter amnt to deposite : ";
  cin >> amnt;
  checkAmnt(amnt);
  gnum = rand() % 900 + 100;
  while (!preNumCheck(gnum)) {
    gnum = rand() % 900 + 100;
  }
  cout << "\nYour account number : " << gnum << endl;
  cout << "Set pin : ";
  cin >> npin;
  name.push_back(hname);
  add.push_back(hadd);
  num.push_back(gnum);
  pin.push_back(npin);
  balance.push_back(amnt);
  saveNewUser(hname, hadd, gnum, npin, amnt);
  cout << "\nThank you to join us.\nYour account is successfully created.";
}

void sendMoney() {
  int sacc, racc;
  int amnt, sin = -1, rin = -1;
  cout << "\nYour account number : ";
  cin >> sacc;
  isRegAcc(sacc, sin);
  if (sin == -1)
    return;
  cout << "Reciver's account number : ";
  cin >> racc;
  isRegAcc(racc, rin);
  if (rin == -1)
    return;
  cout << "\nCurrent balance : " << balance[sin] << endl;
  cout << "Enter amount to send : ";
  cin >> amnt;
  checkAmnt(amnt);
  cout << endl;
  while (amnt > balance[sin]) {
    cout << "You don't have sufficient balance...\n";
    cout << "Enter amount again : ";
    cin >> amnt;
    checkAmnt(amnt);
    cout << endl;
  }
  if (checkPin(sin)) {
    balance[sin] -= amnt;
    balance[rin] += amnt;
    cout << "\nTransferred Rs." << amnt << " to " << name[rin] << "(" << racc
         << ")";
    transac(sacc, amnt, 3, racc, name[sin], name[rin]);
    updateBal(sin + 1, to_string(balance[sin]));
    updateBal(rin + 1, to_string(balance[rin]));
  } else {
    cout << "\nIncorrect pin. Try again later...";
  }
}

int main() {
  srand(time(0));
  fetchData();
  int ch;
  while (1) {
    cout << "1. Deposite money\n2. Withdraw money\n3. Check account\n4. Send "
            "money\n5. Open account\n0. Exit.\n\nEnter your choice "
            "(1/2/3/4/5/0) : ";
    cin >> ch;
    while (ch > 5 || ch < 0) {
      cout << "Not clear...Re-enter : ";
      cin >> ch;
    }
    cin.ignore();
    switch (ch) {
    case 1:
      deposite();
      break;
    case 2:
      withdraw();
      break;
    case 3:
      checkAcc();
      break;
    case 4:
      sendMoney();
      break;
    case 5:
      openAcc();
      break;
    case 0:
      cout << "\nThanks for using...";
      exit(0);
    }
    cin.ignore();
    cout << "\n\nPress ENTER to continue...";
    cin.get();
    (void)system("clear");
  }
}
