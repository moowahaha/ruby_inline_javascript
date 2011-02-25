describe Inline::Javascript do

  it "should call pass arguments and return results" do
    js = Inline::Javascript.new('function concat (a, b) { return(a + " " + b) }')
    js.concat('bath', 'rules').should == 'bath rules'
  end

end
