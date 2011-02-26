#include "ruby.h"
#include <v8.h>

using namespace v8;

class V8Context {

    public:

    V8Context() {
        this->context = Context::New();
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

VALUE rb_execute_javascript(VALUE self, VALUE javascript_string) {
    V8Context *this_context;
    Data_Get_Struct(self, V8Context, this_context);
    return this_context->execute(javascript_string);

}

void dispose_of_context(V8Context *this_context) {
    this_context->dispose();
}

VALUE allocate_context(VALUE klass) {
    V8Context *this_context = new V8Context();
    return Data_Wrap_Struct(klass, 0, dispose_of_context, this_context);
}

extern "C" void Init_inline_javascript_v8_wrapper() {
	rb_cInlineJavaScriptV8Wrapper = rb_define_class("InlineJavaScriptV8Wrapper", rb_cObject);
	rb_define_method(rb_cInlineJavaScriptV8Wrapper, "execute", (VALUE(*)(...))&rb_execute_javascript, 1);
    rb_define_alloc_func(rb_cInlineJavaScriptV8Wrapper, allocate_context);
}

