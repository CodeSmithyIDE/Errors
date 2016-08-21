/*
    Copyright (c) 2015-2016 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OROTHER DEALINGS
    IN THE SOFTWARE.
*/

#ifndef _ISHIKO_ERRORS_EXCEPTION_H_
#define _ISHIKO_ERRORS_EXCEPTION_H_

#include <stdexcept>

namespace Ishiko
{
	
class Exception : public std::exception
{
public:
    Exception(const std::string& message, const char* file, int line);
    virtual ~Exception() throw();

#ifndef _WIN32
    virtual const char* what() const throw();
#endif

    const std::string& file() const;
    int line() const;

private:
#ifndef _WIN32
    // The Visual C++ STL has custom support for the what information
    // so we use it. On other platforms we define our own variable to
    // store that information.
    std::string m_what;
#endif
    std::string m_file;
    int m_line;
};

}

#endif