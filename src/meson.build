config_h_conf = configuration_data()
config_h_conf.set_quoted('APP_ID', app_id)
config_h_conf.set_quoted('APP_PATH', app_path)
config_h = configure_file(
    configuration: config_h_conf,
    output: 'config.h'
)

deps = [
    dependency('peel'),
    dependency('gtk4')
]

peel_gen = find_program('peel-gen', required: true)
peel_h = custom_target(
    'peel-codegen',
    command: [
        peel_gen,
        '--recursive',
        '--out-dir', '@OUTDIR@',
        'Gtk', '4.0'
    ],
    output: 'peel'
)

sources = [
    resources,
    config_h,
    peel_h,
    'corners-application.cpp',
    'corners-application.hpp',
    'corners-window.cpp',
    'corners-window.hpp'
]

executable(
    meson.project_name(),
    sources,
    dependencies: deps,
    install: true
)