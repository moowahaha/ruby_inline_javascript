#include <ruby.h>
#include <js/jsapi.h>

// http://egachine.berlios.de/embedding-sm-best-practice/embedding-sm-best-practice.html

typedef struct {
  JSRuntime *runtime;
  JSContext *context;
  JSObject  *global;
} engine_struct;

VALUE rb_execute_java_script(VALUE self, VALUE javascript_string) {
  engine_struct *engine;
  Data_Get_Struct(self, engine_struct, engine);

  /* script to run (should return 100) */
  char *script = StringValueCStr(javascript_string);
  /* JavaScript value to store the result of the script */

  jsval rval;

  if (!JS_EvaluateScript(engine->context, engine->global, script, strlen(script),
			 "script", 1, &rval))
    return EXIT_FAILURE;

  /*replace with something meaningful  like turning it into a string*/
//  if (!(JSVAL_IS_INT(rval)&&(JSVAL_TO_INT(rval)==100)))
//    return EXIT_FAILURE;

    return rb_str_new2(JS_GetStringBytes(JSVAL_TO_STRING(rval)));
}

VALUE rb_cInlineJavaScriptSpiderMonkeyWrapper = Qnil;

void shutdown_engine(engine_struct *engine) {
  JS_DestroyContext(engine->context);
  JS_DestroyRuntime(engine->runtime);
  JS_ShutDown();
  free(engine);
}

VALUE initialize_engine(VALUE klass) {
  engine_struct* engine = malloc(sizeof(engine_struct));

  engine->runtime = JS_NewRuntime(1024L*1024L);

  if (    (!engine->runtime)
       || (!(engine->context = JS_NewContext (engine->runtime, 8192)))
       || (!(engine->global  = JS_NewObject  (engine->context, NULL, NULL, NULL)))
     ) {
    return EXIT_FAILURE;
  }

  if (!JS_InitStandardClasses(engine->context, engine->global)) {
    return EXIT_FAILURE;
  }

  return Data_Wrap_Struct(klass, 0, shutdown_engine, engine);
}

void Init_inline_java_script_spidermonkey_wrapper() {
    VALUE rb_cInlineJavaScript = rb_define_class("InlineJavaScript", rb_cObject);
    rb_cInlineJavaScriptSpiderMonkeyWrapper = rb_define_class_under(rb_cInlineJavaScript, "SpiderMonkeyWrapper", rb_cObject);

    rb_define_method(rb_cInlineJavaScriptSpiderMonkeyWrapper, "execute", &rb_execute_java_script, 1);
    rb_define_alloc_func(rb_cInlineJavaScriptSpiderMonkeyWrapper, initialize_engine);
}
