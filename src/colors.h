#ifndef COLORS
#define COLORS

/**
 * @defgroup COLOR_GROUP COLOR Definicje kolorow uzywanych w terminalu
 *
 * @brief Definicje kolorow uzywanych w terminalu
 * @{
 */
#define COLOR_RESET "\033[0m"
/** Black */
#define COLOR_BLACK "\033[30m"
/** Red */
#define COLOR_RED "\033[31m"
/** Green */
#define COLOR_GREEN "\033[32m"
/** Yellow */
#define COLOR_YELLOW "\033[33m"
/** Blue */
#define COLOR_BLUE "\033[34m"
/** Magenta */
#define COLOR_MAGENTA "\033[35m"
/** Cyan */
#define COLOR_CYAN "\033[36m"
/** White */
#define COLOR_WHITE "\033[37m"
/** Bold Black */
#define COLOR_BOLDBLACK "\033[1m\033[30m"
/** Bold Red */
#define COLOR_BOLDRED "\033[1m\033[31m"
/** Bold Green */
#define COLOR_BOLDGREEN "\033[1m\033[32m"
/** Bold Yellow */
#define COLOR_BOLDYELLOW "\033[1m\033[33m"
/** Bold Blue */
#define COLOR_BOLDBLUE "\033[1m\033[34m"
/** Bold Magenta */
#define COLOR_BOLDMAGENTA "\033[1m\033[35m"
/** Bold Cyan */
#define COLOR_BOLDCYAN "\033[1m\033[36m"
/** Bold White */
#define COLOR_BOLDWHITE "\033[1m\033[37m"
/** Magiczna komenda czyszczaca ekran terminala ref. https://stackoverflow.com/questions/4062045/clearing-terminal-in-linux-with-c-code */
#define CLEARSCREEN "\033[H\033[2J\033[3J"
/**@}*/

#endif