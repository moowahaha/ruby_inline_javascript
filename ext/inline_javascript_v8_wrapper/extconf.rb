require 'mkmf'

dir_config("inline_javascript_v8_wrapper")

$LIBS << ' -lv8'

create_makefile("inline_javascript_v8_wrapper")
