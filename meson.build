project('fractals','cpp')
src=['main.cpp',
'event_handler.cpp',
'canvas.cpp',
'julia_fractal.cpp',
'key_event_handler.cpp',
'mandelbrot_fractal.cpp',
'gui_element.cpp',
'button.cpp',
'mouse_button_event_handler.cpp',
'label.cpp',
'text_input.cpp',
'fractal.cpp',
'morse_fractal.cpp',
'ttf/hack_ttf.cpp']
sys_dep = dependency('sfml-system',required:false)
win_dep = dependency('sfml-window',required:false)
gfx_dep = dependency('sfml-graphics',required:false)
deps=[sys_dep,win_dep,gfx_dep]
if not (sys_dep.found() and win_dep.found() and gfx_dep.found())
    deps = [subproject('sfml',default_options:'default_library=static').get_variable('sfml_dep')]
endif

executable('fractals',src,dependencies:deps)
