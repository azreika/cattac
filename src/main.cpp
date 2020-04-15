#include "SatInterface.h"

int main(int argc, char** argv) {
    SatInterface interface;
    interface.setOptions(argc, argv);
    interface.execute();
    return 0;
}
