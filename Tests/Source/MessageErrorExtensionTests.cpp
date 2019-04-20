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

#include "MessageErrorExtensionTests.h"
#include "Ishiko/Errors/MessageErrorExtension.h"
#include "Ishiko/Errors/Error.h"
#include <sstream>

using namespace Ishiko::Tests;

MessageErrorExtensionTests::MessageErrorExtensionTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "MessageErrorExtension tests", environment)
{
    append<HeapAllocationErrorsTest>("Construction test 1", ConstructionTest1);
    append<HeapAllocationErrorsTest>("Construction test 2", ConstructionTest2);
    append<HeapAllocationErrorsTest>("fail test 1", FailTest1);
    append<HeapAllocationErrorsTest>("operator<< test 1", StreamInsertionTest1);
}

void MessageErrorExtensionTests::ConstructionTest1(Test& test)
{
    Ishiko::MessageErrorExtension messageExtension;

    ISHTF_FAIL_UNLESS(messageExtension.message() == "");
    ISHTF_FAIL_UNLESS(messageExtension.file() == "");
    ISHTF_FAIL_UNLESS(messageExtension.line() == -1);
    ISHTF_PASS();
}

void MessageErrorExtensionTests::ConstructionTest2(Test& test)
{
    Ishiko::MessageErrorExtension messageExtension("unknown", "file1", 3);

    ISHTF_FAIL_UNLESS(messageExtension.message() == "unknown");
    ISHTF_FAIL_UNLESS(messageExtension.file() == "file1");
    ISHTF_FAIL_UNLESS(messageExtension.line() == 3);
    ISHTF_PASS();
}

void MessageErrorExtensionTests::FailTest1(Test& test)
{
    Ishiko::Error error(0, new Ishiko::MessageErrorExtension());
    error.fail(-3, "a bad error", "file1", 3);

    Ishiko::MessageErrorExtension* messageExtension = static_cast<Ishiko::MessageErrorExtension*>(error.extension());

    ISHTF_ABORT_UNLESS(messageExtension);
    ISHTF_FAIL_UNLESS(messageExtension->message() == "a bad error");
    ISHTF_FAIL_UNLESS(messageExtension->file() == "file1");
    ISHTF_FAIL_UNLESS(messageExtension->line() == 3);
    ISHTF_PASS();
}

void MessageErrorExtensionTests::StreamInsertionTest1(Test& test)
{
    Ishiko::Error error(0, new Ishiko::MessageErrorExtension());
    error.fail(-3, "a bad error", "file1", 3);

    std::stringstream errorMessage;
    errorMessage << error;

    ISHTF_FAIL_UNLESS(errorMessage.str() == "Error: -3, a bad error [file: file1, line: 3]");
    ISHTF_PASS();
}