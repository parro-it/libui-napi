#ifndef __LIBUI_NODE_VALUES_H__
#define __LIBUI_NODE_VALUES_H__

#include "napi_utils.h"

napi_value make_size(napi_env env, uint32_t width, uint32_t height);
napi_value from_size(napi_env env, napi_value size, uint32_t *width, uint32_t *height);

#endif
