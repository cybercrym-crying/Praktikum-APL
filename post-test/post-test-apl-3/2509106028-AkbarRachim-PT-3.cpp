#include "tabulate.hpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace tabulate;

struct User {
  string userName;
  string userPass;
  string userType;
  User() = default;
  User(string n, string p, string t) : userName(n), userPass(p), userType(t) {}
};

struct Date {
  string day;
  string month;
  string year;
  Date() = default;
  Date(string d, string m, string y) : day(d), month(m), year(y) {}
};

struct Survivor {
  string survivorName;
  string survivorGender;
  bool life = true;
  bool hungry = true;
  Date dateEntry;
  Survivor() = default;
  Survivor(string n, string g, string d, string m, string y)
      : survivorName(n), survivorGender(g), dateEntry(d, m, y) {}
};

int inputUser, survivorCount = 0, bunkerLimit = 50, foodStock = 30,
               feedingCount = 0, loginLimit = 0;
string pass, name, gender, day, month, year, typeUser;

void printLoginMenu();
void printBunkerMenu();
bool loginMenu(vector<User> &userList);
void registerMenu(vector<User> &userList);
void addSurvivor(vector<Survivor> &survivorList);
void addSurvivor(vector<Survivor> &survivorList, string n, string g, string d,
                 string m, string y);
void updateAndFeeding(vector<Survivor> &survivorList);
void readSurvivor(vector<Survivor> &survivorList);
void kickSurvivor(vector<Survivor> &survivorList);

int main() {
  bool inBunker = false;
  vector<User> userList;
  userList.push_back(User("Akbar Rachim", "028", "admin"));
  userList.push_back(User("Akbar", "001", "user"));
  vector<Survivor> survivorList;
  addSurvivor(survivorList, "Budi", "Male", "01", "01", "2000");
  addSurvivor(survivorList, "Radi", "Male", "01", "01", "2000");
  addSurvivor(survivorList, "Gea", "Female", "01", "01", "2000");
  while (true) {
    printLoginMenu();
    cin >> inputUser;

    switch (inputUser) {
    case 1:
      inBunker = loginMenu(userList);
      if (loginLimit == 3)
        return 0;
      break;
    case 2:
      registerMenu(userList);
      break;
    case 3:
      return 0;
    }

    while (inBunker == true) {
      printBunkerMenu();
      cin >> inputUser;
      if (typeUser == "user" && inputUser != 2 && inputUser != 5) {
        cout << "You Cant Acces This Menu\n";
        continue;
      }

      switch (inputUser) {
      case 1:
        addSurvivor(survivorList);
        break;
      case 2:
        readSurvivor(survivorList);
        break;
      case 3:
        updateAndFeeding(survivorList);
        break;
      case 4:
        kickSurvivor(survivorList);
        break;
      case 5:
        inBunker = false;
        break;
      default:
        cout << "Id Not In Option" << endl;
      }
    }
  }
  return 0;
}

void printLoginMenu() {
  cout << "-----------Login Menu-----------\n";
  cout << "1. Login\n";
  cout << "2. Regist\n";
  cout << "3. Exit\n";
  cout << "Input Menu Id : ";
}

void printBunkerMenu() {
  cout << "-----------Bunker Menu-----------\n";
  cout << "1. Add Survivor\n";
  cout << "2. Read List Survivor\n";
  cout << "3. Update Food Or Survivor\n";
  cout << "4. Kick Survivor\n";
  cout << "5. Exit\n";
  cout << "Input Menu Id : ";
}

bool loginMenu(vector<User> &userList) {
  string name, pass;
  cout << "Input Username : ";
  cin.ignore(1000, '\n');
  getline(cin, name);
  cout << "Input Password : ";
  cin >> pass;
  for (auto &account : userList) {
    if (account.userName == name && account.userPass == pass) {
      cout << "Login Succes\n";
      typeUser = account.userType;
      return true;
    }
  }
  cout << "Login Failed\n";
  loginLimit++;
  return false;
}

void registerMenu(vector<User> &userList) {

  cout << "Input Name : ";
  cin.ignore(1000, '\n');
  getline(cin, name);
  cout << "Input Pass : ";
  cin >> pass;
  for (auto &account : userList) {
    if (name == account.userName) {
      cout << "Username Already Use\n";
      return;
    }
  }
  userList.push_back(User(name, pass, "user"));

  cout << "Register Succes\n";
}

void addSurvivor(vector<Survivor> &survivorList) {
  if (survivorCount > bunkerLimit - 1) {
    cout << "Bunker Full\n";
  } else {
    cout << "Name : ";
    cin.ignore(1000, '\n');
    getline(cin, name);
    cout << "Gender : ";
    cin >> gender;
    cout << "Day : ";
    cin >> day;
    cout << "Month : ";
    cin >> month;
    cout << "Year : ";
    cin >> year;
    cout << endl;
    if (name.empty() || gender.empty() || day.empty() || month.empty() ||
        year.empty()) {
      cout << "Input Cannot Empty\n";
    } else {
      survivorList.push_back(Survivor(name, gender, day, month, year));
      survivorCount++;
      cout << "New Survivor Succes To Add\n";
    }
  }
}

void addSurvivor(vector<Survivor> &survivorList, string n, string g, string d,
                 string m, string y) {
  if (survivorCount > bunkerLimit - 1) {
    cout << "Bunker Full\n";
  } else {
    if (n.empty() || g.empty() || d.empty() || m.empty() || y.empty()) {
      cout << "Input Cannot Empty\n";
    } else {
      survivorList.push_back(Survivor(n, g, d, m, y));
      survivorCount++;
      cout << "New Survivor Succes To Add\n";
    }
  }
}
void updateAndFeeding(vector<Survivor> &survivorList) {
  while (true) {
    feedingCount = 0;
    cout << "-----------Update & Feeding Menu-----------\n";
    cout << "1. Search Food\n";
    cout << "2. Feeding Hungry Survivor\n";
    cout << "3. Exit\n";
    cout << "Input Id Menu : ";
    cin >> inputUser;
    if (inputUser == 1) {
      cout << "Search Food.....\n";
      foodStock += 3;
      cout << "Search Food Succes\n";
      cout << "Food Stock Now : " << foodStock << endl;
    } else if (inputUser == 2) {
      if (survivorCount == 0) {
        cout << "Bunker Empty\n";
        continue;
      }
      for (int i = 0; i < survivorCount; i++) {
        if (foodStock != 0 && survivorList[i].hungry == true) {
          survivorList[i].hungry = false;
          feedingCount++;
          foodStock--;
        }
      }
      cout << "Survivor Get Feed : " << feedingCount << endl;
      cout << "Food Stock : " << foodStock << endl;
    } else if (inputUser == 3) {
      cout << endl;
      break;
    }
  }
}

void readSurvivor(vector<Survivor> &survivorList) {
  Table t;
  t.add_row({"No", "Name", "Gender", "Status"});
  t[0].format().font_style({FontStyle::bold}).font_align(FontAlign::center);
  if (survivorCount == 0) {
    t.add_row({"-", "Bunker Empty", "-", "-"});
  } else {
    for (int i = 0; i < survivorCount; i++) {
      t.add_row({to_string(i + 1), survivorList[i].survivorName,
                 survivorList[i].survivorGender,
                 survivorList[i].hungry ? "Hungry" : "Not Hungry"});
    }
  }
  cout << t << endl;

  Table info;
  info.add_row({"Food Stock", foodStock == 0 ? "Empty" : to_string(foodStock)});
  info[0].format().font_style({FontStyle::bold});
  if (foodStock == 0)
    info[0][1].format().font_color(Color::red);
  else
    info[0][1].format().font_color(Color::green);
  cout << info << endl;
}

void kickSurvivor(vector<Survivor> &survivorList) {
  if (survivorCount == 0) {
    cout << "Bunker Empty\n";
    return;
  }
  Table t;
  t.add_row({"No", "Name"});
  t[0].format().font_style({FontStyle::bold}).font_align(FontAlign::center);
  for (int i = 0; i < survivorCount; i++) {
    t.add_row({to_string(i + 1), survivorList[i].survivorName});
  }
  cout << t << endl;
  cout << "Input [0] For Exit\n";
  cout << "Input Number Survivor to Kick From Bunker : ";
  cin >> inputUser;
  if (inputUser <= 0 || inputUser > survivorCount) {
    return;
  }
  for (int i = inputUser - 1; i < survivorCount - 1; i++) {
    survivorList[i] = survivorList[i + 1];
  }
  survivorList.pop_back();
  survivorCount--;
}
