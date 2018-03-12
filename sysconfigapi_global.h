#ifndef SYSCONFIGAPI_GLOBAL_H
#define SYSCONFIGAPI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SYSCONFIGAPI_LIBRARY)
#  define SYSCONFIGAPISHARED_EXPORT Q_DECL_EXPORT
#else
#  define SYSCONFIGAPISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SYSCONFIGAPI_GLOBAL_H