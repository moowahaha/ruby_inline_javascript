require File.dirname(__FILE__) + '/spec_helper'

$:.unshift File.dirname(__FILE__) + "/../ext/inline_java_script_spidermonkey_wrapper"
require "inline_java_script_spidermonkey_wrapper.so"

describe "inline_java_script_spidermonkey_wrapper" do
  it "should do nothing" do
    true.should == true
  end
end