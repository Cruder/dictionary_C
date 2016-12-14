#include "gestorth.h"
#include <AccelLib/terminal.h>


int main(void) {
    // Should use the menu3 method
    Dictionary *dico = selectDictionary("demo");
    listMissingWords(dico, "yolo.txt");
    freeDictionary(dico);
    return 0;
}
