// utilities.cpp

// Note:  YOU MUST NOT MAKE ANY CHANGE TO THIS FILE!

#include "utilities.h"
#include <cstdlib>
#include <ctime>

  // Return a uniformly distributed random integer from 0 to limit-1 inclusive


#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>
#include <conio.h>

char getCharacter()
{
    int c = _getch();
    if (c != 0xE0  &&  c != 0x00)  // first of the two sent by arrow keys
        return c;
    else
    {
        c = _getch();
        switch (c)
        {
          case 'K':  return ARROW_LEFT;
          case 'M':  return ARROW_RIGHT;
          case 'H':  return ARROW_UP;
          case 'P':  return ARROW_DOWN;
          default:   return '?';
        }
    }
}


#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <termios.h>
using namespace std;

static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal escape sequence:  ESC [
static const char* ESC_SEQ_X = "\xEF\x9C";  // Xcode Console arrow key escape sequence

class TerminalModeSetter
{
  public:
    TerminalModeSetter()
    {
        tcgetattr(STDIN_FILENO, &m_old);
        m_new = m_old;
        m_new.c_lflag &= ~(ICANON | ECHO);
        m_new.c_cc[VMIN] = 1;
        m_new.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &m_new);
    }
    ~TerminalModeSetter()
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &m_old);
    }
  private:
    termios m_old;
    termios m_new;
};

char getCharacter()
{
    static TerminalModeSetter dummy;
    char ch;
    if (!cin.get(ch))
        return '?';
    if (ch != ESC_SEQ[0]  &&  ch != ESC_SEQ_X[0])
        return ch;
    if (!cin.get(ch)  ||  (ch != ESC_SEQ[1]  &&  ch != ESC_SEQ_X[1])  ||  !cin.get(ch))
        return '?';
    switch (ch)
    {
      case 'D': case '\x82':  return ARROW_LEFT;
      case 'C': case '\x83':  return ARROW_RIGHT;
      case 'A': case '\x80':  return ARROW_UP;
      case 'B': case '\x81':  return ARROW_DOWN;
      default:   return '?';
    }
}


#endif
