def compile_wrapper
  `rake clean 2>&1`
  compile_output =  `rake extconf:compile 2>&1`
  raise compile_output if $? != 0
end

unless File.exists?(File.join(File.dirname(__FILE__), %w{.. .. ext inline_javascript_v8_wrapper inline_javascript_v8_wrapper.bundle}))
  compile_wrapper
end
