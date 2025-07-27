#include "Lexer.hpp"

#include <map>

namespace mlang {

    static auto reserved = std::map<std::string, Lexem>{
        {"fn"       ,FUNCTION},
        {"var"      ,VAR},
        {"val"      ,VAL},
        {"true"     ,TRUE},
        {"false"    ,FALSE},
        {"import"   ,IMPORT},
        {"struct"   ,STRUCT},
    };

    std::vector<Token> tokenize(const std::string &input) {
        std::vector<Token> tokens;
        auto i = 0;
        std::pair pos = {1,1};

        const auto push = [&pos, &tokens](Lexem l) {
            tokens.emplace_back(l,"",pos);
        };

        const auto checkNext = [&i, &input, &pos](char c) {
            if (input[i+1] == c) {
                i++;
                return true;
            }
            return false;
        };

        while (i < input.size()) {
            const char c = input[i];
            if (c == '\n') {
                pos.first++;
                pos.second = 1;
            }
            switch (c) {
                case ' ':
                case '\n':
                case '\t':
                case '\r':
                    break;
                case ':': push(COLON); break;
                case '.': push(DOT); break;
                case ',': push(COMMA); break;
                case '+': checkNext('=') ? push(PLUS_EQ     ) : push(PLUS    ); break;
                case '-': checkNext('=') ? push(MINUS_EQ    ) : push(MINUS   ); break;
                case '*': checkNext('=') ? push(MULTIPLY_EQ ) : push(MULTIPLY); break;
                case '/': {
                        if (input[i+1] == '/') {
                            while (input[i+1] != '\n') {
                                i++;
                            }
                        }else{
                            checkNext('=') ? push(DIVIDE_EQ) : push(DIVIDE);
                        }
                    }
                    break;
                case '%': checkNext('=') ? push(MOD_EQ      ) : push(MOD     ); break;
                case '|': checkNext('=') ? push(OR_EQ   ) : push(OR ); break;
                case '&': checkNext('=') ? push(AND_EQ  ) : push(AND); break;
                case '^': checkNext('=') ? push(XOR_EQ  ) : push(XOR); break;
                case '~': checkNext('=') ? push(INV_EQ  ) : push(INV); break;
                case '!': checkNext('=') ? push(NOT_EQ  ) : push(NOT); break;
                case '<': checkNext('=') ? push(LESS_EQ  ) : push(LESS); break;
                case '>': checkNext('=') ? push(MORE_EQ  ) : push(MORE); break;
                case '(': push(PAREN_LEFT); break;
                case ')': push(PAREN_RIGHT); break;
                case '{': push(BRACE_LEFT); break;
                case '}': push(BRACE_RIGHT); break;
                case '[': push(BRACKET_LEFT); break;
                case ']': push(BRACKET_RIGHT); break;
                case '=': push(ASSIGN); break;
                case '"':{
                    const auto start = i;
                    i++;
                    while (input[i] != '"') {
                        i++;
                    }
                    i++;
                    tokens.emplace_back(STRING, input.substr(start, i-start), pos);
                    i--;
                }
                default: {
                    if (std::isalpha(c) || c == '_') {
                        const auto start = i;
                        while (isalnum(input[i]) || input[i] == '_') {
                            i++;
                            pos.second++;
                        }
                        if (std::string value = input.substr(start, i-start); reserved.contains(value)) {
                            push(reserved.at(value));
                        }else {
                            tokens.emplace_back(IDENTIFIER, value, pos);
                        }
                        i--;
                    }
                    if (std::isdigit(c)) {
                        bool is_real = false;
                        const auto start = i;
                        while (isxdigit(input[i])) {
                            i++;
                        }
                        if (input[i] == '.') {
                            is_real = true;
                            i++;
                            while (isxdigit(input[i])) {
                                i++;
                            }
                        }
                        tokens.emplace_back(is_real ? REAL : INT, input.substr(start, i-start), pos);
                    }
                }
            }

            i++;
            pos.second++;
        }

        return tokens;
    }

}