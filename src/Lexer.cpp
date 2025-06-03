#include "mlang/Lexer.hpp"

#include <iostream>
#include <map>

namespace mlang {

    static std::map<std::string, Token> keywords{
        {"let"      ,Token::Let      },
        {"fn"       ,Token::Function },
        {"class"    ,Token::Class    },
        {"interface",Token::Interface},
        {"struct"   ,Token::Struct   },
        {"abstract" ,Token::Abstract },
        {"if"       ,Token::If       },
        {"else"     ,Token::Else     },
        {"match"    ,Token::Match    },
        {"return"   ,Token::Return   },
        {"const"    ,Token::Const    },
        {"null"     ,Token::Null     },
        {"true"     ,Token::True     },
        {"false"    ,Token::False    },
    };

    static std::map<std::string, Token> operators{
        {"+",   Token::Plus                 },
        {"-",   Token::Minus                },
        {"/",   Token::Divide               },
        {"*",   Token::Multiply             },
        {"%",   Token::Mod                  },
        {"!",   Token::Not                  },
        {"|",   Token::BitwiseOr            },
        {"&",   Token::BitwiseAnd           },
        {"^",   Token::Xor                  },
        {"||",  Token::Or                   },
        {"&&",  Token::And                  },
        {"~",   Token::Invert               },
        {"<<",  Token::ShiftLeft            },
        {">>",  Token::ShiftRight           },
        {"==",  Token::Equal                },
        {"<",   Token::Less                 },
        {">",   Token::Greater              },
        {"+=",  Token::PlusEqual            },
        {"-=",  Token::MinusEqual           },
        {"/=",  Token::DivideEqual          },
        {"*=",  Token::MultiplyEqual        },
        {"%=",  Token::ModEqual             },
        {"|=",  Token::OrEqual              },
        {"&=",  Token::AndEqual             },
        {"^=",  Token::XorEqual             },
        {"~=",  Token::InvertEqual          },
        {"<<=", Token::ShiftLeftEqual       },
        {">>=", Token::ShiftRightEqual      },
        {"!=",  Token::NotEqual             },
        {"<=",  Token::LessEqual            },
        {">=",  Token::GreaterEqual         },
        {".",   Token::Dot                  },
        {":",   Token::Colon                },
        {",",   Token::Comma                },
        {"(",   Token::BracketStart         },
        {")",   Token::BracketEnd           },
        {"[",   Token::BracketSquareStart   },
        {"]",   Token::BracketSquareEnd     },
        {"{",   Token::BracketCurlyStart    },
        {"}",   Token::BracketCurlyEnd      },
        {"=",   Token::Set                  },
    };

    bool isPunkt(const char c) {
        return std::string("~!+-*/%^&|<>{}[]()=:,.").find(c) != std::string::npos;
    }

    void Position::newline() {
        line++;
        column = 0;
    }

    Lexer::Lexer(std::string& buffer) : m_buffer(buffer), pos(1,0){}

    std::vector<Lexem> Lexer::toTokens() {
        std::vector<Lexem> tokens;
        while (pointer < m_buffer.size()) {
            skipWhitespace();
            char c = peek();
            if (std::isalpha(c) || c == '_') {
                tokens.push_back(lexIdentifierOrKeyword());
            } else if (std::isdigit(c)) {
                tokens.push_back(lexNumber());
            } else if (c == '"') {
                tokens.push_back(lexString());
            } else if (isPunkt(c)) {
                tokens.push_back(lexSymbol());
            } else {
                advance();
            }
        }
        tokens.emplace_back(Token::EndOfFile, "", pos);
        return tokens;
    }

    Lexem Lexer::lexIdentifierOrKeyword(){
        size_t start = pointer;
        while (std::isalnum(peek()) || peek() == '_') advance();
        std::string text = m_buffer.substr(start, pointer - start);

        if (keywords.contains(text)) {
            return Lexem(keywords[text], text, pos);
        }

        return Lexem(Token::Identifier, text, pos);
    }

    Lexem Lexer::lexNumber(){
        const size_t start = pointer;
        while (std::isdigit(peek())) advance();
        if (peek() == '.') {
            advance();
            while (std::isdigit(peek())) advance();
        }
        return Lexem(Token::Number, m_buffer.substr(start, pointer - start), pos);
    }

    Lexem Lexer::lexString(){
        advance();
        const size_t start = pointer;
        while (peek() != '"' && peek() != '\0') {
            if (peek() == '\n') pos.newline();
            advance();
        }
        const std::string content = m_buffer.substr(start, pointer - start);
        if (peek() == '"') advance();
        return Lexem(Token::String, content, pos);
    }

    Lexem Lexer::lexSymbol(){
        const size_t start = pointer;
        advance();
        const std::string content = m_buffer.substr(start, pointer - start);
        return Lexem(operators[content], content, pos);
    }

    char Lexer::peek() const{
        return pointer < m_buffer.size() ? m_buffer[pointer] : '\0';
    }

    char Lexer::advance(){
        pos.column++;
        return pointer < m_buffer.size() ? m_buffer[pointer++] : '\0';
    }

    bool Lexer::match(const char expected){
        if (peek() == expected) {
            ++pointer;
            return true;
        }
        return false;
    }

    void Lexer::skipWhitespace(){
        while (true) {
            char c = peek();
            if (c == ' ' || c == '\t' || c == '\r') {
                advance();
            } else if (c == '\n') {
                pos.newline();
                advance();
            } else if (c == '/' && m_buffer[pointer + 1] == '/') {
                while (peek() != '\n' && peek() != '\0') advance();
            } else if (c == '/' && m_buffer[pointer + 1] == '*') {
                advance(); advance(); // skip /*
                while (!(peek() == '*' && m_buffer[pointer + 1] == '/') && peek() != '\0') {
                    if (peek() == '\n') pos.newline();
                    advance();
                }
                if (peek() == '*') advance(); // *
                if (peek() == '/') advance(); // /
            } else {
                break;
            }
        }
    }


}
