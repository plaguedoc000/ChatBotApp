#ifndef CLEARSCREEN_H
#define CLEARSCREEN_H

#ifdef _WIN32
    #define CLEAR_CMD "cls"
#else
    #define CLEAR_CMD "clear"
#endif

inline void clearScreen() {
    std::system(CLEAR_CMD);
}

#endif // CLEARSCREEN_H
