#include "tabulate.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <math.h>
#include <stdexcept>
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
  int idSurvivor;
  string survivorName;
  string survivorGender;
  bool life = true;
  bool hungry = true;
  Date dateEntry;
  Survivor() = default;
  Survivor(int id, string n, string g, string d, string m, string y)
      : idSurvivor(id), survivorName(n), survivorGender(g), dateEntry(d, m, y) {
  }
};

struct Bunker {
  int limit;
  int survivorCount;
  int foodStock;
};

int inputUser, feedingCount = 0, loginLimit = 0, nextId = 0;
string pass, name, gender, day, month, year, typeUser;

void printLoginMenu();
void printBunkerMenu();
bool loginMenu(vector<User> &userList);
void registerMenu(vector<User> &userList);
void addSurvivor(vector<Survivor> &survivorList, Bunker *bunker);
void addSurvivor(vector<Survivor> &survivorList, Bunker *bunker, string n,
                 string g, string d, string m, string y);
void updateAndFeeding(vector<Survivor> &survivorList, Bunker *bunker);
void readSurvivor(vector<Survivor> *survivorList, Bunker *bunker);
void kickSurvivor(vector<Survivor> *survivorList, Bunker *bunker);

int main() {
  Bunker bunker = {50, 0, 10};
  bool inBunker = false;
  vector<User> userList;
  userList.push_back(User("Akbar Rachim", "028", "admin"));
  userList.push_back(User("Akbar", "001", "user"));
  vector<Survivor> survivorList;
  addSurvivor(survivorList, &bunker, "Budi", "Male", "01", "01", "2003");
  addSurvivor(survivorList, &bunker, "Radi", "Male", "01", "01", "2002");
  addSurvivor(survivorList, &bunker, "Gea", "Female", "01", "01", "2001");
  addSurvivor(survivorList, &bunker, "Zea", "Female", "01", "01", "2004");
  while (true) {
    printLoginMenu();
    try {
      cin >> inputUser;
      if (cin.fail()) {
        throw runtime_error("Input Must be integer");
      }
    } catch (const runtime_error &e) {
      cerr << "Error : " << e.what() << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

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
      try {
        cin >> inputUser;
        if (cin.fail()) {
          throw runtime_error("Input Must be integer");
        }
      } catch (const runtime_error &e) {
        cerr << "Error : " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
      if (typeUser == "user" && inputUser != 2 && inputUser != 5) {
        cout << "You Cant Acces This Menu\n";
        continue;
      }

      switch (inputUser) {
      case 1:
        addSurvivor(survivorList, &bunker);
        break;
      case 2:
        readSurvivor(&survivorList, &bunker);
        break;
      case 3:
        updateAndFeeding(survivorList, &bunker);
        break;
      case 4:
        kickSurvivor(&survivorList, &bunker);
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

void insertionSortByName(vector<Survivor> &dataUser) {
  int j;
  for (int i = 1; i < dataUser.size(); i++) {
    Survivor key = dataUser[i];
    j = i - 1;
    while (j >= 0 && key.survivorName > dataUser[j].survivorName) {
      dataUser[j + 1] = dataUser[j];
      j--;
    }
    dataUser[j + 1] = key;
  }
}

void selectionSortByYear(vector<Survivor> &dataUser) {
  int min_index;
  for (int i = 0; i < dataUser.size(); i++) {
    min_index = i;
    for (int j = i + 1; j < dataUser.size(); j++) {
      if (dataUser[j].dateEntry.year < dataUser[min_index].dateEntry.year) {
        min_index = j;
      }
    }
    if (min_index != i) {
      swap(dataUser[i], dataUser[min_index]);
    }
  }
}

void bubbleSortByName(vector<Survivor> &dataUser) {
  for (int i = 0; i < dataUser.size(); i++) {
    for (int j = 0; j < dataUser.size() - 1; j++) {
      if (dataUser[j].survivorName > dataUser[j + 1].survivorName) {
        swap(dataUser[j], dataUser[j + 1]);
      }
    }
  }
}

void linierSearchByName(vector<Survivor> &dataUser) {
  string inputUser;
  bool found = false;
  cin.ignore(1000, '\n');
  cout << "Input Survivor Name : ";
  getline(cin, inputUser);
  for (int i = 0; i < dataUser.size(); i++) {
    if (inputUser == dataUser[i].survivorName) {
      cout << "Survivor Found : " << dataUser[i].survivorName << endl;
      found = true;
    }
  }
  if (found == false) {
    cout << "Survivor Not Found\n";
  }
}

void binarySearchById(vector<Survivor> &dataUser) {
  int low = 0, mid, high = dataUser.size() - 1;
  cout << "Input Survivor Id : ";
  // sorting by id
  for (int i = 0; i < dataUser.size(); i++) {
    for (int j = 0; j < dataUser.size() - 1; j++) {
      if (dataUser[j].idSurvivor > dataUser[j + 1].idSurvivor) {
        swap(dataUser[j], dataUser[j + 1]);
      }
    }
  }
  try {
    cin >> inputUser;
    if (cin.fail()) {
      throw runtime_error("Input Must be integer");
    }
  } catch (const runtime_error &e) {
    cerr << "Error : " << e.what() << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  while (low <= high) {
    mid = low + ((high - low) / 2);
    if (dataUser[mid].idSurvivor == inputUser) {
      cout << "Survivor Found : " << dataUser[mid].survivorName << endl;
      return;
    } else if (dataUser[mid].idSurvivor < inputUser) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  cout << "Not Found\n";
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
      loginLimit = 0;
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

void addSurvivor(vector<Survivor> &survivorList, Bunker *bunker) {
  if (bunker->survivorCount > bunker->limit - 1) {
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
      survivorList.push_back(Survivor(nextId, name, gender, day, month, year));
      bunker->survivorCount++;
      nextId++;
      cout << "New Survivor Succes To Add\n";
    }
  }
}

void addSurvivor(vector<Survivor> &survivorList, Bunker *bunker, string n,
                 string g, string d, string m, string y) {
  if (bunker->survivorCount > bunker->limit - 1) {
    cout << "Bunker Full\n";
  } else {
    if (n.empty() || g.empty() || d.empty() || m.empty() || y.empty()) {
      cout << "Input Cannot Empty\n";
    } else {
      survivorList.push_back(Survivor(nextId, n, g, d, m, y));
      bunker->survivorCount++;
      nextId++;
      cout << "New Survivor Succes To Add\n";
    }
  }
}

void updateAndFeeding(vector<Survivor> &survivorList, Bunker *bunker) {
  while (true) {
    feedingCount = 0;
    cout << "-----------Update & Feeding Menu-----------\n";
    cout << "1. Search Food\n";
    cout << "2. Feeding Hungry Survivor\n";
    cout << "3. Exit\n";
    cout << "Input Id Menu : ";
    try {
      cin >> inputUser;
      if (cin.fail()) {
        throw runtime_error("Input Must be integer");
      }
    } catch (const runtime_error &e) {
      cerr << "Error : " << e.what() << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (inputUser == 1) {
      cout << "Search Food.....\n";
      bunker->foodStock += 3;
      cout << "Search Food Succes\n";
      cout << "Food Stock Now : " << bunker->foodStock << endl;
    } else if (inputUser == 2) {
      if (bunker->survivorCount == 0) {
        cout << "Bunker Empty\n";
        continue;
      }
      for (int i = 0; i < bunker->survivorCount; i++) {
        if (bunker->foodStock != 0 && survivorList[i].hungry == true) {
          survivorList[i].hungry = false;
          feedingCount++;
          bunker->foodStock--;
        }
      }
      cout << "Survivor Get Feed : " << feedingCount << endl;
      cout << "Food Stock : " << bunker->foodStock << endl;
    } else if (inputUser == 3) {
      cout << endl;
      break;
    }
  }
}

void readSurvivor(vector<Survivor> *survivorList, Bunker *bunker) {
  while (true) {
    cout << "1. Sorting By Name (A-Z)\n";
    cout << "2. Sorting By Name (Z-A)\n";
    cout << "3. Sorting By Year (New-O)\n";
    cout << "4. Searching By Id\n";
    cout << "5. Searching By Name\n";
    cout << "Input User : ";

    try {
      cin >> inputUser;
      if (cin.fail()) {
        throw runtime_error("Input Must be integer");
      }
    } catch (const runtime_error &e) {
      cerr << "Error : " << e.what() << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (inputUser == 1) {
      bubbleSortByName(*survivorList);
      break;
    } else if (inputUser == 2) {
      insertionSortByName(*survivorList);
      break;
    } else if (inputUser == 3) {
      selectionSortByYear(*survivorList);
      break;
    } else if (inputUser == 4) {
      binarySearchById(*survivorList);
      return;
    } else if (inputUser == 5) {
      linierSearchByName(*survivorList);
      return;
    } else {
      continue;
    }
  }
  Table t;
  t.add_row({"No", "Id", "Name", "Gender", "Status", "Entry Year"});
  t[0].format().font_style({FontStyle::bold}).font_align(FontAlign::center);
  if (bunker->survivorCount == 0) {
    t.add_row({"-", "Bunker Empty", "-", "-"});
  } else {
    for (int i = 0; i < bunker->survivorCount; i++) {
      t.add_row({to_string(i + 1), to_string((*survivorList)[i].idSurvivor),
                 (*survivorList)[i].survivorName,
                 (*survivorList)[i].survivorGender,
                 (*survivorList)[i].hungry ? "Hungry" : "Not Hungry",
                 (*survivorList)[i].dateEntry.year});
    }
  }
  cout << t << endl;

  Table info;
  info.add_row({"Food Stock", bunker->foodStock == 0
                                  ? "Empty"
                                  : to_string(bunker->foodStock)});
  info[0].format().font_style({FontStyle::bold});
  if (bunker->foodStock == 0)
    info[0][1].format().font_color(Color::red);
  else
    info[0][1].format().font_color(Color::green);
  cout << info << endl;
}

void kickSurvivor(vector<Survivor> *survivorList, Bunker *bunker) {
  if (bunker->survivorCount == 0) {
    cout << "Bunker Empty\n";
    return;
  }
  Table t;
  t.add_row({"No", "Name"});
  t[0].format().font_style({FontStyle::bold}).font_align(FontAlign::center);
  for (int i = 0; i < bunker->survivorCount; i++) {
    t.add_row({to_string(i + 1), (*survivorList)[i].survivorName});
  }
  cout << t << endl;
  cout << "Input [0] For Exit\n";
  cout << "Input Number Survivor to Kick From Bunker : ";
  try {
    cin >> inputUser;
    if (cin.fail()) {
      throw runtime_error("Input Must be integer");
    }
  } catch (const runtime_error &e) {
    cerr << "Error : " << e.what() << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  if (inputUser <= 0 || inputUser > bunker->survivorCount) {
    return;
  }
  for (int i = inputUser - 1; i < bunker->survivorCount - 1; i++) {
    (*survivorList)[i] = (*survivorList)[i + 1];
  }
  survivorList->pop_back();
  bunker->survivorCount--;
}
