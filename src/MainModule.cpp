#include "BasicBinaryExpression.cpp"
#include "BasicEnv.cpp"
#include "BasicExecutor.cpp"
#include "BasicFileConsole.cpp"
#include "BasicGoSubStatement.cpp"
#include "BasicGotoStatement.cpp"
#include "BasicIfStatement.cpp"
#include "BasicInputStatement.cpp"
#include "BasicIntExpression.cpp"
#include "BasicInterpreter.cpp"
#include "BasicLetStatement.cpp"
#include "BasicLexer.cpp"
#include "BasicParser.cpp"
#include "BasicPrintStatement.cpp"
#include "BasicReturnStatement.cpp"
#include "BasicRunStatement.cpp"
#include "BasicTerminal.cpp"
#include "BasicToken.cpp"
#include "BasicUnaryExpression.cpp"
#include "BasicVarExpression.cpp"

namespace basic {

    static int basic_runFile(char* filename) {
        BasicFileConsole console {filename};
        BasicInterpreter interpreter {console};
        interpreter.runInteractive();
        return 0;
    }

    int run(int argc, char** argv, BasicConsole* console) {
        if(argc > 2) {
            return basic_runFile(argv[1]);
        }

        std::cout << "Ross Online Solutions Tiny BASIC (main)" << std::endl;
        std::cout << "Version 1.0.0" << std::endl;

        // else run interactive
        BasicTerminal terminal;
        BasicInterpreter interpreter {console ? *console : terminal};

        interpreter.runInteractive();
        return interpreter.getTotalErrs() == 0 ? 0 : -1;
    }
}
