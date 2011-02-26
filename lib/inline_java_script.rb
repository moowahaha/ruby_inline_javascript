require 'json'

class InlineJavaScript
  VERSION = '0.0.1'

  def initialize javascript_functions
    require File.join(File.dirname(__FILE__), %w{.. ext inline_java_script_v8_wrapper inline_java_script_v8_wrapper})

    @wrapper = InlineJavaScript::V8Wrapper.new
    @wrapper.execute(javascript_functions)
  end

  def method_missing(method, *arguments, &unused_block)
    json_arguments = arguments.map do |arg|
      "JSON.parse(" + arg.to_json.to_json + ")"
    end

    JSON[@wrapper.execute("JSON.stringify({result: #{method}(#{json_arguments.join(',')})})")]['result']
  end
end
