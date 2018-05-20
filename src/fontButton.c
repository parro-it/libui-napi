#include <ui.h>
#include "napi_utils.h"
#include "control.h"
#include "events.h"
#include "values.h"

static const char *MODULE = "FontButton";

// font-descriptor.c
typedef struct {
	uiFontDescriptor *font;
	bool fromButton;
} FontHandle;
napi_value create_font_descriptor(napi_env env, FontHandle *h);

LIBUI_FUNCTION(create) {
	uiControl *ctrl = uiControl(uiNewFontButton());
	return control_handle_new(env, ctrl, "fontButton");
}

LIBUI_FUNCTION(onChanged) {
	INIT_ARGS(2);

	ARG_POINTER(struct control_handle, handle, 0);
	ARG_CB_REF(cb_ref, 1);

	struct event_t *event = create_event(env, cb_ref, "onChanged");
	if (event == NULL) {
		return NULL;
	}

	install_event(handle->events, event);

	uiFontButtonOnChanged(uiFontButton(handle->control),
						  CALLBACK_OF(uiFontButton, control_event_cb), event);

	return NULL;
}

LIBUI_FUNCTION(getFont) {
	INIT_ARGS(1);
	ARG_POINTER(struct control_handle, handle, 0);

	FontHandle *h = malloc(sizeof(FontHandle));
	h->font = malloc(sizeof(uiFontDescriptor));
	h->fromButton = true;

	uiFontButtonFont(uiFontButton(handle->control), h->font);
	return create_font_descriptor(env, h);
}

napi_value _libui_init_fontbutton(napi_env env, napi_value exports) {
	DEFINE_MODULE();
	LIBUI_EXPORT(create);
	LIBUI_EXPORT(getFont);
	LIBUI_EXPORT(onChanged);
	return module;
}
