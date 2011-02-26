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

        TryCatch try_catch;

        Handle<Script> javascript_functions = Script::Compile(source);

        if (javascript_functions.IsEmpty()) {
            throw_javascript_exception(&try_catch);
        }

        Handle<Value> result = javascript_functions->Run();

        if (result.IsEmpty()) {
            throw_javascript_exception(&try_catch);
        }

        v8::String::Utf8Value str(result);

        javascript_result = rb_str_new2(*str);

        return javascript_result;
    }

    private:

    Persistent<Context> context;

    void throw_javascript_exception(TryCatch *try_catch) {
        Handle<Value> exception = try_catch->Exception();
        String::AsciiValue exception_str(exception);

        Handle<Message> message = try_catch->Message();
        if (message.IsEmpty()) {
            rb_raise(rb_eSyntaxError, "JavaScript error: %s", *exception_str);
        }

        int line = message->GetLineNumber();
        String::Utf8Value sourceline(message->GetSourceLine());

        rb_raise(rb_eSyntaxError, "JavaScript error: %s on line %d:\n%s", *exception_str, line, *sourceline);
    }

};

VALUE rb_cInlineJavaScriptV8Wrapper = Qnil;

VALUE rb_execute_java_script(VALUE self, VALUE javascript_string) {
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

extern "C" void Init_inline_java_script_v8_wrapper() {
	VALUE rb_cInlineJavaScript = rb_define_class("InlineJavaScript", rb_cObject);
	rb_cInlineJavaScriptV8Wrapper = rb_define_class_under(rb_cInlineJavaScript, "V8Wrapper", rb_cObject);
	
	rb_define_method(rb_cInlineJavaScriptV8Wrapper, "execute", (VALUE(*)(...))&rb_execute_java_script, 1);
    rb_define_alloc_func(rb_cInlineJavaScriptV8Wrapper, allocate_context);
}

