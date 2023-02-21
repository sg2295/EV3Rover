#ifndef _REPORT_INCLUDE_REPORT_H_
#define _REPORT_INCLUDE_REPORT_H_

#include <iostream>

namespace report {

// TODO: Detect if logging is on, otherwise turn it off...
#define Log(...) do { report::_log_message(std::cout, __VA_ARGS__); } while(0)
#define Assert(exp, ...) do { if (!(exp)) { report::_log_message(std::cerr, "Error: ", __VA_ARGS__, " in ", __FILE__, ":", __LINE__, '\n'); std::exit(1); } } while (0)
#define Warn(exp, ...) do { if (!(exp)) { report::_log_message(std::cerr, "Warning: ", __VA_ARGS__, " in ", __FILE__, ":", __LINE__, '\n'); } } while (0)

// The below need to be inlined to adhere to ODR - this lib is used by many different translation units.
// N.B. Implementation details - use the above macros, NOT the below functions!
inline void _log_message(std::ostream& o){ (void)o; }

template<typename Head, typename ...Tail>
inline void _log_message(std::ostream& o, Head&& h, Tail&& ...t) {
  o << std::forward<Head>(h);
  _log_message(o, std::forward<Tail>(t)...);
}

}  // namespace report

#endif  // _REPORT_INCLUDE_REPORT_H_
