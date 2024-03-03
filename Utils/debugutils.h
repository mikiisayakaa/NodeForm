#pragma once

#include <QString>
#include <QDebug>

namespace Nodest{

void assertion(bool judgement, const QString& file, const QString& func, int line,
               const QString& info);

#ifndef ND_ASSERT
  #ifdef QT_DEBUG
    #define ND_ASSERT(judgement, info) \
      do { \
          assertion((judgement), __FILE__, __func__, __LINE__, (info)); \
      } while(0)
  #else
    #define ND_ASSERT(judgement, info) \
      do { \
      } while(0)
  #endif
#endif

}
