desc "Build the binary extension"
task :build_ext do
  sh "ruby ext/inline_javascript/extconf.rb && make"
end