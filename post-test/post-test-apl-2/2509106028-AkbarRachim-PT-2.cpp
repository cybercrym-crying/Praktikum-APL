#include <iostream>
using namespace std;

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

int main() {
  int inputUser, survivorCount = 0, bunkerLimit = 50, foodStock = 30,
                 feedingCount = 0, accountCount = 2, accountLimit = 10,
                 loginLimit = 0;
  bool condition = false, inBunker = false;
  string pass, name, gender, day, month, year, typeUser;
  User userList[accountLimit];
  userList[0] = User("Akbar Rachim", "028", "admin");
  userList[1] = User("Akbar", "001", "user");
  Survivor survivorList[bunkerLimit];
  while (true) {
    cout << "-----------Login Menu-----------\n";
    cout << "1. Login\n";
    cout << "2. Regist\n";
    cout << "3. Exit\n";
    cout << "Input Menu Id : ";
    cin >> inputUser;
    condition = false;

    switch (inputUser) {
    case 1:
      cout << "Input Username : ";
      cin.ignore(1000, '\n');
      getline(cin, name);
      cout << "Input Password : ";
      cin >> pass;
      for (auto &account : userList) {
        if (account.userName == name && account.userPass == pass) {
          cout << "Login Succes\n";
          condition = true;
          inBunker = true;
          typeUser = account.userType;
          break;
        }
      }
      if (condition == false) {
        cout << "Login Failed\n";
        loginLimit++;
        if (loginLimit == 3) {
          return 0;
        }
        break;
      } else {
        break;
      }

    case 2:
      if (accountCount >= accountLimit) {
        cout << "Database Full\n";
        continue;
      }
      cout << "Input Name : ";
      cin.ignore(1000, '\n');
      getline(cin, name);
      cout << "Input Pass : ";
      cin >> pass;
      for (auto &account : userList) {
        if (name == account.userName) {
          cout << "Username Already Use\n";
          condition = true;
          break;
        }
      }
      if (condition == false) {
        userList[accountCount] = User(name, pass, "user");
        accountCount++;
        break;
      } else {
        continue;
      }
    case 3:
      return 0;
    }
    while (inBunker == true) {
      cout << "-----------Bunker Menu-----------\n";
      cout << "1. Add Survivor\n";
      cout << "2. Read List Survivor\n";
      cout << "3. Update Food Or Survivor\n";
      cout << "4. Kick Survivor\n";
      cout << "5. Exit\n";
      cout << "Input Menu Id : ";
      cin >> inputUser;
      if (typeUser == "user" && inputUser != 2) {
        cout << "You Cant Acces This Menu\n";
        continue;
      }

      switch (inputUser) {

      case 1:
        if (survivorCount > bunkerLimit - 1) {
          cout << "Bunker Full\n";
          break;
        }
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
          break;
        }
        survivorList[survivorCount] = Survivor(name, gender, day, month, year);
        survivorCount++;
        break;

      case 2:
        cout << "---------------------------------\n";
        if (foodStock == 0) {
          cout << "Food Empty\n";
        } else {
          cout << "Food Stock : ";
          cout << foodStock << endl;
        }
        if (survivorCount == 0) {
          cout << "Bunker Empty\n";
          break;
        }

        for (int i = 0; i < survivorCount; i++) {
          cout << "---------------------------------" << endl;
          cout << "Survivor Name\t: ";
          cout << survivorList[i].survivorName << endl;
          cout << "Survivor Gender\t: ";
          cout << survivorList[i].survivorGender << endl;
          cout << "Survivor Hungry\t: ";
          cout << (survivorList[i].hungry ? "Hungry" : "Not Hungry") << endl;
        }
        break;

      case 3:
        while (true) {
          feedingCount = 0;
          cout << "---------------------------------\n";
          cout << "1. Search Food\n";
          cout << "2. Feeding Hungry Survivor\n";
          cout << "3. Exit\n";
          cout << "Input Id Menu : ";
          cin >> inputUser;
          if (inputUser == 1) {

            cout << "Search Food.....\n";
            foodStock += 3;
            cout << "Search Food Succes\n";
            cout << "Food Stock Now : ";
            cout << foodStock << endl;
            continue;
          }

          else if (inputUser == 2) {
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
            cout << "Survivor Get Feed : ";
            cout << feedingCount << endl;
            cout << "Food Stock : ";
            cout << foodStock << endl;
            continue;
          } else if (inputUser == 3) {
            cout << endl;
            break;
          }
        }
        break;
      case 4:
        if (survivorCount == 0) {
          cout << "Bunker Empty\n";
          break;
        }
        for (int i = 0; i < survivorCount; i++) {
          cout << "---------------------------------\n";
          cout << i + 1 << ". " << survivorList[i].survivorName << endl;
        }
        cout << "Input [0] For Exit\n";
        cout << "Input Number Survivor to Kick From Bunker : ";
        cin >> inputUser;
        if (inputUser <= 0) {
          break;
        } else {
          if (inputUser > survivorCount) {
            break;
          }
          while (inputUser - 1 < survivorCount - 1) {
            survivorList[inputUser - 1] = survivorList[inputUser];
            inputUser++;
          }
          survivorCount--;
          break;
        }
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
