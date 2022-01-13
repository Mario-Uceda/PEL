   #ifndef TERMINAL_HPP_CPP_DGVERGEL_LIBRARY
   #define TERMINAL_HPP_CPP_DGVERGEL_LIBRARY

   /*
      terminal.hpp | A C++20 library to make coding with std::cin easier
      ------------------------------------------------------------------------------
      MIT License

      Copyright (c) 2020 Daniel Gómez Vergel
      
      Permission is hereby granted, free of charge, to any person obtaining a copy
      of this software and associated documentation files (the "Software"), to deal
      in the Software without restriction, including without limitation the rights
      to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
      copies of the Software, and to permit persons to whom the Software is
      furnished to do so, subject to the following conditions:

      The above copyright notice and this permission notice shall be included in all
      copies or substantial portions of the Software.

      THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
      IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
      FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
      AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
      LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
      OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
      SOFTWARE.
   */

   #include <concepts>
   #include <iostream> 
   #include <functional> 
   #include <sstream> 
   #include <string> 
   #include <string_view>
   #include <fmt/core.h> // {fmt}lib - Text formatting

   namespace terminal {

      namespace detail {
         class Set_exceptions_policy {
            std::ios_base::iostate old_policy_;
         public:
            explicit Set_exceptions_policy() : old_policy_{std::cin.exceptions()}
            {
               std::cin.exceptions(std::ios::badbit | std::ios::failbit);
            }
            ~Set_exceptions_policy() { std::cin.exceptions(old_policy_); }
         };

         template<typename T>
         concept Readable = requires (T& value_to_read) {
            { std::cin >> value_to_read } -> std::same_as<std::istream&>;
         };
      } // detail NAMESPACE
      
      struct No_constraints {
         template<typename T>
         auto operator()(T const&) const { return true; }
      }; 

      template<typename T, typename Cond = No_constraints>
         requires detail::Readable<T>
              and std::predicate<Cond, T>
      void prompt(std::string_view message, T& value, Cond cond = Cond{}) 
      {
         auto const _ = detail::Set_exceptions_policy{};
         
         fmt::print(message);
  
         auto const invalid_input_warning = "--->[invalid input] try again: ";
         auto input = std::string{};
         while (std::getline(std::cin, input)) { 
            if constexpr (std::same_as<std::string, T>) {
               if (std::invoke(cond, input)) {
                  value = input;  
                  break;
               }
               else
                  fmt::print(invalid_input_warning);
            }
            else {
               auto c = char{}; 
               auto strm = std::stringstream{input}; 
               if (strm >> value and !(strm >> c) and std::invoke(cond, value))
                  break; 
               else
                  fmt::print(invalid_input_warning);
            } 
         }
      }

      template<typename T, typename Cond = No_constraints>
         requires detail::Readable<T>
              and std::default_initializable<T>
              and std::predicate<Cond, T>
      [[nodiscard]] auto prompt_init(std::string_view message, Cond cond = Cond{}) -> T
      {
         auto value = T{};
         prompt(message, value, cond);
         return value;
      }

      template<typename T, typename Cond = No_constraints>
         requires detail::Readable<T>
              and std::predicate<Cond, T>
      [[nodiscard]] auto prompt_loop(std::string_view message,
                                     T& value,
                                     Cond cond = Cond{},
                                     std::string_view sentinel = "<end>") -> bool 
      {
         auto const _ = detail::Set_exceptions_policy{};
         
         fmt::print(message);

         auto const invalid_input_warning = "--->[invalid input] try again: ";
         auto input = std::string{};
         while (std::getline(std::cin, input) and input != sentinel) { 
            if constexpr (std::same_as<std::string, T>) {
               if (std::invoke(cond, input)) {
                  value = input;  
                  return true;
               }
               else
                  fmt::print(invalid_input_warning);
            }
            else {
               auto c = char{}; 
               auto strm = std::stringstream{input}; 
               if (strm >> value and !(strm >> c) and std::invoke(cond, value))
                  return true; 
               else
                  fmt::print(invalid_input_warning); 
            } 
         }
         return false; 
      }

   } // terminal NAMESPACE

   #endif