
#include "corto/cpp/cpp.h"

namespace corto {
::corto::Object root(::root_o);
}

/* cortomain is called when the package is loaded by Corto. It is a good
 * place for initialization code that needs to be executed once.
 * The function can be safely removed if not needed. */
int cortomain(int argc, char *argv[]) {

    return 0;
}
