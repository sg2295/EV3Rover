#ifndef _REPORT_INCLUDE_REPORT_H_
#define _REPORT_INCLUDE_REPORT_H_

#include <iostream>

namespace report {

unsigned num_warns = 0;

// TODO: Detect if logging is on, otherwise turn it off...
#define Log(...) do { report::_log_message(std::cout, __VA_ARGS__); } while(0)
// TODO: Add Error and Warn here...
#define Assert(exp, ...) do { if (!(exp)) { report::_log_message(std::cerr, "Error: ", __VA_ARGS__, " in ", __FILE__, ":", __LINE__, '\n'); std::exit(1); } } while (0)
#define Warn(exp, ...) do { if (!(exp)) { report::_log_message(std::cerr, "Warning:", __VA_ARGS__, " in ", __FILE__, ":", __LINE__, '\n'); report::num_warns++; } } while (0)

// N.B. Implementation details - use the above macros, NOT the below functions!
void _log_message(std::ostream& o){ (void)o; }

template<typename Head, typename ...Tail>
void _log_message(std::ostream& o, Head&& h, Tail&& ...t) {
  o << std::forward<Head>(h);
  _log_message(o, std::forward<Tail>(t)...);
}

}  // namespace report

#endif  // _REPORT_INCLUDE_REPORT_H_
