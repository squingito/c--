#include "Logger.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"
#include "typeHandler.hpp"


int main() {
    /*
    int64_t a = 5;
    tokenizer* tk = createTokenizer("test.txt");
    
    while (1) {
        token* tok = tk->next();
        if (tok != nullptr) {
            std::cout << tok->str << '\n';
        } else break;
    }
        

        */
    parser* pa = parser::createParser("test.txt");
    valueBlockSB* parsed = pa->parseTest();
    std::cout << parsed->toString();

    
/*
    typeHandler* th = new typeHandler();
    valueType* t1 = th->searchType("int", 0);
    valueType* t2 = th->searchType("int", 2);
    std::vector<valueType*> args;
    th->insert(t1, args, 0, new functionType(t1, args));
    valueType* t3 = th->searchType("dsfsfds0", 1);
    */
}