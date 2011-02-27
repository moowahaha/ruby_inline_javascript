require 'json'

#== SYNOPSIS:
#
#To call a JavaScript function as if it was Ruby:
#
#    js = InlineJavaScript.new('function my_add (a, b) { return a+b}')
#    js.my_add(1, 2) #=> 3
#
#Using more complex types:
#
#    js = InlineJavaScript.new('function my_concat (a) { return {concat_string: a[0] + " " + a[1]} }')
#    js.my_concat(['hello', 'world']) #=> {"concat_string" => "hello world"}


class InlineJavaScript
  VERSION = '0.1'

  # Takes a string containing some JavaScript and executes it. The state is maintained.
  # JavaScript functions defined in the string can be called directly from an instance
  # of InlineJavaScript as if they were methods.

  def initialize javascript_functions
    require File.join(File.dirname(__FILE__), %w{.. ext inline_java_script_v8_wrapper inline_java_script_v8_wrapper})

    @wrapper = InlineJavaScript::V8Wrapper.new
    @wrapper.execute(javascript_functions)
  end

  # Attempts to call whatever JavaScript function you defined in the constructor.
  # It will accept any number of parameters of String, Fixnum, Array or Hash and can
  # support returning the same from JavaScript.

  def method_missing(method, *arguments, &unused_block)
    json_arguments = arguments.map do |arg|
      "JSON.parse(" + arg.to_json.to_json + ")"
    end

    JSON[@wrapper.execute("JSON.stringify({result: #{method}(#{json_arguments.join(',')})})")]['result']
  end
end
