#include "duktape.h"
#include <iostream>
#include <fstream>
#include <string>

std::string readFile(const char* filename) {
    std::ifstream file(filename);
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

int main() {
    duk_context *ctx = duk_create_heap_default();

    // Load Faker.js
    std::string fakerScript = readFile("path/to/faker.js");
    duk_eval_string(ctx, fakerScript.c_str());

    // Usage example to generate a name
    duk_eval_string(ctx, "const { name } = require('@faker-js/faker'); name.findName();");
    std::cout << "Generated Name: " << duk_safe_to_string(ctx, -1) << std::endl;

    duk_pop(ctx);
    duk_destroy_heap(ctx);
    return 0;
}
