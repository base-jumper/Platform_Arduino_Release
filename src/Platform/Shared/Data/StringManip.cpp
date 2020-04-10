#include "../../Shared/SharedCommon.h"
#include "../../Shared/Data/StringManip.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

namespace BaseJumper
{
	 bool parse_uint8(char* str, ARG_OUT uint8_t& result)
	 {
		 auto x = atoi(str);
		 // disambiguate between error and number zero (wtf was the person that wrote atoi() thinking?)
		 if ((x == 0) && (str[0] != '0'))
		 return false;
		 if (x < 0)
		 return false;
		 result = static_cast<uint8_t>(x);
		 return true;
	 }
	
	  bool take_until(ARG_INOUT char*& str, char delim, uint8_t max_len, ARG_OUT char* result)
	 {
		 uint16_t i = 0;
		 while ((str[i]) && (i < max_len))
		 {
			 if (str[i] == delim)
			 {
				 result[i] = '\0';
				 str = &str[i+1]; // advance past the delimiter
				 return true;
			 }
			 result[i] = str[i];
			 i++;
		 }
		 result[i] = '\0';
		 return false;
	 }

	 // A 'word' can contain only the following characters: [a-z],[A-Z],[0-9],_.
	 // The 'word' ends when any other character is first encountered.
	 bool take_word(ARG_INOUT char*& str_in, uint8_t max_len, ARG_OUT char* result)
	 {
		char* str = str_in;
		size_t len = 0;
		while (isalnum(*str) || (*str == '_'))
		{
			str++;
			len = str-str_in;
			if (len > max_len-1)
			{
				return false;
			}
		}
		if (len > 0)
		{
			memcpy(result, str_in, len);
			result[len] = '\0';
			str_in = str;
			return true;
		}
		else
		{
			return false;
		}
	 }
	
	  void drop_while(ARG_INOUT char*& str, bool (*predicate)(char))
	 {
		 while ((*str) && predicate(*str))
			str++;
	 }
	
	 bool is_alpha(char c)
	 {
		 return (isalpha(static_cast<int>(c)) != 0);
	 }
	
	 void process_backspaces(char *str)
	 {
		 char *src, *dst;
		 for (src = dst = str; *src != '\0'; src++) {
			 if ((*src == '\b') || (*src == 127)) {
				 if (dst != str) {
					 dst--;
				 }
				 continue;
			 }
			 *dst++ = *src;
		 }
		 *dst = '\0';
	 }
	
	 bool drop_leading_spaces(ARG_INOUT char*& str)
	 {
		bool result = isspace(*str);
		while (isspace(*str))
			str++;
		return result;
	 }

	void drop_trailing_spaces(char* str)
	{
		auto len = strlen(str);
		while ((len > 0) && isspace(str[len-1]))
		{
			str[len-1] = '\0';
			len--;
		}
	}
	
	 bool drop_leading(ARG_INOUT char*& str, char c)
	 {
		if (str[0] == c)
		{
			str++;
			return true;
		}
		else
		{
			return false;
		}
	 }
	
	 void delete_all_spaces(ARG_INOUT char*& str)
	 {
		size_t r = 0;
		size_t w = 0;
		while (str[r])
		{
			if (!isspace(str[r]))
			{
				str[w] = str[r];
				w++;
			}
			r++;
		}
		str[w] = '\0';
	 }

	 bool strings_equal(const char* x, const char* y)
	 {
		return strcmp(x,y) == 0;
	 }

	 bool skip_exact(ARG_INOUT char*& str, const char* substr)
	 {
		auto len = strlen(substr);
		if (strncmp(str, substr, len) == 0)
		{
			str += len;
			return true;
		}
		return false;
	 }

	size_t count_chars(const char* str, char c)
	{
		size_t result = 0;
		while (*str != '\0')
		{
			if (*str == c)
				result++;
			str++;
		}
		return result;
	}

	bool take_function_call(
		ARG_INOUT char*& str,
		size_t max_name_len, ARG_OUT char* name,
		size_t min_args, size_t max_args, const size_t* max_arg_lens, 
		ARG_OUT size_t& args_len, ARG_OUT char** args)
	{
		char* remaining = str;
		if (!take_word(ARG_INOUT remaining, max_name_len, ARG_OUT name))
			return false;
		drop_leading_spaces(ARG_INOUT remaining);
		if (!skip_exact(ARG_INOUT remaining, "("))
			return false;
		drop_leading_spaces(ARG_INOUT remaining);
		constexpr size_t max_args_text_len = 100;
		char args_text[max_args_text_len];
		char* p_args_text = args_text;
		if (!take_until(ARG_INOUT remaining, ')', max_args_text_len, ARG_OUT args_text))
			return false;
		if (!take_arg_list(
			ARG_INOUT p_args_text, 
			min_args, max_args, max_arg_lens, 
			ARG_OUT args_len, ARG_OUT args))
			return false;
		if (strlen(p_args_text) > 0)
			return false; // some parameters were not consumed.

		str = remaining;
		return true;
	}

	bool take_arg_list(
		ARG_INOUT char*& str, 
		size_t min_args, size_t max_args, const size_t* max_arg_lens, 
		ARG_OUT size_t& args_len, ARG_OUT char** args)
	{
		char* remaining = str;

		// handle empty case
		drop_leading_spaces(ARG_INOUT remaining);
		if (is_empty(remaining))
		{
			args_len = 0;
			return (args_len >= min_args);
		}

		// handle general case (non-empty)
		size_t i = 0;
		bool comma_found = false;
		do
		{
			comma_found = take_until(ARG_INOUT remaining, ',', max_arg_lens[i], &args[i][0]);
			drop_trailing_spaces(&args[i][0]);
			i++;
			drop_leading_spaces(ARG_INOUT remaining);
		} while (comma_found && (i < max_args));
		if (!comma_found)
		{
			// end of argument list was hit (instead of a comma).
			// advance remaining ptr to end of string.
			remaining += strlen(remaining);
		}
		bool success = ((i >= min_args) && (i <= max_args));
		if (success)
		{
			str = remaining;
			args_len = i;
		}
		return success;
	}

	uint64_t hash(const char* s) 
	{
		const int p = 31;
		const int m = 1e9 + 9;
		uint64_t hash_value = 0;
		uint64_t p_pow = 1;
		while (*s != '\0')
		{
			hash_value = (hash_value + (*s - 'a' + 1) * p_pow) % m;
			p_pow = (p_pow * p) % m;
			s++;
		}
		return hash_value;
	}
}
