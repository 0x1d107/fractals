project('fractals','cpp')
src=['main.cpp','event_handler.cpp','canvas.cpp','julia_fractal.cpp','key_event_handler.cpp']
sys_dep = dependency('sfml-system',required:false)
win_dep = dependency('sfml-window',required:false)
gfx_dep = dependency('sfml-graphics',required:false)
deps=[sys_dep,win_dep,gfx_dep]
if not (sys_dep.found() and win_dep.found() and gfx_dep.found())
    deps = [subproject('sfml',default_options:'default_library=static').get_variable('sfml_dep')]
endif

executable('fractals',src,dependencies:deps)
