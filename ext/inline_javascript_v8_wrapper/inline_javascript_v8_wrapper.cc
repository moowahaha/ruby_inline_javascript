#include "ruby.h"
#include <v8.h>

using namespace v8;

VALUE rb_cInlineJavaScriptV8Wrapper = Qnil;

Persistent<Context> context = Context::New();
Context::Scope context_scope(context);
HandleScope handle_scope;

VALUE rb_initialize_javascript_function(VALUE self, VALUE javascript_string) {

    Handle<String> func_source = String::New(StringValueCStr(javascript_string));
    Handle<Script> func = Script::Compile(func_source);
    Handle<Value> func_result = func->Run();

    return self;
}

VALUE rb_execute_javascript(VALUE self, VALUE javascript_string) {
    VALUE javascript_result;

    Handle<String> source = String::New(StringValueCStr(javascript_string));
    Handle<Script> script = Script::Compile(source);

    TryCatch trycatch;
    Handle<Value> result = script->Run();

    if (result.IsEmpty()) {
        Handle<Value> exception = trycatch.Exception();
        String::AsciiValue exception_str(exception);
        rb_raise(rb_eSyntaxError, "Cannot parse JavaScript: %s", *exception_str);
    }

    // Dispose the persistent context.
    //context.Dispose();

    // Convert the result to an ASCII string and print it.

    String::AsciiValue ascii(result);

    javascript_result = rb_str_new2(*ascii);

    return javascript_result;
}

extern "C" void Init_inline_javascript_v8_wrapper() {
	rb_cInlineJavaScriptV8Wrapper = rb_define_class("InlineJavaScriptV8Wrapper", rb_cObject);

	rb_define_method(rb_cInlineJavaScriptV8Wrapper, "initialize", (VALUE(*)(...))&rb_initialize_javascript_function, 1);
	rb_define_method(rb_cInlineJavaScriptV8Wrapper, "execute", (VALUE(*)(...))&rb_execute_javascript, 1);
}

