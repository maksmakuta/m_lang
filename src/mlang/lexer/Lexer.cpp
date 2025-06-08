#include "mlang/lexer/Lexer.hpp"

#include <unordered_map>

namespace mlang::lexer {

    const std::unordered_map<std::string, Token> reserved = {
        {"abstract"     , Token::Abstract   },
        {"class"        , Token::Class      },
        {"interface"    , Token::Interface  },
        {"fn"           , Token::Function   },
        {"if"           , Token::If         },
        {"import"       , Token::Import     },
        {"else"         , Token::Else       },
        {"for"          , Token::For        },
        {"match"        , Token::Match      },
        {"while"        , Token::While      },
        {"loop"         , Token::Loop       },
        {"next"         , Token::Next       },
        {"stop"         , Token::Stop       },
        {"let"          , Token::Let        },
        {"const"        , Token::Const      },
        {"override"     , Token::Override   },
        {"constructor"  , Token::Constructor},
        {"super"        , Token::Super      },
        {"true"         , Token::True       },
        {"false"        , Token::False      },
        {"null"         , Token::Null       },
        {"pub"          , Token::Pub        },
        {"prot"         , Token::Prot       },
        {"priv"         , Token::Priv       },
        {"as"           , Token::As         },
        {"is"           , Token::Is         },
        {"return"       , Token::Return     },

        //operator words

        {"and"          , Token::And        },
        {"or"           , Token::Or         },
        {"xor"          , Token::Xor        },
        {"shl"          , Token::Shl        },
        {"shr"          , Token::Shr        },

    };

    Lexems lex(const std::string& raw) {
        auto l = Lexems();
        size_t i = 0;

        const auto push = [&l](Token t, const std::string& v) {
            l.emplace_back(v,t);
        };

        while (i < raw.size()) {
            switch (raw[i]) {
                case '+': push(Token::Plus      ,"+"); break;
                case '-': push(Token::Minus     ,"-"); break;
                case '*': push(Token::Mul       ,"*"); break;
                case '/': push(Token::Div       ,"/"); break;
                case '%': push(Token::Mod       ,"%"); break;
                case '^': push(Token::Xor       ,"^"); break;
                case '&': push(Token::And       ,"&"); break;
                case '|': push(Token::Or        ,"|"); break;
                case '<': push(Token::Less      ,"<"); break;
                case '>': push(Token::More      ,">"); break;
                case '=': push(Token::Eq        ,"="); break;
                case '!': push(Token::Not       ,"!"); break;
                case '~': push(Token::Inv       ,"~"); break;
                case '(': push(Token::BracketI  ,"("); break;
                case ')': push(Token::BracketO  ,")"); break;
                case '{': push(Token::BracketCI ,"{"); break;
                case '}': push(Token::BracketCO ,"}"); break;
                case '[': push(Token::BracketSI ,"["); break;
                case ']': push(Token::BracketSO ,"]"); break;
                case ':': push(Token::Colon     ,":"); break;
                case '?': push(Token::Question  ,"?"); break;
                case '.': push(Token::Dot       ,"."); break;
                case ',': push(Token::Comma     ,","); break;
                case '"': {
                    const auto start = i;
                    while (i < raw.size() && raw[i] != '"') {
                        ++i;
                    }
                    push(Token::String, raw.substr(start,i - start));
                }
                break;
                case '\'': {
                    const auto start = i;
                    while (i < raw.size() && raw[i] != '\'') {
                        ++i;
                    }
                    push(Token::Char, raw.substr(start,i - start));
                }
                break;
                default: {
                    const auto start = i;
                    if (i < raw.size() && std::isdigit(raw[i])) {
                        bool hasPoint = false;

                        while (i < raw.size() && (std::isdigit(raw[i]) || (!hasPoint && raw[i] == '.'))) {
                            if (raw[i] == '.') hasPoint = true;
                            ++i;
                        }

                        if (i < raw.size() && (raw[i] == 'e' || raw[i] == 'E')) {
                            ++i;
                            if (i < raw.size() && (raw[i] == '+' || raw[i] == '-')) {
                                ++i;
                            }
                            while (i < raw.size() && std::isdigit(raw[i])) {
                                ++i;
                            }
                        }

                        if (i < raw.size() && (raw[i] == 'f' || raw[i] == 'F')) {
                            ++i;
                        }

                        push(Token::Number,raw.substr(start,i - start));
                    } else if (i < raw.size() && (std::isalpha(raw[i]) || raw[i] == '_')) {
                        while (std::isalnum(raw[i]) || raw[i] == '_') {
                            ++i;
                        }
                        if (auto result = raw.substr(start,i - start); reserved.contains(result)) {
                            push(reserved.at(result),result);
                        }else {
                            push(Token::Identifier,result);
                        }
                    }
                }
                break;
            }
            i++;
        }
        return l;
    }

}
