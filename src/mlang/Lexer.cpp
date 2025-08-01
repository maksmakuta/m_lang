#include "Lexer.hpp"

#include <map>

namespace mlang {

    const auto reserved = std::map<std::string,Lexem>{
        {"fn"       ,FUNCTION   },
        {"enum"     ,ENUM       },
        {"struct"   ,STRUCT     },
        {"interface",INTERFACE  },
        {"class"    ,CLASS      },
        {"abstract" ,ABSTRACT   },
        {"pub"      ,PUBLIC     },
        {"priv"     ,PRIVATE    },
        {"prot"     ,PROTECTED  },
        {"override" ,OVERRIDE   },
        {"val"      ,VAL        },
        {"var"      ,VAR        },
        {"for"      ,FOR        },
        {"while"    ,WHILE      },
        {"do"       ,DO         },
        {"match"    ,MATCH      },
        {"loop"     ,LOOP       },
        {"if"       ,IF         },
        {"else"     ,ELSE       },
        {"import"   ,IMPORT     },
        {"return"   ,RETURN     },
        {"next"     ,NEXT       },
        {"stop"     ,STOP       },
        {"in"       ,IN         }
    };

    std::vector<Token> Lexer::tokenize(const std::string& input) {
        source = input;
        index = 0;

        std::vector<Token> tokens;
        if (input.empty()) {
            return tokens;
        }

        const auto put = [&tokens, this](const Lexem& l) {
            tokens.emplace_back(l,"", Position{line,static_cast<int>(index)});
        };

        while(index < source.size()) {
            switch (source[index]) {
                case '+': if(isNext('+')) put(INC); else isNext('=') ? put(PLUS_EQ) : put(PLUS); break;
                case '-': if(isNext('-')) put(DEC); else isNext('=') ? put(MINUS_EQ    ) : put(MINUS   ); break;
                case '*': isNext('=') ? put(MULTIPLY_EQ ) : put(MULTIPLY); break;
                case '/':
                    if (isNext('/')) {
                        return tokens;
                    }
                    isNext('=') ? put(DIVIDE_EQ   ) : put(DIVIDE  );
                    break;
                case '%': isNext('=') ? put(MODULO_EQ   ) : put(MODULO  ); break;
                case '~': isNext('=') ? put(INV_EQ      ) : put(INV     ); break;
                case '!': isNext('=') ? put(NOT_EQ      ) : put(NOT     ); break;
                case '|': isNext('=') ? put(OR_EQ       ) : put(OR      ); break;
                case '&': isNext('=') ? put(AND_EQ      ) : put(AND     ); break;
                case '^': isNext('=') ? put(XOR_EQ      ) : put(XOR     ); break;
                case '=': isNext('=') ? put(EQUAL       ) : put(ASSIGN  ); break;

                case '{': put(LBRACE     ); break;
                case '[': put(LBRACK     ); break;
                case '(': put(LPAREN     ); break;
                case '}': put(RBRACE     ); break;
                case ']': put(RBRACK     ); break;
                case ')': put(RPAREN     ); break;

                // < << <= <<=
                case '<':
                    if (isNext('<')) {
                        if (isNext('=')) {
                            put(SHL_EQ);
                        } else put(SHL);
                    }else {
                        if(isNext('=')) {
                            put(LESS_EQ);
                        } else put(LESS);
                    }
                    break;
                case '>':
                    if (isNext('>')) {
                        if (isNext('=')) {
                            put(SHR_EQ);
                        }else put(SHR);
                    }
                    else {
                        if (isNext('=')) {
                            put(GREAT_EQ);
                        } else put(GREAT);
                    }
                    break;

                case ':': put(COLON     ); break;
                case ',': put(COMMA     ); break;
                case '.': put(DOT       ); break;

                case '\'':
                    tokens.push_back(getChar());
                    index++;
                    break;

                case '"':
                    tokens.push_back(getString());
                    index++;
                    break;

                default: {
                    if (std::isalpha(source[index]) || source[index] == '_') {
                        tokens.push_back(getIdentifier());
                    }else if (std::isxdigit(source[index])) {
                        tokens.push_back(getNumber());
                    }
                }
                break;
            }
            index++;
        }

        return tokens;
    }

    Token Lexer::getNumber(){
        auto type = INTEGER;
        const auto start = index;
        std::string val;
        while (std::isdigit(source[index])) {
            val += source[index];
            index++;
        }
        if (source[index] == '.') {
            val += source[index];
            type = REAL;
            index++;
            while (std::isdigit(source[index])) {
                val += source[index];
                index++;
            }
        }
        return Token{type, val, Position{line, static_cast<int>(start) + 1}};
    }

    Token Lexer::getString(){
        const auto start = index;
        index++;
        std::string val;
        while (source[index] != '"' && source[index] != '\0') {
            val += source[index];
            index++;
        }
        index++;
        return Token{STRING, val, Position{line, static_cast<int>(start) + 1}};
    }

    Token Lexer::getChar(){
        const auto start = index;
        index++;
        const auto val = source[index];
        index++;
        return Token{CHAR, std::string() + val, Position{line, static_cast<int>(start) + 1}};
    }

    Token Lexer::getIdentifier() {
        const auto start = index;
        std::string val;
        while (std::isalnum(source[index]) || source[index] == '_') {
            val += source[index];
            index++;
        }
        index--;
        if (reserved.contains(val)) {
            return Token{reserved.at(val),val,Position{line, static_cast<int>(start) + 1}};
        }
        return Token{IDENTIFIER, val, Position{line, static_cast<int>(start) + 1}};
    }

    bool Lexer::isNext(const char c) {
        if (source[index + 1] == c) {
            index++;
            return true;
        }
        return false;
    }
} // mlang