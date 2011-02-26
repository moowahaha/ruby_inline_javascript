require 'json'

module Inline
  class Javascript
    VERSION = '0.0.1'

    def initialize javascript_functions
      require File.join(File.dirname(__FILE__), %w{.. ext inline_javascript_v8_wrapper inline_javascript_v8_wrapper})
      @wrapper = InlineJavaScriptV8Wrapper.new
      @wrapper.execute(javascript_functions)
    end

    def method_missing(method, *arguments, &unused_block)
      json_arguments = arguments.map do |arg|
        "JSON.parse(" + arg.to_json.to_json + ")"
      end

      JSON[@wrapper.execute("JSON.stringify({result: #{method}(#{json_arguments.join(',')})})")]['result']
    end
  end
end
