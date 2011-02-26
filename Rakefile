require 'rubygems'
gem 'hoe', '>= 2.1.0'
require 'hoe'
require 'fileutils'
require './lib/inline_java_script'

Hoe.plugin :newgem
# Hoe.plugin :website
# Hoe.plugin :cucumberfeatures

# Generate all the Rake tasks
# Run 'rake -T' to see list of generated tasks (from gem root directory)
$hoe = Hoe.spec 'inline_java_script' do
  self.developer 'FIXME full name', 'FIXME email'
  self.post_install_message = 'PostInstall.txt' # TODO remove if post-install message not required
  self.rubyforge_name       = self.name # TODO this is default value
  # self.extra_deps         = [['activesupport','>= 2.0.2']]

  self.clean_globs = [
    'ext/inline_java_script_v8_wrapper/Makefile',
    'ext/inline_java_script_v8_wrapper/*.{o,so,bundle,a,log,dll}',
    'ext/inline_java_script_v8_wrapper/conftest.dSYM'
  ]

  self.spec_extras = { :extensions => ["ext/inline_java_script/extconf.rb"] }
end

task :default do
  sh 'rake clean && rake extconf:compile && rake spec'
end

require 'newgem/tasks'
Dir['tasks/**/*.rake'].each { |t| load t }

