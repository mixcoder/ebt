#include "json.h"
#include "string.h"

namespace ebt {

    namespace json {

        void dump(std::string const& str, std::ostream& os)
        {
            os << '"' << replace(str, "\"", "\\\"") << '"';
        }

        void dump(int i, std::ostream& os)
        {
            os << i;
        }

        void dump(double d, std::ostream& os)
        {
            os << d;
        }

        json_parser_exception::json_parser_exception(std::string msg)
            : msg_(msg)
        {}

        char const* json_parser_exception::what() const noexcept
        {
            return msg_.c_str();
        }

        double json_parser<double>::parse(std::istream& is)
        {
            std::string s;

            std::string non_zeros = "123456789";
            std::string digits = "0123456789";

            if (is.peek() == '+') {
                s.append(1, is.get());
            } else if (is.peek() == '-') {
                s.append(1, '-');
            }

            if (non_zeros.find(is.peek()) != std::string::npos) {
                s.append(1, is.get());
            }

            while (digits.find(is.peek()) != std::string::npos) {
                s.append(1, is.get());
            }

            if (is.peek() == '.') {
                s.append(1, is.get());

                while (digits.find(is.peek()) != std::string::npos) {
                    s.append(1, is.get());
                }
            }

            if (is.peek() == 'e') {
                s.append(1, is.get());

                if (is.peek() == '+') {
                    s.append(1, is.get());
                } else if (is.peek() == '-') {
                    s.append(1, is.get());
                }

                while (digits.find(is.peek()) != std::string::npos) {
                    s.append(1, is.get());
                }
            }

            return std::stod(s);
        }

        int json_parser<int>::parse(std::istream& is)
        {
            std::string s;

            std::string non_zeros = "123456789";
            std::string digits = "0123456789";

            if (is.peek() == '+') {
                is.get();
            } else if (is.peek() == '-') {
                s.append(1, '-');
            }

            if (non_zeros.find(is.peek()) != std::string::npos) {
                s.append(1, is.get());
            }

            while (digits.find(is.peek()) != std::string::npos) {
                s.append(1, is.get());
            }

            return std::stoi(s);
        }

        std::string json_parser<std::string>::parse(std::istream& is)
        {
            std::string result;
            expect(is, '"');
            is.get();
            char c[2];
            c[1] = '\0';
            while (is.peek() != '"') {
                if (is.peek() == '\\') {
                    is.get();
                    if (is.peek() != '"' && is.peek() != '\\') {
                        throw json_parser_exception(
                            "can only escape \" and \\");
                    }
                }
                c[0] = is.get();
                result.append(std::string(c));
            }
            is.get();
            return result;
        }

        void expect(std::istream& is, char c)
        {
            if (is.peek() != c) {
                throw json_parser_exception(format(
                    "expected: <{}> actual: <{}> ", c, is.peek()));
            }
        }

        void whitespace(std::istream& is)
        {
            while (is.peek() == ' '
                    || is.peek() == '\t'
                    || is.peek() == '\n') {
                is.get();
            }
        }

    }
}