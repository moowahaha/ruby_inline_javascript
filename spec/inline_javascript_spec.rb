describe Inline::Javascript do

  it "should call pass arguments and return results" do
    js = Inline::Javascript.new('function concat (a, b) { return(a + " " + b) }')
    js.concat('bath', 'rules').should == 'steve rules'
  end

end
