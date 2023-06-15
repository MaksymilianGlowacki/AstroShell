#include <iostream>
#include <tools/InputParser.h>

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    tools::InputParser app(argc, argv);
    app.add_option("max-input", "Maximal number of data points. Default: 100000", 'M');
    app.add_flag("forward-input", "Forwards the photometry data to the next program", 'f');
    auto params = app.parse();


    return 0;
}