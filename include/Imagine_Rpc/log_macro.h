#ifndef IMAGINE_RPC_LOG_MACRO_H
#define IMAGINE_RPC_LOG_MACRO_H

// 内部使用的日志宏(与common_macro分开, 减少额外的include)

#include "Imagine_Log/Imagine_Log.h"

// 内部日志开关
#define OPEN_IMAGINE_RPC_LOG

#ifdef OPEN_IMAGINE_RPC_LOG
#define IMAGINE_RPC_LOG(LOG_MESSAGE...) \
    do { \
        LOG_INFO(LOG_MESSAGE); \
    } while(0)
#else
#define IMAGINE_RPC_LOG(LOG_MESSAGE...) do { } while(0)
#endif

#endif