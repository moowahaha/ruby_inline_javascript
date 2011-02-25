describe Inline::Javascript do

  it "should call pass arguments and return results" do
    js = Inline::Javascript.new('function concat (a, b) { return(a + " " + b) }')
    js.concat('bath', 'rules').should == 'bath rules'
  end

  it "should be able to deal with numeric values" do
    js = Inline::Javascript.new('function add (a, b) { return(a + b) }')
    js.add(1, 100).should == 101
  end

  it "should handle more complex types" do
    js = Inline::Javascript.new('function something (some_array) { return {second: some_array[1]} }')
    js.something(%w{hopefully this works great}).should == {'second' => 'this'}
  end

end
