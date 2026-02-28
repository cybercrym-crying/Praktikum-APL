#include <iostream>
using namespace std;

int main() {
  string userName = "028", userPass = "028", inputName, inputPass, inputUser;
  int countAuth = 0;
  float length;
  while (true) {
    cout << "Input Username  : ";
    getline(cin, inputName);
    cout << "Input Password  : ";
    getline(cin, inputPass);
    if (inputName != userName || inputPass != userPass) {
      countAuth++;

      if (countAuth >= 3) {
        cout << "Username atau Password Salah\n";
        return 0;
      }
      cout << "Batas Percobaan Login : " << 3 - countAuth << endl;
      continue;
    }
    while (true) {
      cout << "\n-----------Program Konversi Panjang-----------\n";
      cout << "1. Meter \t-->\t Kilometer & Centimeter\n";
      cout << "2. Kilometer \t-->\t Meter & Centimeter\n";
      cout << "3. Centimeter \t-->\t Meter & Kilometer\n";
      cout << "4. Keluar Program\n";
      cout << "Input Menu    : ";
      cin >> inputUser;

      if (inputUser == "1") {
        cout << "Input Panjang : ";
        cin >> length;
        cout << "Kilometer     : " << length / 1000 << endl;
        cout << "Centimeter    : " << length * 100 << endl;
      } else if (inputUser == "2") {
        cout << "Input Panjang : ";
        cin >> length;
        cout << "Meter         : " << length * 1000 << endl;
        cout << "Centimeter    : " << length * 100000 << endl;
      } else if (inputUser == "3") {
        cout << "Input Panjang : ";
        cin >> length;
        cout << "Meter         : " << length / 100 << endl;
        cout << "Kilometer     : " << length / 100000 << endl;
      } else if (inputUser == "4") {
        return 0;
      }
    }
    break;
  }

  return 0;
}
