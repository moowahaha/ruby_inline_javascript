require 'rubygems'
gem 'hoe', '>= 2.1.0'
require 'hoe'
require 'fileutils'
require './lib/inline_java_script'

Hoe.plugin :newgem

$hoe = Hoe.spec 'inline_java_script' do
  self.developer 'Stephen Hardisty', 'moowahaha@hotmail.com'
  self.post_install_message = 'PostInstall.txt'
  self.rubyforge_name       = self.name
  self.extra_deps         = [['json','>= 0']]

  self.clean_globs = [
    'ext/inline_java_script_v8_wrapper/Makefile',
    'ext/inline_java_script_v8_wrapper/*.{o,so,bundle,a,log,dll}',
    'ext/inline_java_script_v8_wrapper/conftest.dSYM'
  ]

  self.spec_extras = { :extensions => ["ext/inline_java_script_v8_wrapper/extconf.rb"] }
end

task :default do
  sh 'rake clean && rake extconf:compile && rake spec'
end

require 'newgem/tasks'
Dir['tasks/**/*.rake'].each { |t| load t }

