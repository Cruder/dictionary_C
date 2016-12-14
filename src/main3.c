#include "gestorth.h"

int main(void) {
    // Should use the menu3 method
    Dictionary *dico = selectDictionary("demo");
    listUnexistsWords(dico, "yolo.txt");
    freeDictionary(dico);
    return 0;
}
