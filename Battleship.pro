TEMPLATE = subdirs
SUBDIRS = console gui common
console.depends = common
gui.depends = common
