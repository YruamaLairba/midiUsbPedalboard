#ifndef WARNINGS_H
#define WARNINGS_H

#define DIAGNOSTIC_IGNORE_ALL \
  _Pragma ("GCC diagnostic ignored \"-Wall\"")\
  _Pragma ("GCC diagnostic ignored \"-Wextra\"")\
  _Pragma ("GCC diagnostic ignored \"-Wsign-conversion\"")\
  _Pragma ("GCC diagnostic ignored \"-Wignored-qualifiers\"")\
  _Pragma ("GCC diagnostic ignored \"-Wunused-variable\"")\
  _Pragma ("GCC diagnostic ignored \"-pedantic\"") 

#define DIAGNOSTIC_POP _Pragma ("GCC diagnostic pop")
#define DIAGNOSTIC_PUSH _Pragma ("GCC diagnostic push")

#define WARNINGS \
  _Pragma ("GCC diagnostic warning \"-Wall\"")\
  _Pragma ("GCC diagnostic warning \"-Wextra\"")\
  _Pragma ("GCC diagnostic warning \"-Wsign-conversion\"")\
  _Pragma ("GCC diagnostic warning \"-pedantic\"") 

#endif //WARNINGS_H
