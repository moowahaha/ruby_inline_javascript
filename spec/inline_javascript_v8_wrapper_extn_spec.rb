require File.dirname(__FILE__) + "/../ext/inline_java_script_v8_wrapper/inline_java_script_v8_wrapper"

describe InlineJavaScript::V8Wrapper do

  it "should execute some javascript" do
    wrapper = InlineJavaScript::V8Wrapper.new
    wrapper.execute('function blah() { return "hello"}')
    wrapper.execute('blah()').should == "hello"
  end

  it "should not have globally scoped JS" do
    InlineJavaScript::V8Wrapper.new.execute('function i_should_have_a_short_life() {}')

    wrapper = InlineJavaScript::V8Wrapper.new
    wrapper.execute('function i_am_wasted_javascript () {}')
    -> { wrapper.execute('i_should_have_a_short_life()') }.should raise_error(SyntaxError)
  end

end