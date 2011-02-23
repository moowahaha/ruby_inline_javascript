#include "ruby.h"

using namespace std;

VALUE rb_cInlineJavaScriptV8Wrapper = Qnil;

VALUE rb_initialize_javascript_function(VALUE self, VALUE javascript_string) {
    printf("method: %s\n", StringValueCStr(javascript_string));

    return self;
}

VALUE rb_execute_javascript(VALUE self, VALUE javascript_string) {
    printf("execute: %s\n", StringValueCStr(javascript_string));
}

extern "C" void Init_inline_javascript_v8_wrapper() {
	rb_cInlineJavaScriptV8Wrapper = rb_define_class("InlineJavaScriptV8Wrapper", rb_cObject);

	rb_define_method(rb_cInlineJavaScriptV8Wrapper, "initialize", (VALUE(*)(...))&rb_initialize_javascript_function, 1);
	rb_define_method(rb_cInlineJavaScriptV8Wrapper, "execute", (VALUE(*)(...))&rb_execute_javascript, 1);
}

