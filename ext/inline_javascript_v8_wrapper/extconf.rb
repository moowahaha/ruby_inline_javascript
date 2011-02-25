require 'mkmf'

dir_config("inline_javascript_v8_wrapper")

have_library('v8')

create_makefile("inline_javascript_v8_wrapper")
