#include <iostream>

namespace report {
// TODO: Detect if logging is on, otherwise turn it off...
#define Log(...) do { report::_log_message(std::cout, __VA_ARGS__); } while(0);
// TODO: Add Error and Warn here...


// N.B. Implementation details - use the above macros, NOT the below functions!
void _log_message(std::ostream& o){ (void)o; }

template<typename Head, typename ...Tail>
void _log_message(std::ostream& o, Head&& h, Tail && ...t) {
  o << std::forward<Head>(h);
  _log_message(o, std::forward<Tail>(t)...);
}

}  // namespace report
