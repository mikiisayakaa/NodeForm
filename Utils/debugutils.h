#pragma once

#include <QString>
#include <QDebug>
#include <cassert>
#include <exception>

namespace NF{

void assertion(bool judgement, const char* file, const char* func, int line,
               const QString& info);

#ifndef NF_ASSERT
  #ifdef QT_DEBUG
    #define NF_ASSERT(judgement, info) \
      assertion((judgement), __FILE__, __func__, __LINE__, (info));
  #else
    #define NF_ASSERT(judgement, info) \
      do { \
      } while(0)
  #endif
#endif

}
