/**
 *          Extra Credit Homework
 *          A simple command line calculator
 *                      by Fazekas Csaba
 *                         2023 04 26
*/
#include <cstdint>
#include <cstring>
#include <string>
#include <sstream>
#include <cctype>
#include <iostream>
#include <cassert>
#include <map>
#include <functional>
#include <cmath>

typedef unsigned int uint;

enum TokenType {
    SymbolToken,
    NumberToken,
    PlusOperationToken,
    MinusOperationToken,
    DivideOperationToken,
    MultiplyOperationToken,
    ExponentOperationToken,
    FactorialOperationToken,
    LeftParenToken,
    RightParenToken,
    CommaToken,
    Unknown,
    EOFToken,
};

const char *token_type_to_str(TokenType tt) {
    switch (tt) {
        case TokenType::SymbolToken:
            return "Symbol";

        case TokenType::NumberToken:
            return "Number";
        
        case TokenType::PlusOperationToken:
            return "+";
        
        case TokenType::MinusOperationToken:
            return "-";
        
        case TokenType::MultiplyOperationToken:
            return "*";
        
        case TokenType::DivideOperationToken:
            return "/";
        
        case TokenType::ExponentOperationToken:
            return "^";
        
        case TokenType::FactorialOperationToken:
            return "!";

        case TokenType::LeftParenToken:
            return "(";
        
        case TokenType::RightParenToken:
            return ")";

        case TokenType::CommaToken:
            return ",";
        
        case TokenType::Unknown:
            return "Unknown Token";
        
        case TokenType::EOFToken:
            return "EOF";

        default:
            assert(false && "Unhandled token case");
    }
    return "Unreachable";
}

std::ostream& operator<<(std::ostream &o, TokenType tt) {
    return o << token_type_to_str(tt);
}


typedef struct {
        // Line number on which the token starts. Starts at 1
        uint64_t line;
        // Column number on which the token starts. Starts at 1
        uint64_t column;
        // Actual position/index into the program. Starts at 0
        uint64_t pos;
} Pos;

std::ostream& operator<<(std::ostream& o, Pos pos) {
    o << pos.line << ":" << pos.column;
    return o;
}


class Token {
    public:
        TokenType type;

        union {
            double as_number;
            const char *as_str;
        };

        Pos start;
        Pos end;

        Token() { };

        Token(const Token& o) : type(o.type), start(o.start), end(o.end) {
            switch (o.type) {
                case TokenType::SymbolToken:
                    {
                        char *str = (char*) calloc(strlen(o.as_str)+1, sizeof(char));
                        std::strcpy(str, o.as_str);
                        as_str = str;
                        break;
                    }
                
                case TokenType::NumberToken:
                    as_number = o.as_number;
                    break;
                
                default:
                    break;
            }
        }

        Token(TokenType type, Pos start, Pos end) {
            this->type = type;
            this->start = start;
            this->end = end;
        }

        Token(TokenType type, const char *as_str, Pos start, Pos end) {
            this->type = type;
            this->as_str = as_str;
            this->start = start;
            this->end = end;
        }

        Token(TokenType type, double as_number, Pos start, Pos end) {
            this->type = type;
            this->as_number = as_number;
            this->start = start;
            this->end = end;
        }

        ~Token() {
            if (type == TokenType::SymbolToken) {
                free((void *) as_str);
            }
        }
};

std::ostream &operator<<(std::ostream& o, Token t) {
    o << t.start.line << ":" << t.start.column << " - " << t.end.line << ":" << t.end.column << " " << t.type;
    if (t.type == TokenType::NumberToken) {
        o << "(" << t.as_number << ")";
    };
    if (t.type == TokenType::SymbolToken) {
        o << "(" << t.as_str << ")";
    }
    o << std::endl;
    return o;
}

class Tokenizer {
    private:
        // flat position where we are 
        uint64_t pos = 0;
        // flat position of the last new line character
        uint64_t start_of_new_line = 0;
        uint64_t number_of_new_lines = 0;
        // used in lookahead to store temporary data
        Token *lookahead_token;
        bool is_lookahead_stored = false;
        // input text that needs to be tokenized
        const char* program;

        void eat_whitespace() {
            for (; program[pos] != '\0' && std::isspace(program[pos]); pos++) {
                if (program[pos] == '\n') {
                    start_of_new_line = pos;
                    number_of_new_lines++;
                }
            }
        }

        double eat_number(char start_num) {
            std::string num_str;
            num_str.push_back(start_num);
            for (; program[pos] != '\0' && (std::isdigit(program[pos]) || program[pos] == '.'); pos++) {
                num_str.push_back(program[pos]);
            }
            return std::atof(num_str.c_str());
        }

        const char *eat_str(uint64_t start_str) {
            for (; program[pos] != '\0' && std::isalnum(program[pos]); pos++) { }
            uint64_t len = pos-start_str;
            void *str = calloc(len+1, sizeof(char));
            memcpy(str, &program[start_str], len);
            return (const char *) str;
        }

        Pos get_pos() {
            uint64_t line = number_of_new_lines + 1;
            uint64_t column = pos - start_of_new_line + 1;
            return Pos {line, column, pos};
        }

    public:
        Tokenizer() { this->program = ""; }

        Tokenizer(const char* program) {
            this->program = program;
        }

        const char *get_program() {
            return program;
        }

        /// @brief Gives you the next token without consuming it. Repeatably calling it always returns the same token
        /// @return Pointer to a Token
        Token *lookahead() {
            if (!is_lookahead_stored) {
                lookahead_token = next();
                is_lookahead_stored = true;
            }
            return lookahead_token;
        } 

        /// @brief Gives the next token in the sequence, consuming it
        /// @return Pointer to a Token
        Token *next() {
            if (is_lookahead_stored) {
                is_lookahead_stored = false;
                return lookahead_token;
            }
            eat_whitespace();
            char ch = program[pos];
            Pos start = get_pos();
            pos++;
            switch (ch) {
                case '\0':
                    return new Token(TokenType::EOFToken, start, get_pos());
                
                case '+':
                    return new Token(TokenType::PlusOperationToken, start, get_pos());
                
                case '-':
                    return new Token(TokenType::MinusOperationToken, start, get_pos());
                
                case '*':
                    return new Token(TokenType::MultiplyOperationToken, start, get_pos());
                
                case '/':
                    return new Token(TokenType::DivideOperationToken, start, get_pos());

                case '^':
                    return new Token(TokenType::ExponentOperationToken, start, get_pos());
                
                case '!':
                    return new Token(TokenType::FactorialOperationToken, start, get_pos());
                
                case '(':
                    return new Token(TokenType::LeftParenToken, start, get_pos());
                
                case ')':
                    return new Token(TokenType::RightParenToken, start, get_pos());
                
                case ',':
                    return new Token(TokenType::CommaToken, start, get_pos());
            }
            if (std::isalpha(ch)) {
                const char *str = eat_str(pos-1);
                return new Token(TokenType::SymbolToken, str, start, get_pos());
            }

            if (std::isdigit(ch) || ch == '.') {
                double d = eat_number(ch);
                return new Token(TokenType::NumberToken, d, start, get_pos());
            }
            return new Token(TokenType::Unknown, start, get_pos());
        }
};

char *copy_string(const char *str) {
    char *ret = (char *) calloc(strlen(str)+1, sizeof(char));
    strcpy(ret, str);
    return ret;
}

uint64_t get_lines_count(const char *program) {
    uint64_t n = 1;
    for(uint64_t i = 0; program[i] != '\0'; i++) {
        if (program[i] == '\n')
            n++;
    }
    return n;
}

std::string& operator<<(std::string &a, std::string b) {
    a += b;
    return a;
}

std::string& operator<<(std::string &a, Pos b) {
    a << std::to_string(b.line) << ":" << std::to_string(b.column);
    return a;
}

uint64_t get_line_start_pos(const char *program, uint64_t line_num) {
    uint64_t curr_line_num = 1;
    for (uint64_t i = 0; program[i] != '\0'; i++) {
        if (curr_line_num == line_num)
            return i;
        if (program[i] == '\n') {
            curr_line_num++;
        }
    }
}

/// Gets the specified line by line number
std::string get_line(const char *program, uint64_t line_num) {
    std::string ret;
    uint64_t curr_line_num = 1;
    for(uint64_t i = 0; program[i] != '\0'; i++) {
        if (curr_line_num == line_num && program[i] != '\n') {
            ret.push_back(program[i]);
        }

        if (program[i] == '\n')
            curr_line_num++;
    }
    return ret;
}

class CalcException : std::exception {
    private:
        const char *_msg;
        const char *_program;
        const Pos _start;
        const Pos _end;
        char *ret;
    public:
        CalcException(const char *program, const char *msg, Pos start, Pos end) : _program(program), _msg(msg), _start(start), _end(end)  {};
        const char* what() const noexcept override {
            std::string oss("Encountered the following error at ");
            oss << _start << ":\n";
            uint64_t lines_count = get_lines_count(_program);
            for (uint64_t curr_line = 1; curr_line <= lines_count; curr_line++) {
                if (_start.line <= curr_line && curr_line <= _end.line) {
                    std::string temp;
                    temp << std::to_string(curr_line) << " | ";
                    std::string line;
                    line << get_line(_program, curr_line);
                    uint64_t curr_line_start = get_line_start_pos(_program, curr_line);

                    oss << temp << line << "\n";
                    uint64_t line_start_offset = temp.length();
                    for (uint64_t i = 0; i < line_start_offset; i++) {
                        oss << " ";
                    }
                    
                    uint64_t line_end = curr_line == _end.line ? _end.column : line.length();
                    for (uint64_t curr_col = 0; curr_col < line_end; curr_col++) {
                        oss << (_start.pos <= curr_line_start+curr_col && curr_line_start+curr_col < _end.pos ? "^" : " ");
                    }
                    if (curr_line != _end.line) {
                        oss << "\n";
                    }
                }
            }
            oss << _msg << "\n";

            return copy_string(oss.c_str());
        }
};

class EvalException : public CalcException {
    private:
        const char *_msg;
    public:
        EvalException(const char *program, const char *msg, Pos start, Pos end) : CalcException(program, msg, start, end) {};
};

double factorial(double n) {
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}

enum ExprType {
    /// Start of an expr tree
    ///
    /// Used to denote if there is nothing on the left side of an expr 
    /// instead it should look at the next token to determine its left node
    StartExpr,

    NumberExpr,
    FunCallExpr,
    PlusExpr,
    MinusExpr,
    MultiplyExpr,
    DivideExpr,
    NegationExpr,
    FactorialExpr,
    ExponentExpr,
    Variable,
};

class Expr;

typedef struct {
    const char *name;
    uint64_t size;
    uint64_t len;
    Expr **args;
    
} FunCallData;

class BinaryData {
    public:
        Expr *left;
        Expr *right;
};

// Credit: https://stackoverflow.com/questions/4157687/using-char-as-a-key-in-stdmap
struct cmp_str {
   bool operator() (char const *a, char const *b) const {
      return std::strcmp(a, b) < 0;
   }
};

class EvalContext {
    std::map<const char *, double, cmp_str> variables = {
        {"PI", 3.14159}, {"PHI", (1.+sqrt(5.))/2.}, {"E", 2.71828}
    };
    std::map<const char *, std::function<double(EvalContext *, const Expr *)>, cmp_str> functions;

    public:

        EvalContext(const char *_program);

        const char *program;

        double get_var(const char *var) {
            return variables.at(var);
        }

        std::function<double(EvalContext *, const Expr *)> get_function(const char *fun_name) {
            return functions.at(fun_name);
        }
};

class Expr {
    public:
        ExprType type;
        union {
            FunCallData as_fun_call;
            double as_number;
            const char *as_var;
            Expr *as_unary;
            BinaryData as_binary;
        } data;
        Pos start;
        Pos end;
        Expr(ExprType t, Pos s, Pos e) : type(t), start(s), end(e) { };

        Expr(FunCallData fcd, Pos s, Pos e) : type(ExprType::FunCallExpr), start(s), end(e) {
            data.as_fun_call = fcd;
        };
        
        Expr(double n, Pos s, Pos e) : type(ExprType::NumberExpr), start(s), end(e) {
            data.as_number = n;
        };

        Expr(const char *var, Pos s, Pos e) : type(ExprType::Variable), start(s), end(e) {
            data.as_var = var;
        }

        Expr(ExprType t, Expr *u, Pos s, Pos e) : type(t), start(s), end(e) {
            assert(t == ExprType::NegationExpr || t == ExprType::FactorialExpr);
            data.as_unary = u;
        };

        Expr(ExprType t, BinaryData b, Pos s, Pos e) : type(t), start(s), end(e) {
            assert(t == ExprType::DivideExpr || t == ExprType::PlusExpr || t == ExprType::MultiplyExpr || t == ExprType::MinusExpr || t == ExprType::ExponentExpr);
            data.as_binary = b;
        };

        ~Expr();

        double eval(EvalContext *ec);
        void print_expr_tree(std::ostream& o = std::cout, uint64_t level = 0);
};

double abs_fun(EvalContext *ec, const Expr *fun_call_expr) {
    assert(fun_call_expr->type == ExprType::FunCallExpr);
    if (fun_call_expr->data.as_fun_call.len != 1) {
        throw EvalException(ec->program, "ABS takes 1 argument", fun_call_expr->start, fun_call_expr->end);
    }
    double num = fun_call_expr->data.as_fun_call.args[0]->eval(ec);
    if (num < 0)
        return -num;
    return num;
}

double sin_fun(EvalContext *ec, const Expr *fun_call_expr) {
    assert(fun_call_expr->type == ExprType::FunCallExpr);
    if (fun_call_expr->data.as_fun_call.len != 1) {
        throw EvalException(ec->program, "SIN takes 1 argument", fun_call_expr->start, fun_call_expr->end);
    }
    double num = fun_call_expr->data.as_fun_call.args[0]->eval(ec);

    return sin(num);
}

double cos_fun(EvalContext *ec, const Expr *fun_call_expr) {
    assert(fun_call_expr->type == ExprType::FunCallExpr);
    if (fun_call_expr->data.as_fun_call.len != 1) {
        throw EvalException(ec->program, "COS takes 1 argument", fun_call_expr->start, fun_call_expr->end);
    }
    double num = fun_call_expr->data.as_fun_call.args[0]->eval(ec);

    return cos(num);
}

double sqrt_fun(EvalContext *ec, const Expr *fun_call_expr) {
    assert(fun_call_expr->type == ExprType::FunCallExpr);
    if (fun_call_expr->data.as_fun_call.len != 1 && fun_call_expr->data.as_fun_call.len != 2) {
        throw EvalException(ec->program, "SQRT takes 1", fun_call_expr->start, fun_call_expr->end);
    }
    double num = fun_call_expr->data.as_fun_call.args[0]->eval(ec);
    return sqrt(num);

}

EvalContext::EvalContext(const char *_program) : program(_program) {
    functions.emplace(std::pair{"ABS", abs_fun});
    functions.emplace(std::pair{"SIN", sin_fun});
    functions.emplace(std::pair{"COS", cos_fun});
    functions.emplace(std::pair{"SQRT", sqrt_fun});
}


/// ```
/// term        => factor (("+" | "-") term)*
/// factor      => exponent (("*" | "/") exponent)*
/// exponent    => fun_call ("^" fun_call)*
/// fun_call    => symbol "(" expr ("," expr )* ")" | term
/// primary     => num | symbol | var | "(" fun_call ")" | "-" fun_call | primary "!" 
/// ```
double Expr::eval(EvalContext *ec) {
    switch (type) {
        case ExprType::NumberExpr:
            return data.as_number;

        case ExprType::Variable:
            {
                double num;
                try
                {
                    num = ec->get_var(data.as_var);
                }
                catch(const std::exception& e)
                {
                    throw EvalException(ec->program, "Variable not found", start, end);
                }
                
                return num;
            }

        case ExprType::NegationExpr:
            return -(data.as_unary->eval(ec));

        case ExprType::FactorialExpr:
            {
                double num = data.as_unary->eval(ec);
                double temp;
                double check = std::modf(num, &temp);
                if (check != 0.0 || num < 0) {
                    throw EvalException(ec->program, "Only positive whole integers may be used in a factorial!", data.as_unary->start, data.as_unary->end);
                }
                return factorial(num);
            }
        case ExprType::DivideExpr:
            {
                double left = data.as_binary.left->eval(ec);
                double right = data.as_binary.right->eval(ec);

                if (right == 0) {
                    throw EvalException(ec->program, "Divide by zero!", start, end);
                }

                return left / right;
            }

        case ExprType::PlusExpr:
            {
                double left = data.as_binary.left->eval(ec);
                double right = data.as_binary.right->eval(ec);
                
                return left + right;
            }
        case ExprType::MultiplyExpr:
            {
                double left = data.as_binary.left->eval(ec);
                double right = data.as_binary.right->eval(ec);
                
                return left * right;
            }
        case ExprType::MinusExpr:
            {
                double left = data.as_binary.left->eval(ec);
                double right = data.as_binary.right->eval(ec);
                
                return left - right;
            }
        case ExprType::ExponentExpr:
            {
                double left = data.as_binary.left->eval(ec);
                double right = data.as_binary.right->eval(ec);
                
                return pow(left, right);
            }
        
        case ExprType::FunCallExpr:
            {
                std::function<double (EvalContext *, const Expr *)> f;
                try
                {
                    f = ec->get_function(data.as_fun_call.name);
                }
                catch(const std::exception& e)
                {
                    throw EvalException(ec->program, "No such function exists", start, end);
                }
                
                return f(ec, this);
            }
            break;

        default:
            std::cout << type;
            assert(false && "All cases must be covered in eval");
    }
    return 0;
}

FunCallData fun_call_data_create(const char *name) {
    return FunCallData {
        name,
        2,
        0,
        (Expr **) malloc(sizeof(Expr *)*2)
    };
}

void fun_call_args_push(FunCallData *fcd, Expr *e) {
    if (fcd->len+1 > fcd->size) {
        fcd->size = fcd->size*fcd->size;
        fcd->args = (Expr **) realloc(fcd->args, sizeof(Expr *) * fcd->size);
    }
    fcd->args[fcd->len] = e;
    fcd->len++;
}

void fun_call_data_free(FunCallData *fcd) {
    free((void *) fcd->name);
    for (int i = 0; i < fcd->len; i++) {
        delete fcd->args[i];
    }
    free((void *)fcd->args);
}

Expr::~Expr() {
    switch (type) {
        case ExprType::NumberExpr:
            break;

        case ExprType::Variable:
            free((void *) data.as_var);
            break;

        case ExprType::NegationExpr:
        case ExprType::FactorialExpr:
            delete data.as_unary;
            break;

        case ExprType::DivideExpr:
        case ExprType::PlusExpr:
        case ExprType::MultiplyExpr:
        case ExprType::MinusExpr:
        case ExprType::ExponentExpr:
            delete data.as_binary.left;
            delete data.as_binary.right;
            break;
        
        case ExprType::FunCallExpr:
            fun_call_data_free(&data.as_fun_call);
            break;
    }
}

void Expr::print_expr_tree(std::ostream& o, uint64_t level) {
    for (uint64_t i = 0; i < level; i++) {
        o << "  ";
    }

    switch (type) {
        case ExprType::NumberExpr:
            o << start << " Number: " << data.as_number << std::endl;
            break;
        
        case ExprType::FunCallExpr:
            o << start << " Function call: " << data.as_fun_call.name << std::endl;
            for (uint64_t i = 0; i < data.as_fun_call.len; i++) {
                data.as_fun_call.args[i]->print_expr_tree(o, level+1);
            }
            break;

        case ExprType::Variable:
            o << start << " Variable: " << data.as_var << std::endl;
            break;
        
        case ExprType::NegationExpr:
            o << start << " - " << std::endl;
            data.as_unary->print_expr_tree(o, level+1);
            break;
        
        case ExprType::FactorialExpr:
            o << start << " Factorial ! " << std::endl;
            data.as_unary->print_expr_tree(o, level+1);
            break;
        
        case ExprType::PlusExpr:
            o << start << " Plus:" << std::endl;
            data.as_binary.left->print_expr_tree(o, level+1);
            data.as_binary.right->print_expr_tree(o, level+1);
            break;
        
        case ExprType::MinusExpr:
            o << start << " Minus:" << std::endl;
            data.as_binary.left->print_expr_tree(o, level+1);
            data.as_binary.right->print_expr_tree(o, level+1);
            break;
        
        case ExprType::MultiplyExpr:
            o << start << " Multiply:" << std::endl;
            data.as_binary.left->print_expr_tree(o, level+1);
            data.as_binary.right->print_expr_tree(o, level+1);
            break;
        
        case ExprType::DivideExpr:
            o << start << " Divide:" << std::endl;
            data.as_binary.left->print_expr_tree(o, level+1);
            data.as_binary.right->print_expr_tree(o, level+1);
            break;
        
        case ExprType::ExponentExpr:
            o << start << " Exponent:" << std::endl;
            data.as_binary.left->print_expr_tree(o, level+1);
            data.as_binary.right->print_expr_tree(o, level+1);
    }
}

std::ostream& operator<<(std::ostream& o, Expr& p) {
    p.print_expr_tree(o);
    return o;
}

std::ostream& operator<<(std::ostream& o, Expr *p) {
    p->print_expr_tree(o);
    return o;
}

class ParsingException : public CalcException {
    public:
        ParsingException(const char *program, const char* msg, Pos start, Pos end) : CalcException(program, msg, start, end)  {};
};

// This is used to differentiate EOF problems from actual problems
class EOFBeforeExpectedException : public std::exception {
    const char *what() const noexcept override {return "This function should not have been called!";}
 };

static Expr *START = new Expr(ExprType::StartExpr, Pos{0, 0, 0}, Pos{0, 0, 0});

class Parser {
    private:
        Tokenizer tokenizer;

        /// primary     => num | symbol | "(" unary ")" | "-" fun_call
        Expr *parse_primary(Expr *left) {
            if (left->type != ExprType::StartExpr) {
                return left;
            }

            Token *n = tokenizer.next();
            Expr *ret_expr;
            switch (n->type)
            {
            case TokenType::NumberToken:
                ret_expr = new Expr(n->as_number, n->start, n->end);
                break;
            
            case TokenType::SymbolToken:
                {
                    char *var = (char*) calloc(strlen(n->as_str)+1, sizeof(char));
                    strcpy(var, n->as_str);

                    ret_expr = new Expr(var, n->start, n->end);
                }
                break;
            
            case TokenType::LeftParenToken:
                {
                    Expr *expr = parse_expr();
                    Token *right_paren = tokenizer.next();
                    bool is_right_paren = right_paren->type != TokenType::RightParenToken;
                    if (is_right_paren) {
                        std::string temp = "Expected a ')', but got: ";
                        temp.append(token_type_to_str(right_paren->type));
                        throw ParsingException(tokenizer.get_program(), copy_string(temp.c_str()), right_paren->start, right_paren->end);
                    }
                    delete right_paren;
                    ret_expr = expr;
                }
                break;
            
            case TokenType::MinusOperationToken:
                {
                    Expr *expr = parse_factor(START);
                    ret_expr = new Expr(ExprType::NegationExpr, expr, n->start, expr->end);
                }
                break;
            
            case TokenType::EOFToken:
                throw EOFBeforeExpectedException();

            default:
                std::string temp = "Unexpected token: \"";
                temp.append(token_type_to_str(n->type));
                temp.append("\"");
                throw ParsingException(tokenizer.get_program(), copy_string(temp.c_str()), n->start, n->end);
                
            }
            delete n;
            Token *factorial = tokenizer.lookahead();
            if (factorial->type == TokenType::FactorialOperationToken) {
                delete tokenizer.next();
                ret_expr = new Expr(ExprType::FactorialExpr, ret_expr, n->start, factorial->end);
            }
            return ret_expr;
        }

                /// fun_call    => symbol "(" expr ("," expr )* ")" | term
        Expr *parse_fun_call(Expr *left) {
            left = parse_primary(left);

            if (tokenizer.lookahead()->type != TokenType::LeftParenToken) {
                return left;
            }

            delete tokenizer.next();

            if (left->type != ExprType::Variable) {
                throw ParsingException(tokenizer.get_program(), "That is not something callable", left->start, left->end);
            }

            char *var = copy_string(left->data.as_var);
            Pos start = left->start;
            FunCallData fcd = fun_call_data_create(var);

            // if the fun_call was closed; func()
            if (tokenizer.lookahead()->type == TokenType::RightParenToken) {
                Token *t = tokenizer.next();
                Pos end = t->end;
                delete t;
                delete left;

                return new Expr(fcd, start, end);
            }

            // if the fun_call is still open; fun(
            //                                    ^
            if (tokenizer.lookahead()->type == TokenType::EOFToken) {
                throw EOFBeforeExpectedException();
            }

            fun_call_args_push(&fcd, parse_term(START));

            while (tokenizer.lookahead()->type == TokenType::CommaToken) {
                delete tokenizer.next();
                fun_call_args_push(&fcd, parse_term(START));
            }

            if (tokenizer.lookahead()->type == TokenType::EOFToken) {
                throw EOFBeforeExpectedException();
            }

            if (tokenizer.lookahead()->type == TokenType::RightParenToken) {
                Token *t = tokenizer.next();
                Pos end = t->end;
                delete t;
                delete left;

                return new Expr(fcd, start, end);
            }
            
            throw EOFBeforeExpectedException();
        };

        /// exponent    => primary "^" primary
        Expr *parse_exponent(Expr *left) {
            left = parse_fun_call(left);
            Token *exponent_token = tokenizer.lookahead();
            if (exponent_token->type != TokenType::ExponentOperationToken) {
                return left;
            }

            delete tokenizer.next(); // consume the exponent operator
            Expr *right = parse_expr();
            return new Expr(ExprType::ExponentExpr, BinaryData{left, right}, left->start, right->end);
        }

        /// factor      => exponent (("*" | "/") exponent)
        Expr *parse_factor(Expr *left) {
            left = parse_exponent(left);
            Token *factor_token = tokenizer.lookahead();

            while (factor_token->type == TokenType::MultiplyOperationToken || factor_token->type == TokenType::DivideOperationToken) {
                ExprType tt;
                if (factor_token->type == TokenType::MultiplyOperationToken) {
                    tt = ExprType::MultiplyExpr;
                } else {
                    tt = ExprType::DivideExpr;
                }

                delete tokenizer.next();
                Expr *right = parse_exponent(START);
                left = new Expr(tt, BinaryData {left, right}, left->start, right->end);
                factor_token = tokenizer.lookahead();  
            }
            return left;
        }

        /// term        => factor (("+" | "-") factor)*
        Expr *parse_term(Expr *left) {
            left = parse_factor(left);

            Token *term_token = tokenizer.lookahead();
            while (term_token->type == TokenType::PlusOperationToken || term_token->type == TokenType::MinusOperationToken) {
                ExprType tt;
                if (term_token->type == TokenType::PlusOperationToken) {
                    tt = ExprType::PlusExpr;
                } else {
                    tt = ExprType::MinusExpr;
                }

                delete tokenizer.next();
                Expr *right = parse_factor(START);
                left = new Expr(tt, BinaryData {left, right}, left->start, right->end);    
                term_token = tokenizer.lookahead();
            }
            
            return left;
        }

    public:
        Parser(char *str) {
            tokenizer = Tokenizer(str);
        }

        Parser(Tokenizer tokenizer) {
            this->tokenizer = tokenizer;
        }

        Expr *parse_expr() {
            Expr *left = parse_term(START);
            Token *lookahead = tokenizer.lookahead();
            while (lookahead->type != TokenType::EOFToken && lookahead->type != TokenType::RightParenToken && lookahead->type != TokenType::CommaToken) {
                left = parse_term(left);
            }
            return left;
        }
};

void testing() {
    // TOKENIZER TESTS
    Tokenizer tokenizer1(" asdf 1 () 420.69 + - * /");
    Token *t1 = tokenizer1.next();
    Token *t2 = tokenizer1.next();
    Token *t3 = tokenizer1.next();
    Token *t4 = tokenizer1.next();
    Token *t5 = tokenizer1.next();
    Token *t6 = tokenizer1.next();
    Token *t7 = tokenizer1.next();
    Token *t8 = tokenizer1.next();
    Token *t9 = tokenizer1.next();
    Token *t10 = tokenizer1.next();
    
    assert(t1->type == TokenType::SymbolToken);
    assert(!strcmp(t1->as_str, "asdf"));
    assert(t2->type == TokenType::NumberToken);
    assert(t2->as_number == 1.);
    assert(t3->type == TokenType::LeftParenToken);
    assert(t4->type == TokenType::RightParenToken);
    assert(t5->type == TokenType::NumberToken);
    assert(t5->as_number == 420.69);
    assert(t6->type == TokenType::PlusOperationToken);
    assert(t7->type == TokenType::MinusOperationToken);
    assert(t8->type == TokenType::MultiplyOperationToken);
    assert(t9->type == TokenType::DivideOperationToken);

    Parser p1("1");
    Expr *e1 = p1.parse_expr();
    assert(e1->type == ExprType::NumberExpr);
    assert(e1->data.as_number == 1.);
    delete e1;

    Parser p2("PI^69");
    Expr *e2 = p2.parse_expr();
    assert(e2->type == ExprType::ExponentExpr);
    assert(!strcmp(e2->data.as_binary.left->data.as_var, "PI"));
    assert(e2->data.as_binary.right->data.as_number == 69);
    delete e2;

    Parser p3("PI^(69^3)");
    Expr *e3 = p3.parse_expr();
    assert(e3->type == ExprType::ExponentExpr);
    assert(!strcmp(e3->data.as_binary.left->data.as_var, "PI"));
    assert(e3->data.as_binary.right->data.as_binary.left->data.as_number == 69);
    assert(e3->data.as_binary.right->data.as_binary.right->data.as_number == 3);
    delete e3;

    Parser p4("PI/5^3");
    Expr *e4 = p4.parse_expr();
    assert(e4->type == ExprType::DivideExpr);
    assert(!strcmp(e4->data.as_binary.left->data.as_var, "PI"));
    assert(e4->data.as_binary.right->type == ExprType::ExponentExpr);
    assert(e4->data.as_binary.right->data.as_binary.left->data.as_number == 5);
    assert(e4->data.as_binary.right->data.as_binary.right->data.as_number == 3);
    delete e4;

    Parser p5("PI+5*3!");
    Expr *e5 = p5.parse_expr();
    assert(e5->type == ExprType::PlusExpr);
    assert(!strcmp(e5->data.as_binary.left->data.as_var, "PI"));
    assert(e5->data.as_binary.right->type == ExprType::MultiplyExpr);
    assert(e5->data.as_binary.right->data.as_binary.left->data.as_number == 5);
    assert(e5->data.as_binary.right->data.as_binary.right->type == ExprType::FactorialExpr);
    assert(e5->data.as_binary.right->data.as_binary.right->data.as_unary->data.as_number == 3);
    delete e5;


    Parser p6("ABS()");
    Expr *e6 = p6.parse_expr();
    assert(e6->type == ExprType::FunCallExpr);
    assert(e6->data.as_fun_call.len == 0);
    assert(!strcmp(e6->data.as_fun_call.name, "ABS"));
    delete e6;


    Parser p7("ABS(69)");
    Expr *e7 = p7.parse_expr();
    assert(e7->data.as_fun_call.args[0]->data.as_number == 69);
    assert(e7->data.as_fun_call.len == 1);
    delete e7;

    Parser p8("SOMETHING(69, 70, 71)");
    Expr *e8 = p8.parse_expr();
    assert(e8->data.as_fun_call.args[0]->data.as_number == 69);
    assert(e8->data.as_fun_call.len == 3);
    delete e8;

    std::string prog1 = " 35    + 34 + 35 - 34 -1";
    Parser p9(prog1.c_str());
    Expr *e9 = p9.parse_expr();
    EvalContext *ec1 = new EvalContext(prog1.c_str());
    assert(e9->eval(ec1) == 69);
    delete e9;
    delete ec1;

    std::cout << "All tests ran successfully!";
}

void run(std::string input) {
    Parser parser(input.c_str());
    EvalContext eval_context(input.c_str());

    Expr *expr = nullptr;
    try {
        expr = parser.parse_expr();
    } catch (ParsingException e) {
        std::cout << e.what();
        std::flush(std::cout);
        free((char *) e.what());
        return;
    } catch (EOFBeforeExpectedException e) {
        if (expr != nullptr)
            delete expr;
        std::string temp;
        std::cout << "> ";
        std::getline(std::cin, temp, '\n');
        input << "\n" << temp;
        run(input);
        return;
    }

    try {
        std::cout << expr->eval(&eval_context) << std::endl;
    } catch (EvalException e) {
        std::cout << e.what();
        std::flush(std::cout);
        free((char *) e.what());
    }

    delete expr;
}

int main(int argc, char const *argv[]) {
    if (argc > 1 && !strcmp(argv[1], "test")) {
        try {
            testing();
        } catch (ParsingException e) {
            std::cout << e.what();
        }
        return 0;
    }
    std::string in;

    std::cout << "Calculator:" << std::endl;
    std::cout << "Type in any math expression" << std::endl;
    std::cout << "ex: ABS(-69)*420/69" << std::endl;
    std::cout << "(type \"exit\" to exit; \"help\" for help)" << std::endl;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, in, '\n');
        if (in == "exit" || in == "quit") {
            std::cout << "Bye!";
            break;
        }
        if (in == "help") {
            // TODO: make this more generic and have EvalContext take in the description of functions as well
            std::cout << "Variables: PI, PHI, E" << std::endl;
            std::cout << "Functions:" << std::endl;
            std::cout << "\tABS(num) = absolute value of num" << std::endl;
            std::cout << "\tSIN(num) = sin of num" << std::endl;
            std::cout << "\tCOS(num) = cos of num" << std::endl;
            std::cout << "\tSQRT(num) = sqrt of num" << std::endl;
            continue;
        }
        run(in);
    }

    return 0;
}