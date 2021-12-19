#pragma once

namespace exceptions {
	class MyException : public std::exception {
	public:
		MyException(const std::string& exception) noexcept : _text(exception + '\n') {}
		virtual const char* what() const override {
			return _text.data();
		}

		virtual ~MyException() noexcept = 0 {}

	protected:
		std::string _text; // An outsider must not interfere
	};

	class ArgumentException : public MyException {
	public:
		ArgumentException(const std::string& exception) noexcept : MyException(exception) {}
	};

	class DatabaseException : public MyException {
	public:
		DatabaseException(const std::string& exception) noexcept : MyException(exception) {}
	};

	class InvalidCastException : public MyException {
	public:
		InvalidCastException(const std::string& exception) noexcept : MyException(exception) {}
	};

	class NullReferenceException : public MyException {
	public:
		NullReferenceException(const std::string& exception) noexcept : MyException(exception) {}
	};

	class OutOfRangeException : public MyException {
	public:
		OutOfRangeException(const std::string& exception) noexcept : MyException(exception) {}
	};
}
