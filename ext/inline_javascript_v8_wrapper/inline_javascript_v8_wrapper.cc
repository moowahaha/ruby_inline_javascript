#include "ruby.h"
#include <v8.h>

using namespace v8;

class V8Context {

    public:

    V8Context() {
        this->context = Context::New();
    }

    ~V8Context() {
        this->dispose();
    }

    void dispose() {
        this->context.Dispose();
    }

    VALUE execute(VALUE javascript_string) {
        VALUE javascript_result;

        Context::Scope context_scope(this->context);
        HandleScope handle_scope;

        Handle<String> source = String::New(StringValueCStr(javascript_string));

        Handle<Script> javascript_functions = Script::Compile(source);
        Handle<Value> result = javascript_functions->Run();

        TryCatch trycatch;

        if (result.IsEmpty()) {
            Handle<Value> exception = trycatch.Exception();
            String::AsciiValue exception_str(exception);
            rb_raise(rb_eSyntaxError, "Cannot parse JavaScript: %s", *exception_str);
        }

        v8::String::Utf8Value str(result);

        javascript_result = rb_str_new2(*str);

        return javascript_result;
    }

    private:

    Persistent<Context> context;

};

VALUE rb_cInlineJavaScriptV8Wrapper = Qnil;

V8Context context;

VALUE rb_initialize_javascript_function(VALUE self) {
    return self;
}

VALUE rb_execute_javascript(VALUE self, VALUE javascript_string) {
//    V8Context *context;
//    Data_Get_Struct(self, V8Context, context);
    return context.execute(javascript_string);

}

extern "C" void Init_inline_javascript_v8_wrapper() {
	rb_cInlineJavaScriptV8Wrapper = rb_define_class("InlineJavaScriptV8Wrapper", rb_cObject);

	rb_define_method(rb_cInlineJavaScriptV8Wrapper, "initialize", (VALUE(*)(...))&rb_initialize_javascript_function, 0);
	rb_define_method(rb_cInlineJavaScriptV8Wrapper, "execute", (VALUE(*)(...))&rb_execute_javascript, 1);

}

