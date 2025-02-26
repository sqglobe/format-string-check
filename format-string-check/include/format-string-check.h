#pragma once

#include <algorithm>
#include <array>
#include <sstream>
#include <string_view>

// Wrapper for c-string
// Enable c-string as a template parameter
template <size_t N> struct Format {
  consteval Format(const char (&str)[N]) { std::copy_n(str, N, format); }

  char format[N];
  constexpr static std::size_t Size = N;
};

// Class with the main logic about formatting
// Responcible for formatcorrectness check
// and following formatting
template <Format Fmt, typename... Args> class Formatter {
    struct FormatSplitResult {
        bool isValid;
        bool finished;
        std::string_view beforePlaceholder;
        std::string_view afterPlaceholder;
    };

public:
  consteval Formatter() {
      m_valid = parseFormatString(std::string_view(Fmt.format));
  }

public:
  // Return `true` if format valid
  constexpr bool isValid() const { return m_valid; }

  // Format list of arguments into the string
  std::string format(const Args &...args) const {
    std::stringstream ss;

    if constexpr (sizeof...(Args) > 0) {
      [&]<std::size_t... Indexes>(std::index_sequence<Indexes...>) {
        auto oneArg = [&ss, this](std::size_t i, const auto &arg) {
          ss << m_formatSlices[i] << arg;
        };
        (oneArg(Indexes, std::cref(args)), ...);
      }(std::index_sequence_for<Args...>{});
    }

    ss << m_formatSlices.back();
    return ss.str();
  }

  private:
  constexpr FormatSplitResult findPlaceHolder(std::string_view s){
      auto it = std::find_if(s.begin(), s.end(),
                             [](char c) { return c == '}' || c == '{'; });
      if (it == s.end()) {
          return {.isValid = true, .finished = true, .beforePlaceholder = s};
      } else if (*it == '}') {
          return {.isValid = false};
      } else {
          auto beforePlaceholder = std::string_view(s.begin(), it);
          ++it;
          if (it == s.end() || *it != '}') {
              return {.isValid = false};
          }
          ++it;
          return {.isValid = true, .finished = false, .beforePlaceholder = beforePlaceholder, .afterPlaceholder = std::string_view(it, s.end())};
      }
  }
  consteval bool parseFormatString(std::string_view format){
      for(auto saveAt = m_formatSlices.begin(); saveAt != m_formatSlices.end(); ++saveAt) {
          auto [isValid, finished, beforePlaceholder, afterPlaceholder]= findPlaceHolder(format);
          if(!isValid) {
              return false;
          }
          *saveAt = beforePlaceholder;
          format = afterPlaceholder;
          if(finished){
              ++saveAt;
              return saveAt == m_formatSlices.end();
          }
      }
      return false;
  }

private:
  std::array<std::string_view, 1 + sizeof...(Args)> m_formatSlices;
  bool m_valid;
};

// Format list of `args` into a string
// corresponding to the provided format `Fmt`
template <Format Fmt, typename... Args>
std::string format(const Args &...args) {
  constexpr auto formatter = Formatter<Fmt, Args...>{};
  static_assert(formatter.isValid(), "Format is invalid");
  return formatter.format(args...);
}
