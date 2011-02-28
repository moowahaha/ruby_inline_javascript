require './ext/inline_java_script_spidermonkey_wrapper/inline_java_script_spidermonkey_wrapper'

# http://powerman.name/doc/jquery_in_spidermonkey.html#_env_js

js = InlineJavaScript::SpiderMonkeyWrapper.new
js.execute(File.open('scratchpad/env.rhino.1.2.js').read)
js.execute(File.open('scratchpad/jquery-1.5.min.js').read)
