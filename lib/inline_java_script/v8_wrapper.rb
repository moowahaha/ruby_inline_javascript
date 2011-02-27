require File.join(File.dirname(__FILE__), %w{.. .. ext inline_java_script_v8_wrapper inline_java_script_v8_wrapper})

#== SYNOPSIS:
#To call the V8 engine:
#
#    require 'inline_java_script/v8_wrapper'
#
#    wrapper = InlineJavaScript::V8Wrapper.new
#    wrapper.execute('1 + 2') #=> "3"
#
#An instance of the V8Wrapper maintains state:
#
#    wrapper = InlineJavaScript::V8Wrapper.new
#    wrapper.execute('var e = "monster"')
#    wrapper.execute('e') #=> "monster"
#
#    # ... But I cannot access another instance...
#    InlineJavaScript::V8Wrapper.new.execute('e') #=> SyntaxError

class InlineJavaScript::V8Wrapper
end