require 'mkmf'

have_library('mozjs')

create_makefile("inline_java_script_spidermonkey_wrapper")
