
/*
 *  Copyright (C) 2012 Josh Bialkowski (jbialk@mit.edu)
 *
 *  This file is part of forestrunner.
 *
 *  forestrunner is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  forestrunner is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with forestrunner.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *  \file   printf.h
 *
 *  \date   Sep 6, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef FORESTRUNNER_UTIL_PRINTF_H_
#define FORESTRUNNER_UTIL_PRINTF_H_

#include <cstring>

namespace forestrunner {
namespace         util {

/// automatically-sized string buffer for formatting character strings
class Printf
{
    private:
        size_t  m_size;
        char*   m_buf;

    public:
        Printf();
        ~Printf();



        template <typename T1>
        const char* operator()(const char* fmt, T1);

        template <typename T1,
                  typename T2>
        const char* operator()(const char* fmt, T1, T2);

        template <typename T1,
                  typename T2,
                  typename T3>
        const char* operator()(const char* fmt, T1, T2, T3);

        template <typename T1,
                  typename T2,
                  typename T3,
                  typename T4>
        const char* operator()(const char* fmt, T1, T2, T3, T4);

        template <typename T1,
                  typename T2,
                  typename T3,
                  typename T4,
                  typename T5>
        const char* operator()(const char* fmt, T1, T2, T3, T4, T5);

        template <typename T1,
                  typename T2,
                  typename T3,
                  typename T4,
                  typename T5,
                  typename T6>
        const char* operator()(const char* fmt, T1, T2, T3, T4, T5, T6);

        template <typename T1,
                  typename T2,
                  typename T3,
                  typename T4,
                  typename T5,
                  typename T6,
                  typename T7>
        const char* operator()(const char* fmt, T1, T2, T3, T4, T5, T6, T7);

        template <typename T1,
                  typename T2,
                  typename T3,
                  typename T4,
                  typename T5,
                  typename T6,
                  typename T7,
                  typename T8>
        const char* operator()(const char* fmt, T1, T2, T3, T4, T5, T6, T7, T8);

        template <typename T1,
                  typename T2,
                  typename T3,
                  typename T4,
                  typename T5,
                  typename T6,
                  typename T7,
                  typename T8,
                  typename T9>
        const char* operator()(const char* fmt, T1, T2, T3, T4, T5, T6, T7, T8, T9);


};

} // namespace util
} // namespace forestrunner 

#endif // PRINTF_H_


