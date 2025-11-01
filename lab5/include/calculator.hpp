#pragma once
#include <cstddef> // size_t

namespace basecalc {

    //  перечесление констант типа int 
    enum : int { BASE_BIN = 2, BASE_OCT = 8, BASE_DEC = 10, BASE_HEX = 16 };


    bool is_supported_base(int base) noexcept;


    bool clean_input(const char* in, char* out_buf, std::size_t out_buf_size) noexcept;


    bool validate_digits_for_base(const char* s, int base) noexcept;


    bool from_base_string(const char* s, int base, long long* out_value) noexcept;


    bool to_base_string(long long value, int base, char* out_buf, std::size_t out_buf_size) noexcept;

} // namespace basecalc
