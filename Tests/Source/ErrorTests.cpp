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

using namespace Ishiko::TestFramework;

void ErrorTests::AddTests(TestHarness& theTestHarness)
{
    TestSequence& errorTestSequence = theTestHarness.appendTestSequence("Error tests");

    new HeapAllocationErrorsTest("Creation test 1", CreationTest1, errorTestSequence);
    new HeapAllocationErrorsTest("Creation test 2", CreationTest2, errorTestSequence);
    new HeapAllocationErrorsTest("Creation test 3", CreationTest3, errorTestSequence);
}

TestResult::EOutcome ErrorTests::CreationTest1()
{
    TestResult::EOutcome result = TestResult::eFailed;

    Ishiko::Error error;
    if (error)
    {
        result = TestResult::ePassed;
    }

    return result;
}

TestResult::EOutcome ErrorTests::CreationTest2()
{
    TestResult::EOutcome result = TestResult::eFailed;

    Ishiko::Error error(0);
    if (!error)
    {
        result = TestResult::ePassed;
    }

    return result;
}

TestResult::EOutcome ErrorTests::CreationTest3()
{
    TestResult::EOutcome result = TestResult::eFailed;

    Ishiko::Error error(-2);
    if (error)
    {
        result = TestResult::ePassed;
    }

    return result;
}