#include "gestorth.h"

int main(void) {
    // Should use the menu3 method
    Dictionary *dico = selectDictionary("demo");
    listMissingWords(dico, "yolo.txt");
    freeDictionary(dico);
    return 0;
}
