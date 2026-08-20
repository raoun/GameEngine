#ifndef OBSERVABILITY_EXCEPTION_HPP
#define OBSERVABILITY_EXCEPTION_HPP

#include <string>

namespace observability
{
	class Exception
	{
	public:
		Exception(std::wstring message, std::wstring fileName, std::wstring location);
		std::wstring getMessage() const;
		std::wstring getFileName() const;
		std::wstring getLocation() const;

		std::wstring what() const;
		
	private:
		std::wstring m_message;
		std::wstring m_fileName;
		std::wstring m_location;
	};
}

#endif // OBSERVABILITY_EXCEPTION_HPP