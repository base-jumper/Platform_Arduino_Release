#ifndef STRINGMANIP_H_
#define STRINGMANIP_H_

namespace BaseJumper
{
	inline bool is_empty(char* str)
	{
		return (*str == '\0');
	}
	
	inline void set_empty(char* str)
	{
		*str = '\0';
	}

	bool parse_uint8(char* str, ARG_OUT uint8_t& result);
	
	// take up to but not including delimiter. delimiter is then skipped.
	bool take_until(ARG_INOUT char*& str, char delim, uint8_t max_len, ARG_OUT char* result);
	
	bool take_word(ARG_INOUT char*& str_in, uint8_t max_len, ARG_OUT char* result);
	
	void drop_while(ARG_INOUT char*& str, bool (*predicate)(char));
	
	bool is_alpha(char c);
	
	void process_backspaces(char *str);
	
	// returns true only if some whiespace was actually dropped
	bool drop_leading_spaces(ARG_INOUT char*& str);
	
	void drop_trailing_spaces(char* str);
	
	bool drop_leading(ARG_INOUT char*& str, char c);
	
	void delete_all_spaces(ARG_INOUT char*& str);
	
	bool strings_equal(const char* x, const char* y);
	
	bool skip_exact(ARG_INOUT char*& str, const char* substr);
	
	uint64_t hash(const char* s);
	
	size_t count_chars(const char* str, char c);
	
	// expected input: function(arg1, arg2, arg3, ..)
	bool take_function_call(
		ARG_INOUT char*& str,
		size_t max_name_len, ARG_OUT char* name,
		size_t min_args, size_t max_args, const size_t* max_arg_lens, 
		ARG_OUT size_t& args_len, ARG_OUT char** args);

	// expected input: arg1, arg2, arg3, etc
	bool take_arg_list(
		ARG_INOUT char*& str, 
		size_t min_args, size_t max_args, const size_t* max_arg_lens, 
		ARG_OUT size_t& args_len, ARG_OUT char** args);

	template <typename T>
	int compare_nums(T x, T y)
	{
		if (x < y)
			return -1;
		else if (x == y)
			return 0;
		else
			return 1;
	}
}

#endif /* STRINGMANIP_H_ */
