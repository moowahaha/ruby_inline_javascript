require File.dirname(__FILE__) + "/../ext/inline_javascript_v8_wrapper/inline_javascript_v8_wrapper"

describe InlineJavaScriptV8Wrapper do

  it "should execute some javascript" do
    wrapper = InlineJavaScriptV8Wrapper.new
    wrapper.execute('function blah() { return "hello"}')
    wrapper.execute('blah()').should == "hello"
  end

  it "should not have globally scoped JS" do
    InlineJavaScriptV8Wrapper.new.execute('function i_should_have_a_short_life() {}')

    wrapper = InlineJavaScriptV8Wrapper.new
    wrapper.execute('function i_am_wasted_javascript () {}')
    -> { wrapper.execute('i_should_have_a_short_life()') }.should raise_error(SyntaxError)
  end

end