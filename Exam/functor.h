#pragma once

class ReplaceStringSymbol {
public:
	ReplaceStringSymbol(const char& data) : symbol(data) {}
	bool operator()(const char& data) { return(data == symbol) ? true : false; }

private:
	char symbol;

};
