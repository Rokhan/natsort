/* -*- mode: c; c-file-style: "k&r" -*-

   natsort.cpp -- Example strnatcmp application.
   
   Copyright (C) 2000 by Martin Pool <mbp@humbug.org.au>

   This software is provided 'as-is', without any express or implied
   warranty.  In no event will the authors be held liable for any damages
   arising from the use of this software.
   
   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:
   
   1. The origin of this software must not be misrepresented; you must not
      claim that you wrote the original software. If you use this software
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.
   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original software.
   3. This notice may not be removed or altered from any source distribution.
*/

/* Partial change history:
 *
 * 2016-06-20: Compilation with visual studio, by Sebastien Mirabel
 * 2003-03-18: Add --reverse option, from Alessandro Pisani.
 */

#include "natsort/strnatcmp.h"


#include <boost/program_options.hpp>

#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using std::string;
using std::vector;

namespace po = boost::program_options;

static int fold_case = 0, verbose = 0, reverse = 0;

static void trace_result(char const *a, char const *b, int ret)
{
     char const *op;

     if (ret < 0)
	  op = "<";
     else if (ret > 0)
	  op = ">";
     else
	  op = "==";
     
     fprintf(stderr, "\tstrncatcmp: \"%s\" %s \"%s\"\n",
	     a, op, b);
}


static bool compare_strings(const string& a, const string& b)
{
     char const *pa = a.c_str(), *pb = b.c_str();
     int ret;

     if (fold_case)
	  ret = natsort::strcmpi(pa, pb);
     else
	  ret = natsort::strcmp(pa, pb);

	 if (reverse)
	  ret *= -1;

	 if (verbose)
	  trace_result(pa, pb, ret);

     return ret < 0;
}


int main(int argc, char **argv)
{
    vector<string> list;

    po::options_description desc(
        "Usage: natsort [OPTIONS]\n"
        "Performs a natural sort on standard input, and writes to standard output");

    desc.add_options()
        ("help,h", "show help text")
        ("verbose,v", "show comparisons")
        ("reverse,r", "reverse the result of comparisons")
        ("fold-case,f", "ignore case differences for letters");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if(vm.count("fold-case"))
    {
        fold_case = 1;
    }

    if(vm.count("help"))
    {
        std::cout << desc << "\n";
        return 0;
    }

    if(vm.count("reverse"))
    {
        reverse = 1;
    }

    if(vm.count("verbose"))
    {
        verbose = 1;
    }

    /* read lines into an array */
    while(1)
    {
        string line;
        if(!std::getline(std::cin, line))
            break;

        list.push_back(line);
    }

    std::sort(list.begin(), list.end(), compare_strings);

    /* and output */
    for(const auto& elt : list)
    {
        std::cout << elt << '\n';
    }

    return 0;
}
