require File.dirname(__FILE__) + '/spec_helper'

$:.unshift File.dirname(__FILE__) + "/../ext/inline_javascript_v8_wrapper"
require "inline_javascript_v8_wrapper.so"

describe "inline_javascript_v8_wrapper" do
  it "should do nothing" do
    true.should == true
  end
end