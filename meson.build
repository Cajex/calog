project('calog', ['cpp', 'c'],
        version : '1.0.0',
        default_options : ['warning_level=3', 'cpp_std=c++20'])

lib_args = ['-DBUILDING_MESON_LIBRARY']

#source files
calog_include = include_directories('src/include')
calog_files = files('src/calog.cpp')

calog = shared_library('calog', calog_files,
               install : true,
               cpp_args : lib_args,
               include_directories: calog_include
)

#declare calog dependency
calog_dep = declare_dependency(include_directories: calog_include, link_with: calog)
