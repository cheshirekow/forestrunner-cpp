
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
 *  \file   Printf.hpp
 *
 *  \date   Sep 6, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */


#ifndef FORESTRUNNER_UTIL_PRINTF_HPP_
#define FORESTRUNNER_UTIL_PRINTF_HPP_

namespace forestrunner {
namespace         util {





template <typename T1>
const char* Printf::operator()(const char* fmt, T1 p1)
{
    size_t result = snprintf(m_buf,m_size,fmt,p1);
    if( result >= m_size )
    {
        delete [] m_buf;
        m_size = result+1;
        m_buf = new char[m_size];
        snprintf(m_buf,m_size,fmt,p1);
    }
    
    return m_buf;
}    


    
  
template <typename T1,
          typename T2>
const char* Printf::operator()(const char* fmt, T1 p1, T2 p2)
{
    size_t result = snprintf(m_buf,m_size,fmt,p1,  p2);
    if( result >= m_size )
    {
        delete [] m_buf;
        m_size = result+1;
        m_buf = new char[m_size];
        snprintf(m_buf,m_size,fmt,p1,  p2);
    }
    
    return m_buf;
}    


    
  
template <typename T1,
          typename T2,
          typename T3>
const char* Printf::operator()(const char* fmt, T1 p1, T2 p2, T3 p3)
{
    size_t result = snprintf(m_buf,m_size,fmt,p1,  p2,  p3);
    if( result >= m_size )
    {
        delete [] m_buf;
        m_size = result+1;
        m_buf = new char[m_size];
        snprintf(m_buf,m_size,fmt,p1,  p2,  p3);
    }
    
    return m_buf;
}    


    
  
template <typename T1,
          typename T2,
          typename T3,
          typename T4>
const char* Printf::operator()(const char* fmt, T1 p1, T2 p2, T3 p3, T4 p4)
{
    size_t result = snprintf(m_buf,m_size,fmt,p1,  p2,  p3,  p4);
    if( result >= m_size )
    {
        delete [] m_buf;
        m_size = result+1;
        m_buf = new char[m_size];
        snprintf(m_buf,m_size,fmt,p1,  p2,  p3,  p4);
    }
    
    return m_buf;
}    


    
  
template <typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5>
const char* Printf::operator()(const char* fmt, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5)
{
    size_t result = snprintf(m_buf,m_size,fmt,p1,  p2,  p3,  p4,  p5);
    if( result >= m_size )
    {
        delete [] m_buf;
        m_size = result+1;
        m_buf = new char[m_size];
        snprintf(m_buf,m_size,fmt,p1,  p2,  p3,  p4,  p5);
    }
    
    return m_buf;
}    


    
  
template <typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6>
const char* Printf::operator()(const char* fmt, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6)
{
    size_t result = snprintf(m_buf,m_size,fmt,p1,  p2,  p3,  p4,  p5,  p6);
    if( result >= m_size )
    {
        delete [] m_buf;
        m_size = result+1;
        m_buf = new char[m_size];
        snprintf(m_buf,m_size,fmt,p1,  p2,  p3,  p4,  p5,  p6);
    }
    
    return m_buf;
}    


    
  
template <typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7>
const char* Printf::operator()(const char* fmt, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7)
{
    size_t result = snprintf(m_buf,m_size,fmt,p1,  p2,  p3,  p4,  p5,  p6,  p7);
    if( result >= m_size )
    {
        delete [] m_buf;
        m_size = result+1;
        m_buf = new char[m_size];
        snprintf(m_buf,m_size,fmt,p1,  p2,  p3,  p4,  p5,  p6,  p7);
    }
    
    return m_buf;
}    


    
  
template <typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8>
const char* Printf::operator()(const char* fmt, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8)
{
    size_t result = snprintf(m_buf,m_size,fmt,p1,  p2,  p3,  p4,  p5,  p6,  p7,  p8);
    if( result >= m_size )
    {
        delete [] m_buf;
        m_size = result+1;
        m_buf = new char[m_size];
        snprintf(m_buf,m_size,fmt,p1,  p2,  p3,  p4,  p5,  p6,  p7,  p8);
    }
    
    return m_buf;
}    


    
  
template <typename T1,
          typename T2,
          typename T3,
          typename T4,
          typename T5,
          typename T6,
          typename T7,
          typename T8,
          typename T9>
const char* Printf::operator()(const char* fmt, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9)
{
    size_t result = snprintf(m_buf,m_size,fmt,p1,  p2,  p3,  p4,  p5,  p6,  p7,  p8,  p9);
    if( result >= m_size )
    {
        delete [] m_buf;
        m_size = result+1;
        m_buf = new char[m_size];
        snprintf(m_buf,m_size,fmt,p1,  p2,  p3,  p4,  p5,  p6,  p7,  p8,  p9);
    }
    
    return m_buf;
}    


    
  



} // namespace util
} // namespace forestrunner


#endif // PRINTF_H_

