// taken from:
// http://code.google.com/apis/v8/embed.html
#include <v8.h>

using namespace v8;

int main(int argc, char* argv[]) {

  // Create a stack-allocated handle scope.
  HandleScope handle_scope;

  // Create a new context.
  Persistent<Context> context = Context::New();

  // Enter the created context for compiling and
  // running the hello world script. 
  Context::Scope context_scope(context);

  // Create a method
  Handle<String> func_source = String::New(argv[1]);
  //Handle<String> func_source = String::New("function myConcat (a, b) { return(a + ' ' + b) }");
  Handle<Script> func = Script::Compile(func_source);
  Handle<Value> func_result = func->Run();

  // execute a method
  Handle<String> source = String::New(argv[2]);
  //Handle<String> source = String::New("myConcat('abc', 'def')");
  Handle<Script> script = Script::Compile(source);

  TryCatch trycatch;
  Handle<Value> result = script->Run();

  // Dispose the persistent context.
  context.Dispose();

  // Convert the result to an ASCII string and print it.
  String::AsciiValue ascii(result);
  printf("%s\n", *ascii);
  return 0;
}
