#ifndef AST_HPP
#define AST_HPP

#include <filesystem>
#include <memory>
#include <vector>

namespace mlang {

    struct ASTNode;

    using ASTNodePtr = std::shared_ptr<ASTNode>;

    enum class ASTType {
        // Modules & Declarations
        Import,
        Class,
        Interface,
        Struct,
        Enum,
        Function,
        Variable,
        Field,
        Parameter,
        TypeIdentifier,
        GenericType,

        // Statements
        Block,
        Match,
        If,
        Else,
        For,
        While,
        DoWhile,
        Return,
        Next,
        Stop,

        // Expressions
        Call,
        Binary,
        Unary,
        Ternary,
        Grouping,
        Assignment,
        Index,
        MemberAccess,
        Lambda,
        TypeCast,

        // Literals
        Identifier,
        IntegerLiteral,
        RealLiteral,
        StringLiteral,
        CharLiteral,
        BooleanLiteral,
        NullLiteral
    };


    struct ASTNode {
        explicit ASTNode(const ASTType t) : type(t) {}
        virtual ~ASTNode() = default;

        ASTType type;
    };

    // Represents an import statement on top of file
    struct ImportNode final : ASTNode {
        explicit ImportNode(std::string path) : ASTNode(ASTType::Import),
            path(std::move(path)) {}

        std::string path;
    };

    // Represents a simple type identifier, used in annotations. e.g. `str`, `u8`
    struct TypeIdentifierNode final : ASTNode {
        explicit TypeIdentifierNode(std::string name) : ASTNode(ASTType::TypeIdentifier), name(std::move(name)) {}
        std::string name;
    };

    // Represents a generic type, e.g. `array<u8, 16>`
    struct GenericTypeNode final : ASTNode {
        GenericTypeNode(ASTNodePtr base_type, std::vector<ASTNodePtr> type_params)
            : ASTNode(ASTType::GenericType), base_type(std::move(base_type)), type_parameters(std::move(type_params)) {}

        ASTNodePtr base_type; // e.g., IdentifierNode for "array"
        std::vector<ASTNodePtr> type_parameters; // e.g., TypeIdentifierNode for "u8", IntegerLiteralNode for "16"
    };

    // Represents a parameter in a function or lambda definition.
    struct ParameterNode final : ASTNode {
        ParameterNode(std::string name, ASTNodePtr type_annotation)
            : ASTNode(ASTType::Parameter), name(std::move(name)), type_annotation(std::move(type_annotation)) {}

        std::string name;
        ASTNodePtr type_annotation; // e.g., TypeIdentifierNode or GenericTypeNode
    };

    // Represents a block of statements, enclosed in {}.
    struct BlockNode final : ASTNode {
        explicit BlockNode(std::vector<ASTNodePtr> statements)
            : ASTNode(ASTType::Block), statements(std::move(statements)) {}

        std::vector<ASTNodePtr> statements;
    };

    // Represents a function declaration.
    struct FunctionNode final : ASTNode {
        FunctionNode(std::string name, std::vector<ASTNodePtr> params, ASTNodePtr return_type, ASTNodePtr body)
            : ASTNode(ASTType::Function), name(std::move(name)), parameters(std::move(params)),
              return_type(std::move(return_type)), body(std::move(body)) {}

        std::string name;
        std::vector<ASTNodePtr> parameters; // Vector of ParameterNode
        ASTNodePtr return_type;             // e.g., TypeIdentifierNode or GenericTypeNode
        ASTNodePtr body;                    // e.g., BlockNode
    };

    // Represents a variable declaration, e.g., `var x: int = 10` or `val y = "hello"`
    struct VariableNode final : ASTNode {
        VariableNode(std::string name, bool is_mutable, ASTNodePtr type_annotation, ASTNodePtr initializer)
            : ASTNode(ASTType::Variable), name(std::move(name)), is_mutable(is_mutable),
              type_annotation(std::move(type_annotation)), initializer(std::move(initializer)) {}

        std::string name;
        bool is_mutable;            // true for 'var', false for 'val'
        ASTNodePtr type_annotation; // Optional, can be nullptr
        ASTNodePtr initializer;     // Optional, can be nullptr
    };

    // Represents a class/struct field.
    struct FieldNode final : ASTNode {
        FieldNode(std::string name, bool is_mutable, ASTNodePtr type_annotation, ASTNodePtr initializer)
            : ASTNode(ASTType::Field), name(std::move(name)), is_mutable(is_mutable),
              type_annotation(std::move(type_annotation)), initializer(std::move(initializer)) {}

        std::string name;
        bool is_mutable;            // true for 'var', false for 'val'
        ASTNodePtr type_annotation; // Optional
        ASTNodePtr initializer;     // Optional
    };

    // Represents a struct declaration (data only).
    struct StructNode final : ASTNode {
        StructNode(std::string name, std::vector<ASTNodePtr> fields)
            : ASTNode(ASTType::Struct), name(std::move(name)), fields(std::move(fields)) {}

        std::string name;
        std::vector<ASTNodePtr> fields; // Vector of FieldNode
    };

    // Represents a class declaration (data and behavior).
    struct ClassNode final : ASTNode {
        ClassNode(std::string name, ASTNodePtr base_class, std::vector<ASTNodePtr> members)
            : ASTNode(ASTType::Class), name(std::move(name)), base_class(std::move(base_class)),
              members(std::move(members)) {}

        std::string name;
        ASTNodePtr base_class; // Optional, can be nullptr. e.g., IdentifierNode
        std::vector<ASTNodePtr> members; // Vector of FieldNode and FunctionNode
    };

    // Represents an interface declaration.
    struct InterfaceNode final : ASTNode {
        InterfaceNode(std::string name, std::vector<ASTNodePtr> methods)
            : ASTNode(ASTType::Interface), name(std::move(name)), methods(std::move(methods)) {}

        std::string name;
        std::vector<ASTNodePtr> methods; // Vector of FunctionNode (signatures only)
    };

    // Represents an enum declaration.
    struct EnumNode final : ASTNode {
        EnumNode(std::string name, std::vector<std::string> cases)
            : ASTNode(ASTType::Enum), name(std::move(name)), cases(std::move(cases)) {}

        std::string name;
        std::vector<std::string> cases;
    };

    // --- Statements ---

    // Represents a case within a match statement.
    struct MatchCaseNode final : ASTNode {
        MatchCaseNode(ASTNodePtr pattern, ASTNodePtr body)
            : ASTNode(ASTType::Match), pattern(std::move(pattern)), body(std::move(body)) {}

        ASTNodePtr pattern; // Expression to match against
        ASTNodePtr body;    // BlockNode or single expression to execute
    };

    // Represents a match statement.
    struct MatchNode final : ASTNode {
        MatchNode(ASTNodePtr expression, std::vector<ASTNodePtr> cases)
            : ASTNode(ASTType::Match), expression(std::move(expression)), cases(std::move(cases)) {}

        ASTNodePtr expression;
        std::vector<ASTNodePtr> cases; // Vector of MatchCaseNode
    };

    // Represents an if-else statement.
    struct IfNode final : ASTNode {
        IfNode(ASTNodePtr condition, ASTNodePtr then_branch, ASTNodePtr else_branch)
            : ASTNode(ASTType::If), condition(std::move(condition)),
              then_branch(std::move(then_branch)), else_branch(std::move(else_branch)) {}

        ASTNodePtr condition;
        ASTNodePtr then_branch;
        ASTNodePtr else_branch; // Optional, can be nullptr. Can be another IfNode for `else if`.
    };

    // Represents a for-each loop.
    struct ForNode final : ASTNode {
        ForNode(ASTNodePtr variable, ASTNodePtr iterable, ASTNodePtr body)
            : ASTNode(ASTType::For), variable(std::move(variable)),
              iterable(std::move(iterable)), body(std::move(body)) {}

        ASTNodePtr variable; // Identifier for the loop variable
        ASTNodePtr iterable; // Expression that yields an iterable
        ASTNodePtr body;     // BlockNode
    };

    // Represents a while loop.
    struct WhileNode final : ASTNode {
        WhileNode(ASTNodePtr condition, ASTNodePtr body)
            : ASTNode(ASTType::While), condition(std::move(condition)), body(std::move(body)) {}

        ASTNodePtr condition;
        ASTNodePtr body; // BlockNode
    };

    // Represents a do-while loop.
    struct DoWhileNode final : ASTNode {
        DoWhileNode(ASTNodePtr body, ASTNodePtr condition)
            : ASTNode(ASTType::DoWhile), body(std::move(body)), condition(std::move(condition)) {}

        ASTNodePtr body; // BlockNode
        ASTNodePtr condition;
    };

    // Represents a return statement.
    struct ReturnNode final : ASTNode {
        explicit ReturnNode(ASTNodePtr value) : ASTNode(ASTType::Return), value(std::move(value)) {}

        ASTNodePtr value; // Optional, can be nullptr for returning void.
    };

    // Represents a 'next' (continue) statement.
    struct NextNode final : ASTNode {
        NextNode() : ASTNode(ASTType::Next) {}
    };

    // Represents a 'stop' (break) statement.
    struct StopNode final : ASTNode {
        StopNode() : ASTNode(ASTType::Stop) {}
    };

    // --- Expressions ---

    // Represents a function or method call.
    struct CallNode final : ASTNode {
        CallNode(ASTNodePtr callee, std::vector<ASTNodePtr> arguments)
            : ASTNode(ASTType::Call), callee(std::move(callee)), arguments(std::move(arguments)) {}

        ASTNodePtr callee; // Identifier or MemberAccess
        std::vector<ASTNodePtr> arguments;
    };

    // Represents a binary operation, e.g., `a + b`.
    struct BinaryNode final : ASTNode {
        BinaryNode(ASTNodePtr left, std::string op, ASTNodePtr right)
            : ASTNode(ASTType::Binary), left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

        ASTNodePtr left;
        std::string op; // e.g., "+", "==", ">"
        ASTNodePtr right;
    };

    // Represents a unary operation, e.g., `-x` or `!y`.
    struct UnaryNode final : ASTNode {
        UnaryNode(std::string op, ASTNodePtr operand, bool is_prefix)
            : ASTNode(ASTType::Unary), op(std::move(op)), operand(std::move(operand)), is_prefix(is_prefix) {}

        std::string op; // e.g., "-", "!"
        ASTNodePtr operand;
        bool is_prefix; // true for `!x`, false for `x++` (if supported)
    };

    // Represents a ternary (conditional) expression, e.g., `cond ? then : else`.
    struct TernaryNode final : ASTNode {
        TernaryNode(ASTNodePtr condition, ASTNodePtr then_expr, ASTNodePtr else_expr)
            : ASTNode(ASTType::Ternary), condition(std::move(condition)),
              then_expr(std::move(then_expr)), else_expr(std::move(else_expr)) {}

        ASTNodePtr condition;
        ASTNodePtr then_expr;
        ASTNodePtr else_expr;
    };

    // Represents a grouping expression, e.g., `(1 + 2)`.
    struct GroupingNode final : ASTNode {
        explicit GroupingNode(ASTNodePtr expression) : ASTNode(ASTType::Grouping), expression(std::move(expression)) {}

        ASTNodePtr expression;
    };

    // Represents an assignment, e.g., `x = 5`.
    struct AssignmentNode final : ASTNode {
        AssignmentNode(ASTNodePtr target, ASTNodePtr value)
            : ASTNode(ASTType::Assignment), target(std::move(target)), value(std::move(value)) {}

        ASTNodePtr target; // e.g., Identifier or MemberAccess
        ASTNodePtr value;
    };

    // Represents an index access, e.g., `arr[i]`.
    struct IndexNode final : ASTNode {
        IndexNode(ASTNodePtr callee, ASTNodePtr index)
            : ASTNode(ASTType::Index), callee(std::move(callee)), index(std::move(index)) {}

        ASTNodePtr callee;
        ASTNodePtr index;
    };

    // Represents member access, e.g., `obj.field`.
    struct MemberAccessNode final : ASTNode {
        MemberAccessNode(ASTNodePtr object, std::string member_name)
            : ASTNode(ASTType::MemberAccess), object(std::move(object)), member_name(std::move(member_name)) {}

        ASTNodePtr object;
        std::string member_name;
    };

    // Represents a lambda or anonymous function.
    struct LambdaNode final : ASTNode {
        LambdaNode(std::vector<ASTNodePtr> params, ASTNodePtr body)
            : ASTNode(ASTType::Lambda), parameters(std::move(params)), body(std::move(body)) {}

        std::vector<ASTNodePtr> parameters; // Vector of ParameterNode
        ASTNodePtr body;                    // BlockNode or single expression
    };

    // Represents a type cast, e.g., `x as int`.
    struct TypeCastNode final : ASTNode {
        TypeCastNode(ASTNodePtr expression, ASTNodePtr target_type)
            : ASTNode(ASTType::TypeCast), expression(std::move(expression)), target_type(std::move(target_type)) {}

        ASTNodePtr expression;
        ASTNodePtr target_type; // e.g., TypeIdentifierNode or GenericTypeNode
    };

    // --- Literals ---

    // Represents an identifier, e.g., a variable name.
    struct IdentifierNode final : ASTNode {
        explicit IdentifierNode(std::string name) : ASTNode(ASTType::Identifier), name(std::move(name)) {}
        std::string name;
    };

    // Represents an integer literal, e.g., `123`.
    struct IntegerLiteralNode final : ASTNode {
        explicit IntegerLiteralNode(long long value) : ASTNode(ASTType::IntegerLiteral), value(value) {}
        long long value;
    };

    // Represents a real (floating-point) literal, e.g., `3.14`.
    struct RealLiteralNode final : ASTNode {
        explicit RealLiteralNode(double value) : ASTNode(ASTType::RealLiteral), value(value) {}
        double value;
    };

    // Represents a string literal, e.g., `"hello"`.
    struct StringLiteralNode final : ASTNode {
        explicit StringLiteralNode(std::string value) : ASTNode(ASTType::StringLiteral), value(std::move(value)) {}
        std::string value;
    };

    // Represents a character literal, e.g., `'c'`.
    struct CharLiteralNode final : ASTNode {
        explicit CharLiteralNode(char value) : ASTNode(ASTType::CharLiteral), value(value) {}
        char value;
    };

    // Represents a boolean literal, `true` or `false`.
    struct BooleanLiteralNode final : ASTNode {
        explicit BooleanLiteralNode(bool value) : ASTNode(ASTType::BooleanLiteral), value(value) {}
        bool value;
    };

    // Represents a null literal.
    struct NullLiteralNode final : ASTNode {
        NullLiteralNode() : ASTNode(ASTType::NullLiteral) {}
    };

}

#endif //AST_HPP
