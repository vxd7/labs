#pragma once

enum c_color {
	BLACK   = 30,
	RED     = 31,
	GREEN   = 32,
	YELLOW  = 33,
	BLUE    = 34,
	MAGENTA = 35,
	CYAN    = 36,
	LGRAY   = 37,
	DGRAY   = 90,
	LRED    = 91,
	LGREEN  = 92,
	LYELLOW = 93,
	LBLUE   = 36,
	LCYAN   = 96
};

enum c_mod {
	NORMAL = 0,
	BOLD   = 1,
	DIM    = 2,
	UNDERL = 4
};

std::string getCode(c_color _color, c_mod _mod)
{
	return ("\033[" + _mod + ';' + _color + 'm');
}

std::string applyColor(const std::string str, c_color _color, c_mod _mod = NORMAL)
{
	std::ostringstream os;

	os << "\033[" << _mod << ';' << _color << 'm' << str << "\033[0m";
	return os.str();
}
