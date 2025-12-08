glib_compile_schemas = find_program('glib-compile-schemas', required: true)
gschema_conf = configuration_data()
gschema_conf.set('APP_ID', app_id)
gschema_conf.set('APP_PATH', app_path)
gschema_conf.set('GETTEXT', gettext)
configure_file(
    input: 'corners.gschema.xml.in',
    configuration: gschema_conf,
    output: '@0@.gschema.xml'.format(app_id),
    install: true,
    install_dir: schemadir
)
if glib_compile_schemas.found()
    test(
        'validate-gschema',
        glib_compile_schemas,
        args: [
            '--strict',
            '--dry-run',
            meson.current_build_dir()
        ]
    )
endif

resources_conf = configuration_data()
resources_conf.set('APP_PATH', app_path)
resources_file = configure_file(
    input: 'corners.gresource.xml.in',
    configuration: resources_conf,
    output: '@0@.gresource.xml'.format(app_id)
)
resources = gnome.compile_resources(
    '@0@-resources'.format(meson.project_name()),
    resources_file,
    c_name: meson.project_name()
)