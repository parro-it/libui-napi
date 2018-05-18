#include <ui.h>
#include "napi_utils.h"
#include "values.h"

static const char *MODULE = "OpenTypeFeatures";

// static void free_otf(napi_env env, void *finalize_data, void *finalize_hint) {
// 	uiOpenTypeFeatures *otf = (uiOpenTypeFeatures *)finalize_data;
// 	uiFreeOpenTypeFeatures(otf);
// }

// static napi_value create_otf_external(napi_env env, uiOpenTypeFeatures *otf) {
// 	napi_value otf_external;
// 	napi_status status = napi_create_external(env, otf, free_otf, NULL, &otf_external);
// 	CHECK_STATUS_THROW(status, napi_create_external);

// 	return otf_external;
// }

napi_value _libui_init_font_opentype(napi_env env, napi_value exports) {
	DEFINE_MODULE();

	return module;
}
