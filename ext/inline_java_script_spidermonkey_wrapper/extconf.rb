require 'mkmf'

have_library('mozjs')

$CFLAGS = '-g'

create_makefile("inline_java_script_spidermonkey_wrapper")
