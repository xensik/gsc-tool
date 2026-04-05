#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include "antlr4-runtime.h"
#include "gsc_iw_grammarLexer.h"
#include "gsc_iw_grammarParser.h"


using namespace antlr4;
using json = nlohmann::json;

json parseTreeToJson(tree::ParseTree* tree, Parser* parser) {
    json j;
    if (tree->children.empty()) {
        j["text"] = tree->getText();
    } else {
        auto context = dynamic_cast<ParserRuleContext*>(tree);
        if (context) {
            j["rule"] = parser->getRuleNames()[context->getRuleIndex()];
        } else {
            j["rule"] = "unknown";
        }
        for (auto child : tree->children) {
            j["children"].push_back(parseTreeToJson(child, parser));
        }
    }
    return j;
}

int main(int argc, const char* argv[]) {
    // Read input
    std::ifstream stream;
    stream.open("test.gsc");
    ANTLRInputStream input(stream);

    // Create a lexer and parser
    gsc_iw_grammarLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    gsc_iw_grammarParser parser(&tokens);

    // Parse the input
    tree::ParseTree* tree = parser.program();

    // Print the parse tree
    //std::cout << tree->toStringTree(&parser) << std::endl;

    // Convert parse tree to JSON
    json j = parseTreeToJson(tree, &parser);

    // Print the JSON representation of the parse tree
    //std::cout << j.dump(4) << std::endl; // Pretty print with 4 spaces indentation

    // Save the JSON representation of the parse tree to a file
    std::ofstream outFile("parse_tree.json");
    outFile << j.dump(4); // Pretty print with 4 spaces indentation
    outFile.close();
    
    return 0;
}
