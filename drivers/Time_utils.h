// -----------------------------------------------------------------------------
// Time_utils.h
//
// DISCLAIMER:
// Feabhas is furnishing this item "as is". Feabhas does not provide any
// warranty of the item whatsoever, whether express, implied, or statutory,
// including, but not limited to, any warranty of merchantability or fitness
// for a particular purpose or any warranty that the contents of the item will
// be error-free.
// In no respect shall Feabhas incur any liability for any damages, including,
// but limited to, direct, indirect, special, or consequential damages arising
// out of, resulting from, or any way connected to the use of the item, whether
// or not based upon warranty, contract, tort, or otherwise; whether or not
// injury was sustained by persons or property or otherwise; and whether or not
// loss was sustained from, or arose out of, the results of, the item, or any
// services that may be provided by Feabhas.
// -----------------------------------------------------------------------------

#ifndef TIME_UTILS_H_
#define TIME_UTILS_H_

#include <utility>
#include "Time_types.h"


namespace Time {

    // Wait for a period of time
    //
    void sleep(Time::Duration duration);


    // Sleep until an absolute point in time.
    // If the wake-up time is earlier than the
    // current time, the function returns
    // immediately.
    //
    void sleep(Time::Observation wakeup_time);


    // Using alias to ensure only Time::Observations are used
    // with until()
    //
    template <typename U>
    using is_time_obs = typename std::enable_if<std::is_same<Time::Observation, typename std::decay<U>::type>::value, bool>::type;


    // until is pure 'syntactic sugar' for creating
    // time observations.  It exists so you can write code
    // such as:
    // sleep(until(now() + 500_ms));
    //
    template <typename T, is_time_obs<T> = true>
    inline constexpr decltype(auto) until(T&& obs)
    {
        return std::forward<T>(obs);
    }


    // from() generates an absolute time observation for
    // use with sleep(Time::Observation).
    // from() uses the current time (using a call to now()) to compute
    // how long to actually sleep for.
    // 
    // returns     The absolute time to wake up, equivalent
    //             to (marker + duration)
    //
    // Usage:
    // void some_func()
    // {
    //     auto start_time = now();
    //
    //     // Code taking a long time...
    //
    //     // Wake up 1000ms from when start_time
    //     // was recorded.
    //     //
    //     Time::sleep(from(start_time, 1000_ms));
    // }
    //
    Time::Observation from(Time::Observation marker, Time::Duration duration);
 

    // Get the current time.
    //
    Time::Observation now();

} // namespace Time

#endif // TIME_UTILS_H_
