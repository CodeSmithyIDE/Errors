/*
    Copyright (c) 2019 Xavier Leclercq

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
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "ErrorTests.h"
#include "Ishiko/Errors/Error.h"
#include "Ishiko/Errors/Exception.h"

using namespace Ishiko::Tests;

ErrorTests::ErrorTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Error tests", environment)
{
    append<HeapAllocationErrorsTest>("Construction test 1", ConstructionTest1);
    append<HeapAllocationErrorsTest>("Construction test 2", ConstructionTest2);
    append<HeapAllocationErrorsTest>("Construction test 3", ConstructionTest3);
    append<HeapAllocationErrorsTest>("Construction test 4", ConstructionTest4);
    append<HeapAllocationErrorsTest>("fail test 1", FailTest1);
    append<HeapAllocationErrorsTest>("fail test 2", FailTest2);
    append<HeapAllocationErrorsTest>("fail test 3", FailTest3);
    append<HeapAllocationErrorsTest>("fail test 4", FailTest4);
    append<HeapAllocationErrorsTest>("succeed test 1", SucceedTest1);
}

void ErrorTests::ConstructionTest1(Test& test)
{
    Ishiko::Error error;

    ISHTF_FAIL_UNLESS((bool)error);
    ISHTF_FAIL_UNLESS(error.code() == -1);
    ISHTF_PASS();
}

void ErrorTests::ConstructionTest2(Test& test)
{
    Ishiko::Error error(0);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(error.code() == 0);
    ISHTF_PASS();
}

void ErrorTests::ConstructionTest3(Test& test)
{
    Ishiko::Error error(-2);
    
    ISHTF_FAIL_UNLESS((bool)error);
    ISHTF_FAIL_UNLESS(error.code() == -2);
    ISHTF_PASS();
}

void ErrorTests::ConstructionTest4(Test& test)
{
    Ishiko::Error error(Ishiko::Error::ThrowException);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(error.code() == 0);
    ISHTF_PASS();
}

void ErrorTests::FailTest1(Test& test)
{
    Ishiko::Error error(0);
    error.fail(-3);

    ISHTF_FAIL_UNLESS((bool)error);
    ISHTF_FAIL_UNLESS(error.code() == -3);
    ISHTF_PASS();
}

void ErrorTests::FailTest2(Test& test)
{
    Ishiko::Error error(4);
    error.fail(-3);

    ISHTF_FAIL_UNLESS((bool)error);
    ISHTF_FAIL_UNLESS(error.code() == 4);
    ISHTF_PASS();
}

void ErrorTests::FailTest3(Test& test)
{
    Ishiko::Error error(Ishiko::Error::ThrowException);
    try
    {
        error.fail(-3);

        ISHTF_FAIL();
    }
    catch (const Ishiko::Exception& e)
    {
        ISHTF_FAIL_UNLESS(std::string(e.what()) == "");
        ISHTF_PASS();
    }
}

void ErrorTests::FailTest4(Test& test)
{
    Ishiko::Error error(Ishiko::Error::ThrowException);
    try
    {
        error.fail(-3, "error message", __FILE__, __LINE__);

        ISHTF_FAIL();
    }
    catch (const Ishiko::Exception& e)
    {
        ISHTF_FAIL_UNLESS(std::string(e.what()) == "error message");
        ISHTF_FAIL_UNLESS(e.file().find("errortests.cpp") != std::string::npos);
        ISHTF_FAIL_UNLESS(e.line() == (__LINE__ - 8));
        ISHTF_PASS();
    }
}

void ErrorTests::SucceedTest1(Test& test)
{
    Ishiko::Error error;
    error.succeed();

    ISHTF_FAIL_IF((bool)error);
    ISHTF_FAIL_UNLESS(error.code() == 0);
    ISHTF_PASS();
}
