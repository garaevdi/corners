project(
    'corners',
    'cpp',
    version: '0.1',
    license: 'GPL-3.0'
)

app_id = 'com.github.garaevdi.corners'
app_path = '/' + app_id.replace('.', '/')
gettext = meson.project_name()

prefix = get_option('prefix')
datadir = prefix / get_option('datadir')
pkgdatadir = datadir / meson.project_name()
schemadir = datadir / 'glib-2.0' / 'schemas'

gnome = import('gnome')

subdir('data')
subdir('src')

gnome.post_install(
    glib_compile_schemas: true
)
