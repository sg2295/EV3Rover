#ifndef _REPORT_INCLUDE_REPORT_H_
#define _REPORT_INCLUDE_REPORT_H_

#include <iostream>

namespace report {

#ifdef ENABLE_LOGGING
#define Log(...) do { report::_log_message(std::cout, __VA_ARGS__); } while(0)
#else
#define Log(...) do { report::_no_log(__VA_ARGS__); } while (0)
#endif
#define Error(exp, ...) do { if (!(exp)) { report::_log_message(std::cerr, "Error: ", __VA_ARGS__, " in ", __FILE__, ":", __LINE__, '\n'); std::exit(1); } } while (0)
#define Warn(exp, ...) do { if (!(exp)) { report::_log_message(std::cerr, "Warning: ", __VA_ARGS__, " in ", __FILE__, ":", __LINE__, '\n'); } } while (0)

// The below need to be inlined to adhere to ODR - this lib is used by many different translation units.
// N.B. Implementation details - use the above macros, NOT the below functions!

inline void _log_message(std::ostream& o){ (void)o; }

// No need to explicitly inline templates... because templates `are` inline!
template<typename Head, typename ...Tail>
void _log_message(std::ostream& o, Head&& h, Tail&& ...t) {
  o << std::forward<Head>(h);
  _log_message(o, std::forward<Tail>(t)...);
}

inline void _no_log() {}

template<typename Head, typename ...Tail>
void _no_log(Head&& h, Tail&& ...t) {
  std::ignore = h;
  _no_log(std::forward<Tail>(t)...);
}

}  // namespace report

#endif  // _REPORT_INCLUDE_REPORT_H_
