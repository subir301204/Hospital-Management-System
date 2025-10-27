#ifndef GETCH_CROSS_H
#define GETCH_CROSS_H

#include <iostream>
#include <string>

using namespace std;

#ifdef _WIN32
#include <conio.h>
inline char getch_cross() { return _getch(); }
#else
#include <termios.h>
#include <unistd.h>
inline char getch_cross() {
  char buf = 0;
  struct termios old = {0};
  if (tcgetattr(STDIN_FILENO, &old) < 0) perror("tcgetattr");
  old.c_lflag &= ~(ICANON | ECHO);  // disable Enter and echo
  if (tcsetattr(STDIN_FILENO, TCSANOW, &old) < 0) perror("tcsetattr");
  if (read(STDIN_FILENO, &buf, 1) < 0) perror("read");
  old.c_lflag |= (ICANON | ECHO);   // restore settings
  if (tcsetattr(STDIN_FILENO, TCSADRAIN, &old) < 0) perror("tcsetattr");
  return buf;
}
#endif

inline string getHiddenInput(string s) {
  string password;
  char ch;

  cout << s;
  cout.flush();

  while (true) {
#ifdef _WIN32
    ch = _getch();
#else
    ch = getch_cross();
#endif
    if (ch == '\r' || ch == '\n') {  // stop at Enter
      cout << endl;
      break;
    }
    else if ((ch == 8 || ch == 127) && !password.empty()) { // backspace
      password.pop_back();
      cout << "\b \b";
      cout.flush();
    }
    else if (ch >= 32 && ch <= 126) { // printable characters
      password.push_back(ch);
      cout << '*';
      cout.flush();
    }
  }

  return password;
}

#endif
