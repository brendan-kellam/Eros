#ifndef BASICPROFILER_H
#define BASICPROFILER_H

#pragma once

#include <iostream>
#include <chrono>

#define EROS_TIME_NOW (std::chrono::high_resolution_clock::now())

#define EROS_DURATION_NANO(a, b)     (std::chrono::duration_cast< std::chrono::nanoseconds  >(b - a).count())
#define EROS_DURATION_MICRO(a, b)    (std::chrono::duration_cast< std::chrono::microseconds >(b - a).count())
#define EROS_DURATION_MILLI(a, b)    (std::chrono::duration_cast< std::chrono::milliseconds >(b - a).count())
#define EROS_DURATION_SECOND(a, b)   (std::chrono::duration_cast< std::chrono::seconds      >(b - a).count())
#define EROS_DURATION_MINUTES(a, b)  (std::chrono::duration_cast< std::chrono::minutes      >(b - a).count())
#define EROS_DURATION_HOURS(a, b)	 (std::chrono::duration_cast< std::chrono::hours        >(b - a).count())


#endif /* BASICPROFILER_H */