#ifndef CTKCOREEXPORT_H
#define CTKCOREEXPORT_H

#include <QtCore/qglobal.h>

#if defined(PluginFramework_CORE_LIBRARY)
#  define CTK_CORE_EXPORT Q_DECL_EXPORT
#else
#  define CTK_CORE_EXPORT Q_DECL_IMPORT
#endif

#endif // CTKCOREEXPORT_H
