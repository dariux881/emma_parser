template<typename T>
inline T Utils::stringToNumber(string str) {
	T result;

	result = (T)atof( str.c_str() );

	return result;
}
