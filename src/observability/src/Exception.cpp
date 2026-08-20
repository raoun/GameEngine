#include "Exception.hpp"

namespace observability
{
	Exception::Exception(std::wstring message, std::wstring fileName, std::wstring location)
				: m_message( std::move(message)),
				  m_fileName( std::move(fileName) ),
				  m_location( std::move(location) )
	{}
	std::wstring Exception::getMessage() const
	{
		return m_message;
	}
	std::wstring Exception::getFileName() const
	{
		return m_fileName;
	}
	std::wstring Exception::getLocation() const
	{
		return m_location;
	}
	std::wstring Exception::what() const
	{
		std::wstring message( L"Exception in '");
		message.append(m_location)
		.append(L"' (")
		.append(m_fileName)
		.append(L"): ")
		.append(m_message);
		return message;
	}
}