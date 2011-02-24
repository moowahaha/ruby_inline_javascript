require File.dirname(__FILE__) + "/../ext/inline_javascript_v8_wrapper/inline_javascript_v8_wrapper"

describe InlineJavaScriptV8Wrapper do
  it "should blah" do
    wrapper = InlineJavaScriptV8Wrapper.new('function blah() {"hello"}')
    wrapper.execute('blah()').should == "hello"
  end
end