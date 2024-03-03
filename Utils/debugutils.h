#pragma once

#include <QString>
#include <QDebug>
#include <cassert>
#include <exception>

namespace Nodest{

void assertion(bool judgement, const char* file, const char* func, int line,
               const QString& info);

#ifndef ND_ASSERT
  #ifdef QT_DEBUG
    #define ND_ASSERT(judgement, info) \
      assertion((judgement), __FILE__, __func__, __LINE__, (info));
  #else
    #define ND_ASSERT(judgement, info) \
      do { \
      } while(0)
  #endif
#endif

}
