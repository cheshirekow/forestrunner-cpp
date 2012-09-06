#/!usr/bin/perl

#    Copyright (C) 2012 Josh Bialkowski (jbialk@mit.edu)
#  
#    This file is part of forestrunner
#  
#    forestrunner is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#  
#    forestrunner is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#  
#    You should have received a copy of the GNU General Public License
#    along with forestrunner.  If not, see <http://www.gnu.org/licenses/>.

use Cwd 'abs_path';
use File::Basename;

my $this_path   = abs_path($0);
my $script_path = dirname($this_path);

chdir $script_path or die "Cannot chdir to $script_path $!\n\n";

my ($output_h, $output_hpp, $output_cpp);

open ($output_h, '>', '../src/forestrunner/util/Printf.h')
    or die "Failed to open Printf.h for write $!\n";
    
open ($output_hpp, '>', '../src/forestrunner/util/Printf.hpp')
    or die "Failed to open Printf.hpp for write $!\n";
    
open ($output_cpp, '>', '../src/forestrunner/util/Printf.cpp')
    or die "Failed to open Printf.cpp for write $!\n";
    


print $output_cpp <<'HERE';

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
 *  along with Fontconfigmm.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *  \file   printf.cpp
 *
 *  \date   Sep 6, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "forestrunner/util/Printf.h"
#include <cstring>

namespace forestrunner {
namespace         util {

Printf::Printf()
{
    m_size = 256;
    m_buf  = new char[256];
}

Printf::~Printf()
{
    delete [] m_buf;
}






} // namespace game 
} // namespace forestrunner 


HERE
    
close ($output_cpp);




# Print headers for the h and hpp files

print $output_h <<'HERE';

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



HERE

print $output_hpp <<'HERE';

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





HERE



# print templates

$maxParams = 9;

for($i=1; $i <= $maxParams; $i++)
{
	print $output_h '        template <typename T1';
	for($j=2; $j<=$i; $j++)
	{
        print $output_h ",\n                  typename T$j";
	}
	print $output_h ">\n";
	print $output_h "        const char* operator()(const char* fmt, T1";
	for($j=2; $j<=$i; $j++)
    {
        print $output_h ", T$j";
    }
    print $output_h ");\n\n";
    
    
    print $output_hpp 'template <typename T1';
    for($j=2; $j<=$i; $j++)
    {
        print $output_hpp ",\n          typename T$j";
    }
    print $output_hpp ">\n";
    
    print $output_hpp "const char* Printf::operator()(const char* fmt, T1 p1";
    for($j=2; $j<=$i; $j++)
    {
        print $output_hpp ", T$j p$j";
    }
    print $output_hpp ")\n{\n";
    print $output_hpp "    size_t result = snprintf(m_buf,m_size-1,fmt,p1";
    for($j=2; $j<=$i; $j++)
    {
        print $output_hpp ",  p$j";
    }
    print $output_hpp ");\n";
    print $output_hpp <<'HERE';
    if( result >= m_size )
    {
        delete [] m_buf;
        m_size = result+1;
        m_buf = new char[m_size];
HERE

    print $output_hpp "        snprintf(m_buf,m_size-1,fmt,p1";
    
    for($j=2; $j<=$i; $j++)
    {
        print $output_hpp ",  p$j";
    }
    
    print $output_hpp ");\n";
    
    print $output_hpp <<'HERE';
    }
    
    return m_buf;
}    


    
  
HERE
}






# Print footers

print $output_h <<'HERE';

};

} // namespace util
} // namespace forestrunner 

#endif // PRINTF_H_


HERE

print $output_hpp <<'HERE';



} // namespace util
} // namespace forestrunner


#endif // PRINTF_H_

HERE



close ($output_h);
close ($output_hpp);