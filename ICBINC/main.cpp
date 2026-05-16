#include "Logger.hpp"
#include "tokenizer.hpp"


int main() {
    int64_t a = 5;
    tokenizer* tk = createTokenizer("test.txt");
    
    while (1) {
        token* tok = tk->next();
        if (tok != nullptr) {
            std::cout << tok->str << '\n';
        } else break;
    }
}