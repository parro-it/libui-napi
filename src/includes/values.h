#ifndef LIBUI_NODE_VALUES_H__
#define LIBUI_NODE_VALUES_H__

#include "napi_utils.h"

napi_value make_size_int(napi_env env, int width, int height);
napi_value make_size_double(napi_env env, double width, double height);
napi_value make_point(napi_env env, double x, double y);
napi_value make_color(napi_env env, double r, double g, double b, double a);

#endif
