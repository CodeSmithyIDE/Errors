/*
    Copyright (c) 2017-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "Error.h"
#include "Exception.h"

namespace Ishiko
{

Error::Error() noexcept
    : m_extension(0)
{
}

Error::Error(int code, const ErrorCategory& category) noexcept
    : m_condition(code, category), m_extension(0)
{
}

Error::Error(ErrorExtension* extension) noexcept
    : m_extension(extension)
{
}

Error::Error(int code, const ErrorCategory& category, ErrorExtension* extension) noexcept
    : m_condition(code, category), m_extension(extension)
{
}

Error::~Error() noexcept
{
    if (m_extension)
    {
        m_extension->release();
    }
}

Error::operator bool() const noexcept
{
    return (bool)m_condition;
}

bool Error::operator!() const noexcept
{
    return !m_condition;
}

const ErrorCondition& Error::condition() const noexcept
{
    return m_condition;
}

bool Error::tryGetOrigin(const char*& file, int& line) const noexcept
{
    bool result = false;

    if (*this && m_extension)
    {
        result = m_extension->tryGetOrigin(file, line);
    }

    return result;
}

void Error::fail(int code, const ErrorCategory& category) noexcept
{
    if (m_extension)
    {
        m_extension->onFail(code, "", "", -1);
    }
    
    if (!m_condition)
    {
        m_condition.fail(code, category);
    }
}

void Error::fail(int code, const ErrorCategory& category, const std::string& message, const char* file, int line) noexcept
{
    if (m_extension)
    {
        m_extension->onFail(code, message, file, line);
    }

    if (!m_condition)
    {
        m_condition.fail(code, category);
    }
}

void Error::succeed() noexcept
{
    m_condition.succeed();
}

const ErrorExtension* Error::extension() const noexcept
{
    return m_extension;
}

ErrorExtension* Error::extension() noexcept
{
    return m_extension;
}

std::ostream& operator<<(std::ostream& os, const Error& error)
{
    os << error.condition();
    const ErrorExtension* extension = error.extension();
    if (extension)
    {
        extension->operator<<(os);
    }
    return os;
}

void ThrowIf(const Error& error)
{
    if (error)
    {
        const char* file = nullptr;
        int line = -1;
        bool found = error.tryGetOrigin(file, line);
        if (found)
        {
            throw Exception(error.condition(), file, line);
        }
        else
        {
            throw Exception(error.condition(), __FILE__, __LINE__);
        }
    }
}

}
